#include "item.h"

Point Item::getPos() {
    return position;
}

std::string Item::getId() {
    return id;
}

Item::~Item() {}