#include "gold.h"
#include "player.h"

using namespace std;

Gold::Gold(Point pos, int amount):amount {amount} {
    position = pos;
    id = "Gold";
}

bool Gold::onPickup(unique_ptr<Player> & p) {
    p->setGold(p->getGold() + amount);
    return true;
}