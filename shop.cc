#include "shop.h"
#include "random.h"
#include "hppotion.h"
#include "atkpotion.h"
#include "defpotion.h"
#include "point.h"

using namespace std;

string options[4] = {"no", "ea", "so", "we"};

string createDesc(int value, string type) {
    if (abs(value) > 10) {
        return "Powerful " + type + " Potion (Power: " + to_string(value) + ")";  
    } else if (abs(value) <= 10 && abs(value) > 5) {
        return "Mediocre " + type + " Potion (Power: " + to_string(value) + ")"; 
    } else if (abs(value) <= 5 && abs(value) > 0) {
        return "Weak " + type + " Potion (Power: " + to_string(value) + ")"; 
    } else if (abs(value) == 0) {
        return "Potion of Nullness (?\?\?)";
    }
    return "";
}

Shop::Shop() {
    for (int i = 0; i < 3; i++) {
        int random = Random::getRand(0,2);
        if (random == 0) {
            int power = Random::getRand(-15,30);
            items.emplace_back(std::make_unique<HpPotion>(Point (0,0), power) );
            cost.emplace_back((abs(power) / 5) + 2);
            description.emplace_back(createDesc(power, "HP"));
        } else if (random == 1) {
            int power = Random::getRand(-11,15);
            items.emplace_back(std::make_unique<AtkPotion>(Point (0,0), nullptr, power));
            cost.emplace_back((abs(power) / 3) + 3);
            description.emplace_back(createDesc(power, "ATK"));
        } else if (random == 2) {
            int power = Random::getRand(-11,15);
            items.emplace_back(std::make_unique<DefPotion>(Point (0,0), nullptr, power));
            cost.emplace_back((abs(power) / 3) + 3);
            description.emplace_back(createDesc(power, "DEF"));
        }
    }
    items.emplace_back(nullptr);
    cost.emplace_back(15);
    description.emplace_back("Reset Stats Potion");
}

// outputs item in shop
string Shop::view() {
    string output = "\nWelcome to the Shop! What would you like to buy?\n";
    for (int i = 0; i < static_cast<int>(cost.size()); i++) {
        output += "[" + options[i] + "] " + description.at(i) + " Cost: " + to_string(cost.at(i)) + " gold\n";
    }
    return output;
}

// attempts to buy item at index for player p
string Shop::buy(int index, unique_ptr<Player> & p) {
    if (index >= static_cast<int>(cost.size())) {
        return "\nNo item exists at that position. Please pick another item.\n";
    } else if (cost[index] > p->getGold()) {
        return "\nYou have insufficient funds to buy this item.\n";
    }
    if (description[index] == "Reset Stats Potion") {
        p->resetPotions();
    } else {
        items[index]->onPickup(p);
    }
    p->setGold(p->getGold() - cost[index]);
    items.erase(items.begin()+index);
    cost.erase(cost.begin()+index);
    description.erase(description.begin()+index);
    return "\nThank you for buying that potion! Would you like anything else?\n";
}
