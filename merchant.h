# ifndef _MERCHANT_H_
# define _MERCHANT_H_
#include <string>
#include <memory>
#include "enemy.h"
#include "shop.h"

class Player;
class Shade;
class Drow;
class Vampire;
class Troll;
class Goblin;


class Merchant : public Enemy {
public:
    Merchant();
    int dropGold() override;
    std::unique_ptr<Shop> s;
    std::string defend (std::unique_ptr<Player> & p) override;
    std::string attack (Shade & p) override;
    std::string attack (Drow & p) override;
    std::string attack (Vampire & p) override;
    std::string attack (Troll & p) override;
    std::string attack (Goblin & p) override;
};

#endif