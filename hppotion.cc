#include "hppotion.h"
#include "player.h"

using namespace std;

HpPotion::HpPotion(Point pos, int power): power {power} {
    position = pos;
    id = string((power > 0) ? "+" : "-") + "Hp Potion";
}

bool HpPotion::onPickup(unique_ptr<Player> & p) {
    if (p->getRace() == "Drow") power *= 1.5;
    p->setHp(p->getHp() + power);
    return true;
}
