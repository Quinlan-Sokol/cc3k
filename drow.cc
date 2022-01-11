#include "drow.h"
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

Drow::Drow(): Player {150, 150, 25, 15, "Drow"} {}

string Drow::defend (shared_ptr<Enemy> & e) {
    return e->attack( *this);
}

string Drow::attack (Human & e) { 
    return doDamage(e);
}

string Drow::attack (Dwarf & e) {
    return doDamage(e);
}

string Drow::attack (Elf & e) {
    return doDamage(e);
}

string Drow::attack (Orc & e) {
    return doDamage(e);
}

string Drow::attack (Merchant & e) {
    return doDamage(e);
}

string Drow::attack (Dragon & e) {
    return doDamage(e);
}

string Drow::attack (Halfling & e) {
    if (Random::getRand(0,1) == 0) {
        return doDamage(e);
    }
    return "PC missed the " + e.getRace() + " (" + to_string(e.getHp()) + " HP) dealing 0 damage."; 
}