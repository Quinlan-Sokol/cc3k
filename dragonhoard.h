# ifndef _DRAGONHOARD_H_
# define _DRAGONHOARD_H_
#include <memory>
#include <string>
#include "point.h"
#include "gold.h"
#include "dragon.h"

class Player;

class DragonHoard : public Gold {
    std::shared_ptr<Dragon> owner;
public:
    DragonHoard(Point pos, std::shared_ptr<Dragon> owner);
    bool onPickup (std::unique_ptr<Player> & p) override;
};

#endif
