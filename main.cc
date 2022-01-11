#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include "game.h"
#include "point.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

string state = "Main Menu";
string file = "default.txt";
bool shopDLC = false;

void lineBreak(){
    cout << endl;
    cout << "|===============================================================|" << endl;
    cout << endl;
}

void displayMainMenu(){
    lineBreak();
    cout << "                _..._          _..._" << endl;
    cout << "             .-'_..._''.    .-'_..._''. ..-'''-." << endl;
    cout << "            .' .'      '.\\ .' .'      '.\\\\.-'''\\ \\       ." << endl;
    cout << "            / .'           / .'                  | |    .'|" << endl;
    cout << "            . '            . '                 __/ /   .'  |" << endl;
    cout << "            | |            | |                |_  '.  <    |" << endl;
    cout << "            | |            | |                   `.  \\ |   | ____" << endl;
    cout << "            . '            . '                     \\ '.|   | \\ .'" << endl;
    cout << "            \\ '.          .\\ '.          .         , ||   |/  ." << endl;
    cout << "            '. `._____.-'/ '. `._____.-'/         | ||    /\\  \\" << endl;
    cout << "             `-.______ /    `-.______ /         / ,'|   |  \\  \\" << endl;
    cout << "                      `              `  -....--'  / '    \\  \\  \\" << endl;
    cout << "                                        `.. __..-' '------'  '---'" << endl;
    cout << endl;
    cout << " ____  _                     ____        _                   ____  _     ____" << endl;
    cout << "|  _ \\| | __ _ _   _        |  _ \\ _   _| | ___  ___        |  _ \\| |   / ___|" << endl;
    cout << "| |_) | |/ _` | | | |       | |_) | | | | |/ _ \\/ __|       | | | | |  | |" << endl;
    cout << "|  __/| | (_| | |_| |       |  _ <| |_| | |  __/\\__ \\       | |_| | |__| |___" << endl;
    cout << "|_|   |_|\\__,_|\\__, |       |_| \\_\\\\__,_|_|\\___||___/       |____/|_____\\____|" << endl;
    cout << "               |___/" << endl;
    cout << endl;
    
    bool valid = false;
    while (!valid){
        cout << "[play/rules/dlc/exit]: ";
        string choice;
        cin >> choice;
        
        if (choice == "play"){
            valid = true;
            state = "Race Select";
        } else if (choice == "rules"){
            valid = true;
            state = "Rules";
        } else if (choice == "dlc"){
            valid = true;
            state = "DLC";
        } else if (choice == "exit"){
            valid = true;
            state = "Exit";
        } else{
            cout << "Invalid Command" << endl;
        }
    }
}

