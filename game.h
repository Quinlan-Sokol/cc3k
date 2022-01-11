# ifndef _GAME_H_
# define _GAME_H_
#include <vector>
#include <unordered_set>
#include <string>
#include <memory>
#include <map>
#include "floor.h"
#include "player.h"
#include "point.h"

class Game{
    int curFloor;
    bool win;
    bool lose;
    bool moveEnemies;
    static bool flashlightOn;
    static bool trapsOn;
    std::string messageBuffer;
    std::string floorFile;
    std::unordered_set<std::string> knownPotions;
    std::vector<Point> fPoints;
    std::vector<Floor> floors;
    std::unique_ptr<Player> player;
    std::string collectItem(Point targetPos, std::string type);
    void updateEnemies();
    void detectPotions();
    void setFPoints();
public:
    Game(std::string file);
    void update(std::string cmd, std::string dir);
    void draw();
    void createFloors();
    void setRace(char c);
    void progress();
    
    static void toggleFlashlight();
    static bool isFlashlightOn();
    
    static void toggleTraps();
    static bool areTrapsOn();
    
    bool hasWon();
    bool hasLost();
    std::unique_ptr<Player>& getPlayer();
};

# endif
