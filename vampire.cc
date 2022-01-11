#include "vampire.h"
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

int lifeSteal = 5;

Vampire::Vampire(): Player {50, -1, 25, 25, "Vampire"} {}

string Vampire::defend (shared_ptr<Enemy> & e) {
    return e->attack( *this);
}

string Vampire::attack (Human & e) {
    this->setHp(this->getHp()+lifeSteal);
    return doDamage(e);
}

string Vampire::attack (Dwarf & e) {
    this->setHp(this->getHp()-lifeSteal);
    return doDamage(e);
}

string Vampire::attack (Elf & e) {
    this->setHp(this->getHp()+lifeSteal);
    return doDamage(e);
}

string Vampire::attack (Orc & e) {
    this->setHp(this->getHp()+lifeSteal);
    return doDamage(e);
}

string Vampire::attack (Merchant & e) {
    this->setHp(this->getHp()+lifeSteal);
    return doDamage(e);
}

string Vampire::attack (Dragon & e) {
    this->setHp(this->getHp()+lifeSteal);
    return doDamage(e);
}

string Vampire::attack (Halfling & e) {
    if (Random::getRand(0,1) == 0) {
        this->setHp(this->getHp()+lifeSteal);
        return doDamage(e);
    }
    return "PC missed the " + e.getRace() + " (" + to_string(e.getHp()) + " HP) dealing 0 damage."; 
}