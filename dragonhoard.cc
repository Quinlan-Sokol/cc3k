#include "dragonhoard.h"
#include "player.h"
#include <iostream>

using namespace std;

Point range[9] = {Point(0,0), Point(1,0), Point(-1,0), Point(0,1), Point(0,-1), Point(1,1), Point(1,-1), Point(-1,1), Point(-1,-1)};

DragonHoard::DragonHoard(Point pos, std::shared_ptr<Dragon> owner): Gold {pos, 6}, owner {owner} {
    id = "Dragon Gold";
    for (Point offset : range) {   
        owner->addHoardArea(pos + offset);
    }
}

bool DragonHoard::onPickup(unique_ptr<Player> & p) {
    cout << owner.use_count() << endl;
    if (owner.use_count() == 1) {
        p->setGold(p->getGold() + amount);
        return true;
    }
    return false;
}
