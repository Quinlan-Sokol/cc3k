#ifndef _ATKPOTION_H_
#define _ATKPOTION_H_
#include "decorator.h"
#include "point.h"

class TempPotion;
class Player;

class AtkPotion: public Decorator {
    int power;
 public:
    AtkPotion(Point pos, std::unique_ptr<TempPotion> component, int power);
    int getAtk() override;
    int getDef() override;
    bool onPickup (std::unique_ptr<Player> & p) override;
};

#endif