# ifndef _PLAYER_H_
# define _PLAYER_H_
#include <string>
#include <vector>
#include <memory>
#include "temppotion.h"
#include "point.h"

class Enemy;
class Human;
class Dwarf;
class Elf;
class Orc;
class Merchant;
class Dragon;
class Halfling;

class Player {
    int hp, maxHp, atk, def, gold;
    std::string race;
    std::unique_ptr<TempPotion> potions;
    Point position;
protected:
    virtual std::string doDamage(Enemy & e);
public:
    Player(int hp, int maxHp, int atk, int def, std::string race);
    void move(Point pos);
    Point getPos();
    void addPotion(std::unique_ptr<TempPotion> p);
    std::unique_ptr<TempPotion> getPotions();
    void resetPotions();
    int getAtk();
    int getDef();
    int getHp();
    int getGold();
    std::string getRace();
    void setHp(int hp);
    void setGold(int gold);
    virtual std::string defend (std::shared_ptr<Enemy> & e) = 0;
    virtual std::string attack (Human & e) = 0;
    virtual std::string attack (Dwarf & e) = 0;
    virtual std::string attack (Elf & e) = 0;
    virtual std::string attack (Orc & e) = 0;
    virtual std::string attack (Merchant & e) = 0;
    virtual std::string attack (Dragon & e) = 0;
    virtual std::string attack (Halfling & e) = 0;
};

#endif
