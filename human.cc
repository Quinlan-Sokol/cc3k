#include "human.h"
#include "shade.h"
#include "drow.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"
#include "random.h"

using namespace std;

Human::Human(): Enemy {140, 20, 20, "Human"} {}

int Human::dropGold() {
    return 0;
}

string Human::defend (unique_ptr<Player> & p) {
    return p->attack( *this);
}

string Human::attack (Shade & p) {
    return doDamage(p);
}

string Human::attack (Drow & p) {
    return doDamage(p);
}

string Human::attack (Vampire & p) {
    return doDamage(p);
}

string Human::attack (Troll & p) {
    return doDamage(p);
}

string Human::attack (Goblin & p) {
    return doDamage(p);
}