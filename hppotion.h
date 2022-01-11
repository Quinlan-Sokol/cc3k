# ifndef _HPPOTION_H_
# define _HPPOTION_H_
#include "item.h"
#include "point.h"
#include <memory>

class Player;

class HpPotion: public Item {
    int power;
public:
    HpPotion(Point pos, int power);
    bool onPickup (std::unique_ptr<Player> & p) override;
};

#endif