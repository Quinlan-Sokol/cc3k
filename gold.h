# ifndef _GOLD_H_
# define _GOLD_H_
# include "item.h"
# include <memory>
# include "point.h"

class Player;

class Gold : public Item {
protected:
    int amount;
public:
    Gold(Point pos, int amount);
    virtual bool onPickup (std::unique_ptr<Player> & p) override;
};

#endif