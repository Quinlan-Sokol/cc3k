# ifndef _HUMAN_H_
# define _HUMAN_H_
#include <string>
#include <memory>
#include "enemy.h"

class Player;
class Shade;
class Drow;
class Vampire;
class Troll;
class Goblin;

class Human : public Enemy {
public:
    Human();
    int dropGold() override;
    std::string defend (std::unique_ptr<Player> & p) override;
    std::string attack (Shade & p) override;
    std::string attack (Drow & p) override;
    std::string attack (Vampire & p) override;
    std::string attack (Troll & p) override;
    std::string attack (Goblin & p) override;
};

#endif