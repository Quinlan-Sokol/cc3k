#include "elf.h"
#include "shade.h"
#include "drow.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"
#include "random.h"

using namespace std;

Elf::Elf(): Enemy {140, 30, 10, "Elf"} {}

string Elf::doDamage(Player & p) {
    if (isHostile() == false) return "";
    int one = Random::getRand(0,1);
    int two = Random::getRand(0,1);
    if (one + two == 0){
        return getRace() + " missed twice dealing no damage to PC."; 
    }
    int damage = ceil((100/(100+static_cast<double>(p.getDef())))*(static_cast<double>(getAtk())));
    p.setHp(p.getHp() - (one+two)*damage);
    return getRace() + " hits PC " + to_string(one+two) +" time(s)! dealing " + to_string((one+two)*damage) + " damage to PC."; 
}

string Elf::defend (unique_ptr<Player> & p) {
    return p->attack( *this);
}

string Elf::attack (Shade & p) { 
    return doDamage(p);
}

string Elf::attack (Drow & p) {
    return Enemy::doDamage(p);
}

string Elf::attack (Vampire & p) {
    return doDamage(p);
}

string Elf::attack (Troll & p) {
    return doDamage(p);
}

string Elf::attack (Goblin & p) {
    return doDamage(p);
}