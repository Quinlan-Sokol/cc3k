#include "shade.h"
#include "enemy.h"
#include "human.h"
#include "dwarf.h"
#include "elf.h"
#include "orc.h"
#include "merchant.h"
#include "dragon.h"
#include "halfling.h"
#include "random.h"

using namespace std;

Shade::Shade(): Player {125, 125, 25, 25, "Shade"} {}

string Shade::defend (shared_ptr<Enemy> & e) {
    return e->attack(*this);
}

string Shade::attack (Human & e) { 
    return doDamage(e);
}

string Shade::attack (Dwarf & e) {
    return doDamage(e);
}

string Shade::attack (Elf & e) {
    return doDamage(e);
}

string Shade::attack (Orc & e) {
    return doDamage(e);
}

string Shade::attack (Merchant & e) {
    return doDamage(e);
}

string Shade::attack (Dragon & e) {
    return doDamage(e);
}

string Shade::attack (Halfling & e) {
    if (Random::getRand(0,1) == 0) {
        return doDamage(e);
    }
    return "PC missed the " + e.getRace() + " (" + to_string(e.getHp()) + " HP) dealing 0 damage."; 
}