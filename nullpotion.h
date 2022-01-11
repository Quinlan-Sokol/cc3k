#ifndef _NULLPOTION_H_
#define _NULLPOTION_H_
#include "temppotion.h"
#include <memory>

class Player;

class NullPotion: public TempPotion {
 public:
    NullPotion();
    int getAtk() override;
    int getDef() override;
    bool onPickup (std::unique_ptr<Player> & p) override;
};

#endif