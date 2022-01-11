#include "nullpotion.h"
#include "player.h"
#include "point.h"

using namespace std;

NullPotion::NullPotion() {
    position = Point (0,0);
    id = "Null Potion";
}

int NullPotion::getAtk() {
    return 0;
}

int NullPotion::getDef() {
    return 0;
}

bool NullPotion::onPickup(unique_ptr<Player> & p) {return true;}