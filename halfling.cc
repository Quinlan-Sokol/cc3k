#include "halfling.h"
#include "shade.h"
#include "drow.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"
#include "random.h"

using namespace std;

Halfling::Halfling(): Enemy {100, 15, 20, "Halfling"} {}

string Halfling::defend (unique_ptr<Player> & p) {
    return p->attack( *this);
}

string Halfling::attack (Shade & p) { 
    return doDamage(p);
}

string Halfling::attack (Drow & p) {
    return doDamage(p);
}

string Halfling::attack (Vampire & p) {
    return doDamage(p);
}

string Halfling::attack (Troll & p) {
    return doDamage(p);
}   

string Halfling::attack (Goblin & p) {
    return doDamage(p);
}