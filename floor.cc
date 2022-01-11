#include "floor.h"
#include <algorithm>
#include "human.h"
#include "dragon.h"
#include "elf.h"
#include "orc.h"
#include "dwarf.h"
#include "halfling.h"
#include "merchant.h"
#include "item.h"
#include "dragonhoard.h"
#include "gold.h"
#include "random.h"
#include "atkpotion.h"
#include "defpotion.h"
#include "hppotion.h"

Floor::Chamber::Chamber(std::vector<Point> a){
    area = a;
    hasStart = false;
}

// returns a random position within the chamber
Point Floor::Chamber::getRandPos(){
    int index = Random::getRand(0, area.size()-1);
    return area[index];
}

// checks if the chamber contains a point
bool Floor::Chamber::contains(Point p){
    for (Point p2 : area){
        if (p == p2){
            return true;
        }
    }
    return false;
}

Floor::Floor(char g[79][25], bool custom){
    // copy the grid, also loads in start and end points
    for (int y = 0; y < 25; y++){
        for (int x = 0; x < 79; x++){
            if (g[x][y] == '\\'){
                endPos = Point(x, y);
            }
            grid[x][y] = g[x][y];
            
            if (g[x][y] == '@'){
                startPos = Point(x, y);
                playerPos = startPos;
                grid[x][y] = '.';
            }
        }
    }
    
    // detect the chambers in the file
    createChambers();
    
    if (custom){
        // load in enemies / items from file
        loadEnemies();
        loadItems();
    }else{
        // randomly generate start and end points
        startPos = getRandPos(true, false);
        endPos = getRandPos(false, true);
        grid[endPos.getX()][endPos.getY()] = '\\';
        
        // create 20 random enemies
        for (int i = 0; i < 20; i++){
            createRandEnemy();
        }
        
        // create 10 random gold and potions
        for (int i = 0; i < 10; i++){
            createGold();
            createPotion();
        }
    }
    
    // create traps
    for (int i = 0; i < 10; i++){
        traps.emplace_back(getRandPos());
    }
}

// create enemies based off of file
void Floor::loadEnemies(){
    for (int y = 0; y < 25; y++){
        for (int x = 0; x < 79; x++){
            if (grid[x][y] == 'H'){
                createEnemy<Human>(x, y);
            } else if (grid[x][y] == 'W'){
                createEnemy<Dwarf>(x, y);
            } else if (grid[x][y] == 'E'){
                createEnemy<Elf>(x, y);
            } else if (grid[x][y] == 'O'){
                createEnemy<Orc>(x, y);
            } else if (grid[x][y] == 'M'){
                createEnemy<Merchant>(x, y);
            } else if (grid[x][y] == 'D'){
                createEnemy<Dragon>(x, y);
            } else if (grid[x][y] == 'L'){
                createEnemy<Halfling>(x, y);
            }
        }
    }
}

// create items based off of file
void Floor::loadItems(){
    for (int y = 0; y < 25; y++){
        for (int x = 0; x < 79; x++){
            if (grid[x][y] == '0'){
                items.push_back(std::make_unique<HpPotion>(Point(x, y), 10));
                grid[x][y] = 'P';
            } else if (grid[x][y] == '1'){
                items.push_back(std::make_unique<AtkPotion>(Point(x, y), nullptr, 5));
                grid[x][y] = 'P';
            } else if (grid[x][y] == '2'){
                items.push_back(std::make_unique<DefPotion>(Point(x, y), nullptr, 5));
                grid[x][y] = 'P';
            } else if (grid[x][y] == '3'){
                items.push_back(std::make_unique<HpPotion>(Point(x, y), -10));
                grid[x][y] = 'P';
            } else if (grid[x][y] == '4'){
                items.push_back(std::make_unique<AtkPotion>(Point(x, y), nullptr, -5));
                grid[x][y] = 'P';
            } else if (grid[x][y] == '5'){
                items.push_back(std::make_unique<DefPotion>(Point(x, y), nullptr, -5));
                grid[x][y] = 'P';
            } else if (grid[x][y] == '6'){
                createGold(x, y, 2);
            } else if (grid[x][y] == '7'){
                createGold(x, y, 1);
            } else if (grid[x][y] == '8'){
                createGold(x, y, 4);
            } else if (grid[x][y] == '9'){
                createHoard(x, y);
            }
        }
    }
}