void displayRules(){
    lineBreak();
    cout << "What set of rules would you like to view?" << endl;
    cout << "[general/controls/races/enemies/potions/gold/menu]:";
    string choice;
    cin >> choice;
    
    if (choice == "general"){
        lineBreak();
        cout << "The goal of the game is to reach the 5th floor, fighting enemies along the way." << endl;
        cout << "Upon doing so, you will be given a score based on the amount of gold gathered." << endl;
        cout << "However, if you reach 0 HP, you lose!" << endl;
        cout << "The player is denoted by @, while the stairs are denoted by \\" << endl;
    } else if (choice == "controls"){
        lineBreak();
        cout << "In what follows, [direction] indicates the input of one of [no/so/ea/we/ne/nw/se/sw]" << endl;
        cout << endl;
        cout << "The valid commands during gameplay are as follows:" << endl;
        cout << "   [direction]     --> Moves the player one block in the appropriate direction" << endl;
        cout << "   u [direction]   --> Player uses the potion indicated by the given direction" << endl;
        cout << "   a [direction]   --> Player attacks in the given direction" << endl;
        cout << "   f               --> Stops enemies from moving until command is inputed again" << endl;
        cout << "   r               --> Restarts the game" << endl;
        cout << "   q               --> Quit the game" << endl;
    } else if (choice == "races"){
        lineBreak();
        cout << "Upon starting the game, you will pick the race of the player character." << endl;
        cout << "Each race has its own unique characteristics, so choose carefully!" << endl;
        cout << endl;
        cout << "Shade: (125 HP, 25 Atk, 25 Def)" << endl;
        cout << "   Racial Trait --> 50% more score" << endl;
        cout << endl;
        cout << "Drow: (150 HP, 25 Atk, 15 Def)" << endl;
        cout << "   Racial Trait --> Potion effects multiplied by 1.5" << endl;
        cout << endl;
        cout << "Vampire: (50 HP, 25 Atk, 25 Def)" << endl;
        cout << "   Racial Trait --> Gains 5 HP after every attack" << endl;
        cout << endl;
        cout << "Troll: (120 HP, 25 Atk, 15 Def)" << endl;
        cout << "   Racial Trait --> Regains 5 HP after each turn" << endl;
        cout << endl;
        cout << "Goblin: (110 HP, 15 Atk, 20 Def)" << endl;
        cout << "   Racial Trait --> Steals 5 gold from each slain enemy" << endl;
    } else if (choice == "enemies"){
        lineBreak();
        cout << "You will encounter multiple types of enemies throughout the game." << endl;
        cout << endl;
        cout << "Human: (140 HP, 20 Atk, 20 Def)        denoted by H" << endl;
        cout << "   Racial Trait --> Drops 2 normal piles of gold" << endl;
        cout << endl;
        cout << "Dwarf: (100 HP, 20 Atk, 30 Def)        denoted by W" << endl;
        cout << "   Racial Trait --> Attacking vampires will lose health instead of gaining it" << endl;
        cout << endl;
        cout << "Elf: (140 HP, 30 Atk, 10 Def)          denoted by E" << endl;
        cout << "   Racial Trait --> Attacks twice against every race except drows" << endl;
        cout << endl;
        cout << "Orc: (180 HP, 20 Atk, 25 Def)          denoted by O" << endl;
        cout << "   Racial Trait --> 1.5x damage against goblins" << endl;
        cout << endl;
        cout << "Merchant: (30 HP, 70 Atk, 5 Def)       denoted by M" << endl;
        cout << "   Racial Trait --> Neutral by default, attacking makes all merchants hostile" << endl;
        cout << endl;
        cout << "Dragon: (150 HP, 20 Atk, 20 Def)       denoted by D" << endl;
        cout << "   Racial Trait --> Attacks player when they are next to it or its hoard" << endl;
        cout << endl;
        cout << "Halfling: (100 HP, 15 Atk, 20 Def)     denoted by L" << endl;
        cout << "   Racial Trait --> Player has 50% chance of missing their attack" << endl;
    } else if (choice == "potions"){
        lineBreak();
        cout << "Potions are usable items, denoted by P, that can buff or debuff the player" << endl;
        cout << "The effect of a potion will remain unknown until it has been used." << endl;
        cout << "All potion effects are removed after each floor, except for HP effects." << endl;
        cout << endl;
        cout << "Positive Potions:" << endl;
        cout << "   Restore Health   -->   Restores health by 10" << endl;
        cout << "   Boost Atk        -->   Increases ATK by 5" << endl;
        cout << "   Boost Def        -->   Increases DEF by 5" << endl;
        cout << endl;
        cout << "Negative Potions:" << endl;
        cout << "   Poison Health    -->   Decrease health by 10" << endl;
        cout << "   Wound Atk        -->   Decreases ATK by 5" << endl;
        cout << "   Wound Def        -->   Decreases DEF by 5" << endl;
    } else if (choice == "gold"){
        lineBreak();
        cout << "Gold are collectable items, denoted by G, with several different types." << endl;
        cout << endl;
        cout << "Types:" << endl;
        cout << "   Small Pile      -->   Gives 1 gold" << endl;
        cout << "   Normal Pile     -->   Gives 2 gold" << endl;
        cout << "   Merchant Hoard  -->   Gives 4 gold" << endl;
        cout << "   Dragon Hoard    -->   Gives 6 gold" << endl;
        cout << endl;
        cout << "Merchant Hoards are dropped when a Merchant dies." << endl;
        cout << "Dragon Hoards cannot be picked up until their Dragon has been slain." << endl;
    } else if (choice == "menu"){
        state = "Main Menu";
    } else{
        cout << endl;
        cout << "Invalid Command" << endl;
    }
}

void displayRaceSelect(std::unique_ptr<Game>& game){
    lineBreak();
    cout << "Please select your races:" << endl;
    cout << "[(s)hade/(d)row/(v)ampire/(t)roll/(g)oblin]: ";
    
    bool valid = false;
    char allowed[5] = {'s','d','v','t','g'};
    char choice;
    // ask for input until valid
    while(!valid) {
        cin >> choice;
        for (char c : allowed){
            if (c == choice){
                valid = true;
            }
        }
        if (!valid){
            cout << "Invalid Command" << endl;
        }
    }
    game->setRace(choice);
    game->progress();
    state = "Play";
}

