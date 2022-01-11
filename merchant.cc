#include "merchant.h"
#include "player.h"
#include "shade.h"
#include "drow.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"
#include "random.h"
#include "shop.h"

using namespace std;

Merchant::Merchant(): Enemy {30, 70, 5, "Merchant", false}, s {make_unique<Shop>()} {}

int Merchant::dropGold() {
    return 0;
}

string Merchant::defend (unique_ptr<Player> & p) {
    return p->attack( *this);
}

string Merchant::attack (Shade & p) { 
    return doDamage(p);
}

string Merchant::attack (Drow & p) {
    return doDamage(p);
}

string Merchant::attack (Vampire & p) {
    return doDamage(p);
}

string Merchant::attack (Troll & p) {
    return doDamage(p);
}

string Merchant::attack (Goblin & p) {
    return doDamage(p);
}