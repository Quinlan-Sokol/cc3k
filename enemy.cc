#include "enemy.h"
#include "player.h"
#include "point.h"
#include "random.h"

using namespace std;

Point directions[8] = {Point(1,0), Point(-1,0), Point(0,1), Point(0,-1), Point(1,1), Point(1,-1), Point(-1,1), Point(-1,-1)};

void Enemy::updateArea() {
    hostileArea.clear();
    for (Point offset : directions) {   
        hostileArea.push_back(position + offset);
    }
}

Enemy::Enemy (int hp, int atk, int def, string race, bool hostile): hp {hp}, atk {atk}, def {def}, race {race}, position { Point {0,0} }, hostile {hostile}, alive {true} {
    updateArea();
}

void Enemy::move(char g[79][25], Point pPos) {
    Point dir;
    int counter = 50;
    do {
        counter--;
        dir = directions[Random::getRand(0,7)];
        if (counter == 0) {
            dir = Point(0,0);
            break;
        }
    } while(g[(position+dir).getX()][(position+dir).getY()] != '.' ||
        pPos == (position+dir));
    position = position + dir;
    updateArea();
}

void Enemy::move( Point pos ) {
    // update position
    position = pos;
    // update hostile area
    updateArea();
}

Point Enemy::getPos() {
    return position;
}

int Enemy::getHp() {
    return hp;
}

int Enemy::getDef() {
    return def;
}
int Enemy::getAtk() {
    return atk;
}

bool Enemy::isHostile() {
    return hostile;
}

bool Enemy::isDead() {
    return !alive;
}

void Enemy::setHostile(bool x) {
    hostile = x;
}

string Enemy::getRace() {
    return race;
}

void Enemy::setHp(int hp) {
    if (hp <= 0) {
        this->hp = 0;
        alive = false;
        return;
    }
    alive = true;
    this->hp = hp;
}

string Enemy::doDamage(Player & p) {
    if (hostile == false) return "";
    if (Random::getRand(0,1) == 0) {
        int damage = ceil((100/(100+static_cast<double>(p.getDef())))*(static_cast<double>(atk)));
        p.setHp(p.getHp() - damage);
        return getRace() + " deals " + to_string(damage) + " damage to PC."; 
    }
    return getRace() + " missed dealing no damage to PC."; 
}

int Enemy::dropGold() {
    if (Random::getRand(0,1) == 0) {
        return 1;
    } else {
        return 2;
    }
}

bool Enemy::inRange(Point p) {
    for (Point p2 : hostileArea) {
        if (p2 == p) {
            return true;
        }
    }
    return false;
}