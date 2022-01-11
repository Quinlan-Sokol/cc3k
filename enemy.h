# ifndef _ENEMY_H_
# define _ENEMY_H_
#include <string>
#include <vector>
#include <memory>
#include "point.h"

class Player;
class Shade;
class Drow;
class Vampire;
class Troll;
class Goblin;

class Enemy {
    int hp, atk, def;
    std::string race;
    Point position;
    bool hostile;
    bool alive;
    std::vector<Point> hostileArea;
    virtual void updateArea();
protected:
    virtual std::string doDamage(Player & p);
public:
    Enemy(int hp, int atk, int def, std::string race, bool hostile = true);
    virtual void move(char g[79][25], Point pPos);
    void move(Point pos);
    Point getPos();
    int getHp();
    int getDef();
    int getAtk();
    bool isHostile();
    bool isDead();
    void setHostile(bool);
    std::string getRace();
    void setHp(int hp);
    virtual int dropGold();
    virtual bool inRange(Point p);
    virtual std::string defend (std::unique_ptr<Player> & p) = 0;
    virtual std::string attack ( Shade & p) = 0;
    virtual std::string attack ( Drow & p) = 0;
    virtual std::string attack ( Vampire & p) = 0;
    virtual std::string attack ( Troll & p) = 0;
    virtual std::string attack ( Goblin & p) = 0;
};

#endif