void displayDLC(){
    lineBreak();
    
    cout << "Custom Floor Layouts:" << endl;
    cout << "--> Ability to load in customized floor patterns, as long as the chambers are properly bounded." << endl;
    cout << "--> [Always Enabled]" << endl;
    cout << endl;
    
    cout << "Custom Floor Editor:" << endl;
    cout << "--> Ability to personally design and save floor patterns." << endl;
    cout << "--> [Always Enabled]" << endl;
    cout << endl;
    
    cout << "Flashlight:" << endl;
    cout << "--> Player will have vision limited to a radius around them." << endl;
    cout << "--> [" << (Game::isFlashlightOn() ? "Enabled" : "Disabled") << "]" << endl;
    cout << endl;
    
    cout << "Traps:" << endl;
    cout << "--> Invisible traps that spawn enemies when the Player steps on them" << endl;
    cout << "--> [" << (Game::areTrapsOn() ? "Enabled" : "Disabled") << "]" << endl;
    cout << endl;

    cout << "Shop:" << endl;
    cout << "--> Merchants are now open for buisness! Use the command < t [direction] > to speak to a merchant." << endl;
    cout << "--> [" << (shopDLC ? "Enabled" : "Disabled") << "]" << endl;
    cout << endl;
    
    cout << "What do you want to enable/disable?" << endl;
    cout << "[(e)ditor/(f)lashlight/(t)raps/(s)hop/exit]: ";
    string choice;
    cin >> choice;
    if (choice == "exit"){
        state = "Main Menu";
    } else if (choice == "e"){
        state = "Editor";
    } else if (choice == "f"){
        Game::toggleFlashlight();
    } else if (choice == "t"){
        Game::toggleTraps();
    } else if (choice == "s") {
        if (shopDLC) {
            shopDLC = false;
        } else {
            shopDLC = true;
        }
    } else {
        cout << "Invalid Command" << endl;
    }
}

string readCmd(){
    string allowed[14] = {"no","so","ea","we","ne","nw","se","sw","u","a","f","r","q","t"};
    string s;
    bool valid = false;
    cin >> s;
    
    for (string str : allowed){
        if (str == s){valid = true;}
    }
    
    if (!valid){
        cout << endl;
        cout << "Invalid Command" << endl;
        return "null";
    }
    return s;
}

string readDir(){
    string allowed[8] = {"no","so","ea","we","ne","nw","se","sw"};
    string s;
    bool valid = false;
    cin >> s;
    
    for (string str : allowed){
        if (str == s){valid = true;}
    }
    
    if (!valid){
        cout << endl;
        cout << "Invalid Direction" << endl;
        return "null";
    }
    return s;
}

void runGame(std::unique_ptr<Game>& game){
    lineBreak();
    
    game->draw();
    
    string cmd = "null";
    string dir = "null";
    while (cmd == "null" || dir == "null"){
        cout << "Command: ";
        cmd = readCmd();
        if (cmd != "null"){
            dir = "valid";
        }
        if (cmd == "u" || cmd == "a" || cmd == "t"){
            dir = readDir();
        }
        // if shopDLC is not enabled then cmd t is disabled.
        if (cmd == "t" && shopDLC == false) {
            cout << endl;
            cout << "Invalid Command" << endl;
            cmd = "null";
            dir = "null";
        }
    }
    
    if (cmd == "q"){
        state = "Main Menu";
        game = std::make_unique<Game>(file);
    }else if (cmd == "r"){
        state = "Race Select";
        game = std::make_unique<Game>(file);
    }else{
        game->update(cmd, dir);
        if (game->hasWon()){
            state = "Win";
        }else if (game->hasLost()){
            state = "Lose";
        }
    }
}

void resetGrid(char (&grid)[79][25]){
    for (int y = 0; y < 25; y++){
        for (int x = 0; x < 79; x++){
            if (x == 0 || x == 78)
                grid[x][y] = '|';
            else if (y == 0 || y == 24)
                grid[x][y] = '-';
            else
                grid[x][y] = ' ';
        }
    }
}

void drawGrid(char grid[79][25]){
    cout << "   ";
    for (int x = 0; x < 79; x++){
        cout << std::to_string(x)[0];
    }
    cout << endl << "   ";
    for (int x = 0; x < 79; x++){
        cout << ((x > 9) ? std::to_string(x)[1] : ' ');
    }
    cout << endl;
    for (int y = 0; y < 25; y++){
        cout << y << ((y > 9) ? " " : "  ");
        for (int x = 0; x < 79; x++){
            cout << grid[x][y];
        }
        cout << endl;
    }
}

