#include "dragon.h"
#include "shade.h"
#include "drow.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"
#include "random.h"

using namespace std;

Dragon::Dragon(): Enemy {150, 20, 20, "Dragon"} {}

int Dragon::dropGold() {
    return 0;
}

bool Dragon::inRange(Point p) {
    if (Enemy::inRange(p) == true) return true;
    for (Point p2 : hoardArea) {
        if (p2 == p) {
            return true;
        }
    }
    return false;
}

void Dragon::addHoardArea(Point p) {
    hoardArea.insert(hoardArea.begin(), p);
}

void Dragon::move(char g[79][25], Point pPos) {}

string Dragon::defend (unique_ptr<Player> & p) {
    return p->attack( *this);
}

string Dragon::attack (Shade & p) { 
    return doDamage(p);
}

string Dragon::attack (Drow & p) {
    return doDamage(p);
}

string Dragon::attack (Vampire & p) {
    return doDamage(p);
}

string Dragon::attack (Troll & p) {
    return doDamage(p);
}

string Dragon::attack (Goblin & p) {
    return doDamage(p);
}
