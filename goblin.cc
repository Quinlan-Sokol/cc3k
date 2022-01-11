#include "goblin.h"
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

Goblin::Goblin(): Player {110, 110, 15, 20, "Goblin"} {}

string Goblin::doDamage(Enemy & e) {
    int damage = ceil((100/(100+static_cast<double>(e.getDef())))*(static_cast<double>(getAtk())));
    e.setHp(e.getHp() - damage);
    if (e.isDead()) {
        int amount = e.dropGold() + 5;
        setGold(getGold() + amount);
        return "PC deals " + to_string(damage) + " damage to " + e.getRace() +  " (" + to_string(e.getHp()) + " HP) killing it.";
    }
    return "PC deals " + to_string(damage) + " damage to " + e.getRace() +  " (" + to_string(e.getHp()) + " HP)."; 
}

string Goblin::defend (shared_ptr<Enemy> & e) {
    return e->attack( *this);
}

string Goblin::attack (Human & e) { 
    return doDamage(e);
}

string Goblin::attack (Dwarf & e) {
    return doDamage(e);
}

string Goblin::attack (Elf & e) {
    return doDamage(e);
}

string Goblin::attack (Orc & e) {
    return doDamage(e);
}

string Goblin::attack (Merchant & e) {
    return doDamage(e);
}

string Goblin::attack (Dragon & e) {
    return doDamage(e);
}

string Goblin::attack (Halfling & e) {
    if (Random::getRand(0,1) == 0) {
        return doDamage(e);
    }
    return "PC missed the " + e.getRace() + " (" + to_string(e.getHp()) + " HP) dealing 0 damage."; 
}