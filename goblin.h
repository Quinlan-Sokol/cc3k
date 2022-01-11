# ifndef _GOBLIN_H_
# define _GOBLIN_H_
#include <string>
#include <memory>
#include "player.h"

class Enemy;
class Human;
class Dwarf;
class Elf;
class Orc;
class Merchant;
class Dragon;
class Halfling;

class Goblin : public Player {
protected:
    std::string doDamage(Enemy & e) override;
public:
    Goblin();
    std::string defend (std::shared_ptr<Enemy> & e) override;
    std::string attack (Human & e) override;
    std::string attack (Dwarf & e) override;
    std::string attack (Elf & e) override;
    std::string attack (Orc & e) override;
    std::string attack (Merchant & e) override;
    std::string attack (Dragon & e) override;
    std::string attack (Halfling & e) override;
};

#endif
