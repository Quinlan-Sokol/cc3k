# ifndef _ITEM_H_
# define _ITEM_H_
#include <memory>
#include <string>
#include "point.h"

class Player;

class Item {
protected:
    Point position;
    std::string id;
public:
    Point getPos();
    std::string getId();
    virtual bool onPickup (std::unique_ptr<Player> & p) = 0;
    virtual ~Item();
};

#endif