#include "dwarf.h"
#include "shade.h"
#include "drow.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"
#include "random.h"

using namespace std;

Dwarf::Dwarf(): Enemy {100, 20, 30, "Dwarf"} {}

string Dwarf::defend (unique_ptr<Player> & p) {
    return p->attack( *this);
}

string Dwarf::attack (Shade & p) { 
    return doDamage(p);
}

string Dwarf::attack (Drow & p) {
    return doDamage(p);
}

string Dwarf::attack (Vampire & p) {
    return doDamage(p);
}

string Dwarf::attack (Troll & p) {
    return doDamage(p);
}

string Dwarf::attack (Goblin & p) {
    return doDamage(p);
}