// used for the fill command
void traverseGrid(std::vector<Point>& arr, char (&grid)[79][25], Point p, char c){
    Point dirArr[4] = {Point(1,0), Point(-1,0), Point(0,1), Point(0,-1)};
    for (Point offset : dirArr){
        Point np{p.getX() + offset.getX(), p.getY() + offset.getY()};
        if (std::find(arr.begin(), arr.end(), np) == arr.end() && grid[np.getX()][np.getY()] == ((c == '*') ? ' ' : c)){
            arr.push_back(np);
            traverseGrid(arr, grid, np, c);
        }
    }
}

void runEditor(){
    char floors[5][79][25];     // [floor#][x][y]
    int floor = 0;
    resetGrid(floors[floor]);
    
    bool done = false;
    while(!done){
        lineBreak();
        drawGrid(floors[floor]);
        
        cout << "Floor: " << floor+1 << endl << endl;
        cout << "Use the command <set top bottom left right char> to create rectangles." << endl;
        cout << "--> Note 0 <= top <= bottom <= 24 and 0 <= left <= right <= 78, and char is a character." << endl;
        cout << "--> Input * to use whitespace." << endl;
        cout << "Use the command <next> to move on to the next floor." << endl;
        cout << "Use the command <copy> to copy the previous floor." << endl;
        cout << "Use the command <fill x y char> to fill a constrained area with the given character." << endl;
        cout << endl;
        cout << "[set/next/copy/fill/exit]: ";
        
        string choice;
        cin >> choice;
        
        if (choice == "set"){
            std::string top, bottom, left, right;
            char c;
            
            try {
                cin >> top;
                cin >> bottom;
                cin >> left;
                cin >> right;
                cin >> c;
                
                // setting the grid
                for (int y = std::stoi(top); y <= std::stoi(bottom); y++){
                    for (int x = std::stoi(left); x <= std::stoi(right); x++){
                        floors[floor][x][y] = (c == '*') ? ' ' : c;
                    }
                }
            } catch(std::invalid_argument&){}
        } else if (choice == "copy"){
            if (floor != 0){
                for (int y = 0; y < 25; y++){
                    for (int x = 0; x < 79; x++){
                        floors[floor][x][y] = floors[floor-1][x][y];
                    }
                }
            }
        } else if (choice == "fill"){
            string x, y;
            char c;
            cin >> x;
            cin >> y;
            cin >> c;
            
            try{
                std::vector<Point> points;
                traverseGrid(points, floors[floor], Point(std::stoi(x), std::stoi(y)), floors[floor][std::stoi(x)][std::stoi(y)]);
                for (Point p : points){
                    floors[floor][p.getX()][p.getY()] = (c == '*') ? ' ' : c;
                }
            } catch(std::invalid_argument&){}
        } else if (choice == "next"){
            floor++;
            if (floor == 5){
                done = true;
            }else{
                resetGrid(floors[floor]);
            }
        } else if (choice == "exit"){
            state = "DLC";
            break;
        }
    }
    
    // save floors
    if (done){
        lineBreak();
        cout << "What would you like the name the file?: ";
        string fileName;
        cin >> fileName;
        
        std::ofstream file;
        file.open(fileName + ".txt");
        
        for (int k = 0; k < 5; k ++){
            for (int y = 0; y < 25; y++){
                for (int x = 0; x < 79; x++){
                    file << floors[k][x][y];
                }
                file << endl;
            }
        }
        
        file.close();
        state = "DLC";
    }
}

int main(int argc, char *argv[])
{
    if (argc > 1){
        file = argv[1];
    }
    
    std::unique_ptr<Game> game;
    
    while (true){
        if (state == "Main Menu"){
            displayMainMenu();
        } else if (state == "Race Select"){
            game = std::make_unique<Game>(file);
            displayRaceSelect(game);
        } else if (state == "Play"){
            runGame(game);
        } else if (state == "Rules"){
            displayRules();
        } else if (state == "DLC"){
            displayDLC();
        } else if (state == "Editor"){
            runEditor();
        } else if (state == "Win"){
            lineBreak();
            cout << "Congratulations! You won with a score of " << game->getPlayer()->getGold() * ((game->getPlayer()->getRace() == "Shade") ? 1.5 : 1) << endl;
            state = "Main Menu";
        } else if (state == "Lose"){
            lineBreak();
            cout << "Better Luck Next Time! You lost with a score of " << game->getPlayer()->getGold() * ((game->getPlayer()->getRace() == "Shade") ? 1.5 : 1) << endl;
            state = "Main Menu";
        } else if (state == "Exit"){
            break;
        }
    }
    
    return 0;
}
