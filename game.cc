#include "game.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "shade.h"
#include "drow.h"
#include "troll.h"
#include "vampire.h"
#include "goblin.h"
#include "merchant.h"

using std::cout;
using std::endl;

bool Game::flashlightOn = false;
bool Game::trapsOn = false;
bool inShop = false;
std::shared_ptr<Merchant> shopMerchant = nullptr;

// used for conversions from directions to offsets
std::map<std::string, Point> dirMap = {{"no", Point{0,-1}},{"so", Point{0,1}},{"ea", Point{1,0}},{"we", Point{-1,0}},{"ne", Point{1,-1}},{"nw", Point{-1,-1}},{"se", Point{1,1}},{"sw", Point{-1,1}}};

// creating a game also immediately loads the floors
Game::Game(std::string file){
    curFloor = -1;
    win = false;
    lose = false;
    moveEnemies = true;
    floorFile = file;
    createFloors();
}

// init the player
void Game::setRace(char c){
    if (c == 's'){
        player = std::make_unique<Shade>();
    }else if (c == 'd'){
        player = std::make_unique<Drow>();
    }else if (c == 'v'){
        player = std::make_unique<Vampire>();
    }else if (c == 't'){
        player = std::make_unique<Troll>();
    }else if (c == 'g'){
        player = std::make_unique<Goblin>();
    }
}

std::unique_ptr<Player>& Game::getPlayer(){
    return player;
}

// called each time the player reaches the stairs
void Game::progress(){
    curFloor++;
    if (curFloor != 0) {
        messageBuffer += "PC has moved to the next floor!\n";
    }
    player->move(floors[curFloor].startPos);
    player->resetPotions();
    if (curFloor == 5){
        win = true;
    }
    setFPoints();
}

// allows possible collection of item based on their id
std::string Game::collectItem(Point targetPos, std::string type){
    std::string ret = "";
    for (int i = 0; i < static_cast<int>(floors[curFloor].items.size()); i++){
        // check if item is of the correct position and type
        if (floors[curFloor].items[i]->getPos() == targetPos &&
            floors[curFloor].items[i]->getId().find(type) != std::string::npos){
            // let the item process its pickup
            if (floors[curFloor].items[i]->onPickup(player)){
                ret = floors[curFloor].items[i]->getId();
                // delete the item once it is successfully processed
                floors[curFloor].grid[targetPos.getX()][targetPos.getY()] = '.';
                floors[curFloor].items.erase(floors[curFloor].items.begin() + i);
                
                if (type == "Gold"){
                    messageBuffer += "PC has picked up a pile of gold.\n";
                }
            }else{
                messageBuffer += "The Dragon prevents you from stealing its hoard!\n";
            }
        }
    }
    // return item id for output
    return ret;
}

// used for ouputing info on potions
void Game::detectPotions(){
    for (auto &item : floors[curFloor].items){
        Point targetPos = item->getPos();
        // if item is within range of the player
        if ((abs(targetPos.getX() - player->getPos().getX()) <= 1) &&
            (abs(targetPos.getY() - player->getPos().getY()) <= 1)){
            // if item is a potion
            if (item->getId().find("Potion") != std::string::npos){
                // check if potion is known
                messageBuffer += "PC sees " + ((knownPotions.find(item->getId()) != knownPotions.end()) ? "a " + item->getId() : "an unknown potion") + ".\n";
            }
        }
    }
}

void Game::updateEnemies(){
    for (auto e : floors[curFloor].enemies){
        // only update enemies if they are alive
        if (!e->isDead()){
            bool hasAttacked = false;
            // attack if close to player and hostile
            if (e->isHostile() && e->inRange(player->getPos())){
                messageBuffer += player->defend(e) + "\n";
                hasAttacked = true;
            }
            // only move under certain conditions
            if (moveEnemies && !hasAttacked){
                char c = floors[curFloor].grid[e->getPos().getX()][e->getPos().getY()];
                floors[curFloor].grid[e->getPos().getX()][e->getPos().getY()] = '.';
                e->move(floors[curFloor].grid, player->getPos());
                floors[curFloor].grid[e->getPos().getX()][e->getPos().getY()] = c;
            }
        }
    }
    
    // delete dead enemies
    for (int i = 0; i < static_cast<int>(floors[curFloor].enemies.size()); i++){
        if (floors[curFloor].enemies[i]->isDead()){
            Point p = floors[curFloor].enemies[i]->getPos();
            floors[curFloor].grid[p.getX()][p.getY()] = '.';
            
            // spawn gold piles upon slaying
            if (floors[curFloor].enemies[i]->getRace() == "Human"){
                Point g1 = floors[curFloor].getClosestPoint(p);
                floors[curFloor].createGold(g1.getX(), g1.getY(), 2);
                Point g2 = floors[curFloor].getClosestPoint(p);
                floors[curFloor].createGold(g2.getX(), g2.getY(), 2);
            } else if (floors[curFloor].enemies[i]->getRace() == "Merchant"){
                floors[curFloor].createGold(p.getX(), p.getY(), 4);
            }
            
            floors[curFloor].enemies.erase(floors[curFloor].enemies.begin() + i);
            i--;
        }
    }
}

