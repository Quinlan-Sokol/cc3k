#ifndef _DEFPOTION_H_
#define _DEFPOTION_H_
#include "decorator.h"
#include "point.h"
#include <memory>

class TempPotion;
class Player;

class DefPotion: public Decorator {
    int power;
 public:
    DefPotion(Point pos, std::unique_ptr<TempPotion> component, int power);
    int getAtk() override;
    int getDef() override;
    bool onPickup (std::unique_ptr<Player> & p) override;
};

#endif