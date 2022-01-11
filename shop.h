# ifndef _SHOP_H_
# define _SHOP_H_
# include "item.h"
# include "player.h"
# include <memory>
# include <vector>
# include <string>

class Shop {
    std::vector<std::unique_ptr<Item>> items;
    std::vector<int> cost;
    std::vector<std::string> description;
public:
    Shop();
    std::string buy(int index, std::unique_ptr<Player> & p);
    std::string view();
};

#endif