void Floor::setPlayerPos(Point p){
    playerPos = p;
}

// return random position within the floor
// bools account for start and end points
Point Floor::getRandPos(bool start, bool end){
    Point p;
    int index;
    do{
        do{
            index = Random::getRand(0, chambers.size()-1);
        }while(end ? chambers[index].hasStart : false);
        p = chambers[index].getRandPos();
    }while(grid[p.getX()][p.getY()] != '.' || p == playerPos);
    
    if (start){
        chambers[index].hasStart = true;
    }
    return p;
}

// returns the closest unoccupied point to the given point
Point Floor::getClosestPoint(Point p){
    std::vector<Point> points;
    // find correct chamber and copy its area
    for (int i = 0; i < static_cast<int>(chambers.size()); i++){
        if (chambers[i].contains(p)){
            points = chambers[i].area;
            break;
        }
    }
    
    // sorts points by shortest distance
    std::sort(points.begin(), points.end(), [p](Point p1, Point p2){return p1.distance(p) < p2.distance(p);});
    
    // search for valid point
    for (Point e : points){
        if (grid[e.getX()][e.getY()] == '.' && !(e == p) && !(playerPos == e)){
            return e;
        }
    }
    return p;
}

// check if point is in chamber
bool Floor::chambersContain(Point p){
    for (Chamber c : chambers){
        if (c.contains(p)){
            return true;
        }
    }
    return false;
}

bool Floor::validChar(char c){
    const char ignoreChars[20] = {'0','1','2','3','4','5','6','7','8','9','@','\\', '.','H','W','E','O','M','D','L'};
    for (char c2 : ignoreChars){
        if (c == c2){
            return true;
        }
    }
    return false;
}

// recursively traverse a chamber, storing each point
void Floor::traverseChamber(std::vector<Point>& arr, int x, int y){
    for (Point offset : dirArr){
        Point p{x + offset.getX(), y + offset.getY()};
        if (validChar(grid[x + offset.getX()][y + offset.getY()]) && std::find(arr.begin(), arr.end(), p) == arr.end()){
            arr.push_back(p);
            traverseChamber(arr, x + offset.getX(), y + offset.getY());
        }
    }
}

void Floor::createChambers(){
    bool foundChamber = false;
    for (int y = 0; y < 25; y++){
        for (int x = 0; x < 79; x++){
            // search for doorways, and create chambers based off adjacent empty spaces
            if (grid[x][y] == '+'){
                for (Point offset : dirArr){
                    if (validChar(grid[x + offset.getX()][y + offset.getY()]) && !chambersContain(Point(x + offset.getX(), y + offset.getY()))){
                        foundChamber = true;
                        std::vector<Point> points;
                        traverseChamber(points, x + offset.getX(), y + offset.getY());
                        chambers.emplace_back(points);
                    }
                }
            }
        }
    }
    
    // single chamber case, manual search
    if (!foundChamber){
        for (int y = 0; y < 25; y++){
            for (int x = 0; x < 79; x++){
                if (validChar(grid[x][y])){
                    foundChamber = true;
                    std::vector<Point> points;
                    traverseChamber(points, x, y);
                    chambers.emplace_back(points);
                }
                if (foundChamber) break;
            }
            if (foundChamber) break;
        }
    }
}

