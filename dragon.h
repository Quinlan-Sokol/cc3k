# ifndef _DRAGON_H_
# define _DRAGON_H_
#include <string>
#include <memory>
#include "enemy.h"

class Player;
class Shade;
class Drow;
class Vampire;
class Troll;
class Goblin;


class Dragon : public Enemy {
    std::vector<Point> hoardArea;
public:
    Dragon();
    bool inRange(Point p) override;
    void addHoardArea(Point p);
    int dropGold() override;
    void move(char g[79][25], Point pPos) override;
    std::string defend (std::unique_ptr<Player> & p) override;
    std::string attack (Shade & p) override;
    std::string attack (Drow & p) override;
    std::string attack (Vampire & p) override;
    std::string attack (Troll & p) override;
    std::string attack (Goblin & p) override;
};

#endif