void Game::update(std::string cmd, std::string dir){
    messageBuffer = "";
    if (inShop == false) {
        if (cmd == "u"){
            Point targetPos = player->getPos() + dirMap[dir];
            std::string usedPotion = collectItem(targetPos, "Potion");
            if (usedPotion != ""){
                messageBuffer += "PC used a " + usedPotion + ".\n";
                knownPotions.insert(usedPotion);
            }
        } else if (cmd == "a"){
            Point targetPos = player->getPos() + dirMap[dir];
            for (auto e : floors[curFloor].enemies){
                if (e->getPos() == targetPos){
                    messageBuffer += e->defend(player) + "\n";
                    
                    //agro merchants
                    if (e->getRace() == "Merchant"){
                        for (int k = 0; k < static_cast<int>(floors.size()); k++){
                            floors[k].agroMerchants();
                        }
                    }
                }
            }
        } else if (cmd == "f"){
            moveEnemies = !moveEnemies;
        } else if (cmd == "t") {
            Point targetPos = player->getPos() + dirMap[dir];
            for (auto e : floors[curFloor].enemies){
                if (e->getPos() == targetPos){
                    if (e->getRace() == "Merchant" && !e->isHostile()){
                        shopMerchant = std::static_pointer_cast<Merchant>(e);
                        messageBuffer += shopMerchant->s->view();
                        messageBuffer += "\n[no/ea/so/we/(f)arewell)]\n";
                        inShop = true;
                        return;
                    }
                }
            }
        } else {
            char allowed[5] = {'.','+','#','G','\\'};
            Point newPos = player->getPos() + dirMap[cmd];
            for (char c : allowed){
                if (floors[curFloor].grid[newPos.getX()][newPos.getY()] == c){
                    player->move(newPos);
                    floors[curFloor].setPlayerPos(newPos);
                }
            }
            
            //check for gold under player
            collectItem(player->getPos(), "Gold");
            detectPotions();
            if (flashlightOn)
                setFPoints();
        }
        
        updateEnemies();
        
        if (trapsOn)
            messageBuffer += floors[curFloor].checkTraps();
        
        // check lose condition
        if (player->getHp() == 0){
            lose = true;
            draw();
        }
        
        // implement troll's trait
        if (player->getRace() == "Troll"){
            player->setHp(player->getHp() + 5);
        }

        // check stairs
        if (player->getPos() == floors[curFloor].endPos){
            progress();
        }
    } else if (inShop) {
        std::string temp = "";
        if (cmd == "no") {
            temp = shopMerchant->s->buy(0, player);
        } else if (cmd == "ea") {
            temp = shopMerchant->s->buy(1, player);
        } else if (cmd == "so") {
            temp = shopMerchant->s->buy(2, player);
        } else if (cmd == "we") {
            temp = shopMerchant->s->buy(3, player);
        } else if (cmd == "f") {
            shopMerchant = nullptr;
            inShop = false;
            messageBuffer += "You have exited the shop.\n";
            return;
        } else {
            temp += "\nThe CS professor words echo ... There's a time and place for everything, but not now.\n";
        }
        messageBuffer += shopMerchant->s->view();
        messageBuffer += temp;
        messageBuffer += "\n[no/ea/so/we/(f)arewell)]\n";
    }
}

void Game::setFPoints(){
    fPoints.clear();
    const double PI = 3.14159;
    for (double a = 0; a <= 2*PI; a += 0.01){
        bool hitWall = false;
        for (double r = 0.75; r <= 4; r += 0.25){
            int x = static_cast<int>(round(player->getPos().getX() + 1.75*r*cos(a)));
            int y = static_cast<int>(round(player->getPos().getY() + r*sin(a)));
            if (floors[curFloor].grid[x][y] == '|' ||
                floors[curFloor].grid[x][y] == '-' ||
                floors[curFloor].grid[x][y] == '+' ||
                floors[curFloor].grid[x][y] == ' '){
                hitWall = true;;
            }
            fPoints.emplace_back(x, y);
            if(hitWall)
                break;
        }
    }
}

void Game::draw(){
    // draw the grid
    for (int y = 0; y < 25; y++){
        for (int x = 0; x < 79; x++){
            if (player->getPos() == Point(x, y)){
                cout << "@";
            }else{
                if (flashlightOn && y != 0 && y!= 24 && x != 0 && x != 78){
                    bool b = std::find(fPoints.begin(), fPoints.end(), Point(x,y)) != fPoints.end();
                    cout << (b ? floors[curFloor].grid[x][y] : ' ');
                } else{
                    cout << floors[curFloor].grid[x][y];
                }
            }
        }
        cout << endl;
    }
    // output information rows
    cout << "Race: " << player->getRace() << std::setw(30) << "Gold: " << player->getGold() << std::setw(33) << "Floor: " << curFloor + 1 << endl;
    cout << "HP: " << player->getHp() << endl;
    cout << "Atk: " << player->getAtk() << endl;
    cout << "Def: " << player->getDef() << endl;
    
    // output buffered messaged
    if (messageBuffer != "" && inShop == false) {
        cout << "Action: " << messageBuffer;
    } else if (messageBuffer != "") {
        cout << "Shop:\n" << messageBuffer;
    }
}

// loads in the floors from file
void Game::createFloors(){
    std::ifstream f{floorFile};
    for (int k = 0; k < 5; k++){
        char grid[79][25];
        for (int y = 0; y < 25; y++){
            for (int x = 0; x < 79; x++){
                f >> std::noskipws >> grid[x][y];
                
                if (grid[x][y] == '\n'){
                    x -= 1;
                }
            }
        }
        // create new floors using the loaded in array
        floors.emplace_back(grid, floorFile != "default.txt");
    }
}

bool Game::hasWon(){
    return win;
}

bool Game::hasLost(){
    return lose;
}

void Game::toggleFlashlight(){
    flashlightOn = !flashlightOn;
}

bool Game::isFlashlightOn(){
    return flashlightOn;
}

void Game::toggleTraps(){
    trapsOn = !trapsOn;
}

bool Game::areTrapsOn(){
    return trapsOn;
}
