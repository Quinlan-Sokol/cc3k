# ifndef _FLOOR_H_
# define _FLOOR_H_
#include <vector>
#include <memory>
#include <map>
#include "point.h"
#include "enemy.h"

class Item;

class Floor{
    // class for storing information about each chamber
    class Chamber{
    public:
        std::vector<Point> area;
        Chamber(std::vector<Point> a);
        Point getRandPos();
        bool hasStart;
        bool contains(Point p);
    };
    std::vector<Point> traps;
    
    std::vector<Chamber> chambers;
    Point dirArr[4] = {Point(1,0), Point(-1,0), Point(0,1), Point(0,-1)};
    Point playerPos;
    
    bool validChar(char c);
    void createChambers();
    void traverseChamber(std::vector<Point>& arr, int x, int y);
    bool chambersContain(Point p);
    
    Point getRandPos(bool start=false, bool end=false);
    
    void loadEnemies();
    void loadItems();
    
    void createRandEnemy(Point pos = Point(-1, -1));
    
    // used for rng generation
    template<class T> void createEnemy(){
        enemies.push_back(std::make_shared<T>());
        enemies.back()->move(getRandPos());
    }
    
    // used for loading in files
    template<class T> void createEnemy(int x, int y){
        enemies.push_back(std::make_shared<T>());
        enemies.back()->move(Point(x, y));
    }
    
    void createGold();
    void createHoard(int x, int y);
    void createPotion();
public:
    char grid[79][25];
    Point startPos, endPos;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Item>> items;
    
    Point getClosestPoint(Point p);
    void createGold(int x, int y, int amount);
    void setPlayerPos(Point p);
    void agroMerchants();
    std::string checkTraps();
    
    Floor(char g[79][25], bool custom);
};
#endif
