#include "troll.h"
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

Troll::Troll(): Player {120, 120, 25, 15, "Troll"} {}

string Troll::defend (shared_ptr<Enemy> & e) {
    return e->attack( *this);
}

string Troll::attack (Human & e) { 
    return doDamage(e);
}

string Troll::attack (Dwarf & e) {
    return doDamage(e);
}

string Troll::attack (Elf & e) {
    return doDamage(e);
}

string Troll::attack (Orc & e) {
    return doDamage(e);
}

string Troll::attack (Merchant & e) {
    return doDamage(e);
}

string Troll::attack (Dragon & e) {
    return doDamage(e);
}

string Troll::attack (Halfling & e) {
    if (Random::getRand(0,1) == 0) {
        return doDamage(e);
    }
    return "PC missed the " + e.getRace() + " (" + to_string(e.getHp()) + " HP) dealing 0 damage."; 
}