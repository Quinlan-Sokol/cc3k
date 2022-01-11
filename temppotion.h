# ifndef _TEMPPOTION_H_
# define _TEMPPOTION_H_
#include "item.h"

class TempPotion: public Item {
public:
    virtual int getAtk() = 0;
    virtual int getDef() = 0;
    virtual ~TempPotion();
};

#endif