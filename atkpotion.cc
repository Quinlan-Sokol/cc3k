#include "atkpotion.h"
#include "temppotion.h"
#include "player.h"
#include <memory>

using namespace std;

AtkPotion::AtkPotion(Point pos, unique_ptr<TempPotion> component, int power): Decorator { move(component) }, power {power} {
    position = pos;
    id = string((power > 0) ? "+" : "-") + "Atk Potion";
}

int AtkPotion::getAtk() {
    return component->getAtk() + power;
}

int AtkPotion::getDef() {
    return component->getDef();
}

bool AtkPotion::onPickup(unique_ptr<Player> & p) {
    if (p->getRace() == "Drow") power *= 1.5;
    auto newPotion = make_unique<AtkPotion>(position, p->getPotions(), power);
    p->addPotion( static_cast<unique_ptr<TempPotion>>(move(newPotion)) );
    return true;
}
