#include "orc.h"
#include "shade.h"
#include "drow.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"
#include "random.h"

using namespace std;

Orc::Orc(): Enemy {180, 30, 25, "Orc"} {}

string Orc::doDamage(Player & p) {
    if (isHostile() == false) return "";
    if (Random::getRand(0,1) == 0) {
        int damage = ceil((100/(100+static_cast<double>(p.getDef())))*(static_cast<double>(getAtk())));
        if (p.getRace() == "Goblin") damage *= 1.5;
        p.setHp(p.getHp() - damage);
        return getRace() + " deals " + to_string(damage) + " damage to PC."; 
    }
    return getRace() + " missed dealing no damage to PC."; 
}

string Orc::defend (unique_ptr<Player> & p) {
    return p->attack( *this);
}

string Orc::attack (Shade & p) { 
    return doDamage(p);
}

string Orc::attack (Drow & p) {
    return doDamage(p);
}

string Orc::attack (Vampire & p) {
    return doDamage(p);
}

string Orc::attack (Troll & p) {
    return doDamage(p);
}

string Orc::attack (Goblin & p) {
    return doDamage(p);
}