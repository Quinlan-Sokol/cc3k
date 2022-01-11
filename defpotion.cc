#include "defpotion.h"
#include "temppotion.h"
#include "player.h"
#include <memory>

using namespace std;

DefPotion::DefPotion(Point pos, unique_ptr<TempPotion> component, int power):  Decorator { move(component) }, power {power} {
    position = pos;
    id = string((power > 0) ? "+" : "-") + "Def Potion";
}

int DefPotion::getAtk() {
    return component->getAtk();
}

int DefPotion::getDef() {
    return component->getDef() + power;
}

bool DefPotion::onPickup(unique_ptr<Player> & p) {
    if (p->getRace() == "Drow") power *= 1.5;
    auto newPotion = make_unique<DefPotion>(position, p->getPotions(), power );
    p->addPotion( static_cast<unique_ptr<TempPotion>>(move(newPotion)) );
    return true;
}
