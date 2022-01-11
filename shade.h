# ifndef _SHADE_H_
# define _SHADE_H_
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

class Shade : public Player {
public:
    Shade();
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
