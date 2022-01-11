#include "player.h"
#include "nullpotion.h"
#include "temppotion.h"
#include "enemy.h"
#include <memory>
#include <cmath>

using namespace std;

Player::Player (int hp, int maxHp, int atk, int def, string race):
    hp {hp}, maxHp {maxHp}, atk {atk}, def {def}, gold {0}, race {race}, position { Point {0,0} } {
    potions = make_unique<NullPotion>();
}

void Player::addPotion(unique_ptr<TempPotion> p) {
    potions = std::move(p);
}

unique_ptr<TempPotion> Player::getPotions() {
    return std::move(potions);
}

void Player::resetPotions() {
    potions = make_unique<NullPotion>();
}

int Player::getAtk() {
    int totalAtk = atk + potions->getAtk();
    if (totalAtk < 0) return 0;
    return totalAtk;
}

int Player::getDef() {
    int totalDef = def + potions->getDef();
    if (totalDef < 0) return 0;
    return totalDef;
}

int Player::getHp(){
    return hp;
}

int Player::getGold(){
    return gold;
}

string Player::getRace() {
    return race;
}

void Player::setHp(int hp){
    this->hp = hp;
    if (hp < 0) {
        this->hp = 0;
    } else if (hp > maxHp && maxHp > 0) {
        this->hp = maxHp;
    }
}

void Player::setGold(int gold){
    this->gold = gold;
}

void Player::move( Point pos ) {
    position = pos;
}

Point Player::getPos() {
    return position;
}

string Player::doDamage(Enemy & e) {
    int damage = ceil((100/(100+static_cast<double>(e.getDef())))*(static_cast<double>(atk)));
    e.setHp(e.getHp() - damage);
    if (e.isDead()) {
        int amount = e.dropGold();
        gold += amount;
        return "PC deals " + to_string(damage) + " damage to " + e.getRace() +  " (" + to_string(e.getHp()) + " HP) killing it.";
    }
    return "PC deals " + to_string(damage) + " damage to " + e.getRace() +  " (" + to_string(e.getHp()) + " HP)."; 
}