// create rng weighted enemies
void Floor::createRandEnemy(Point pos){
    Point p = ((pos == Point(-1,-1)) ? getRandPos() : pos);
    switch(Random::getRand(0, 17)){
        case 0 ... 3:
            enemies.push_back(std::make_shared<Human>());
            grid[p.getX()][p.getY()] = 'H';
            break;
        case 4 ... 6:
            enemies.push_back(std::make_shared<Dwarf>());
            grid[p.getX()][p.getY()] = 'W';
            break;
        case 7 ... 11:
            enemies.push_back(std::make_shared<Halfling>());
            grid[p.getX()][p.getY()] = 'L';
            break;
        case 12 ... 13:
            enemies.push_back(std::make_shared<Elf>());
            grid[p.getX()][p.getY()] = 'E';
            break;
        case 14 ... 15:
            enemies.push_back(std::make_shared<Orc>());
            grid[p.getX()][p.getY()] = 'O';
            break;
        case 16 ... 17:
            enemies.push_back(std::make_shared<Merchant>());
            grid[p.getX()][p.getY()] = 'M';
            break;
    }
    enemies.back()->move(p);
}

// create rng weighted gold
void Floor::createGold(){
    Point p = getRandPos();
    switch(Random::getRand(0, 7)){
        case 0 ... 4:
        {
            items.push_back(std::make_unique<Gold>(p, 2));
            grid[p.getX()][p.getY()] = 'G';
            break;
        }
        case 5:
        {
            auto d = std::make_shared<Dragon>();
            enemies.push_back(d);
            Point dp = getClosestPoint(p);
            grid[dp.getX()][dp.getY()] = 'D';
            enemies.back()->move(dp);
            
            // link dragonhoard to a dragon
            items.push_back(std::make_unique<DragonHoard>(p, d));
            grid[p.getX()][p.getY()] = 'G';
            break;
        }
        case 6 ... 7:
        {
            items.push_back(std::make_unique<Gold>(p, 1));
            grid[p.getX()][p.getY()] = 'G';
            break;
        }
    }
}

void Floor::createGold(int x, int y, int amount){
    items.push_back(std::make_unique<Gold>(Point(x, y), amount));
    grid[x][y] = 'G';
}

// create dragon hoard from file
void Floor::createHoard(int x, int y){
    int index = -1;
    // find closest dragon
    for (int i = 0; i < static_cast<int>(enemies.size()); i++){
        if (enemies[i]->getRace() == "Dragon" &&
            (index == -1 || enemies[i]->getPos().distance(Point(x, y)) < enemies[index]->getPos().distance(Point(x, y)))){
            index = i;
        }
    }
    // link dragonhoard to closest dragon
    items.push_back(std::make_unique<DragonHoard>(Point(x, y), std::static_pointer_cast<Dragon>(enemies[index])));
    grid[x][y] = 'G';
}

void Floor::createPotion(){
    Point p = getRandPos();
    switch(Random::getRand(0, 5)){
        case 0:
            items.push_back(std::make_unique<HpPotion>(p, 10));
            break;
        case 1:
            items.push_back(std::make_unique<HpPotion>(p, -10));
            break;
        case 2:
            items.push_back(std::make_unique<AtkPotion>(p, nullptr, 5));
            break;
        case 3:
            items.push_back(std::make_unique<AtkPotion>(p, nullptr, -5));
            break;
        case 4:
            items.push_back(std::make_unique<DefPotion>(p, nullptr, 5));
            break;
        case 5:
            items.push_back(std::make_unique<DefPotion>(p, nullptr, -5));
            break;
    }
    grid[p.getX()][p.getY()] = 'P';
}

// set all merchant to be hostile
void Floor::agroMerchants(){
    for (auto e : enemies){
        if (e->getRace() == "Merchant"){
            e->setHostile(true);
        }
    }
}

std::string Floor::checkTraps(){
    for (int i = 0; i < static_cast<int>(traps.size()); i++){
        if (traps[i] == playerPos){
            traps.erase(traps.begin()+i);
            for (int k = 0; k < 4; k++){
                Point c = getClosestPoint(playerPos);
                createRandEnemy(c);
            }
            return "PC has triggered a trap!\n";
        }
    }
    return "";
}
