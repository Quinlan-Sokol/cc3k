# ifndef _DECORATOR_H_
# define _DECORATOR_H_
#include "temppotion.h"
#include <memory>

class Decorator: public TempPotion {
protected:
    std::unique_ptr<TempPotion> component;
public:
    Decorator(std::unique_ptr<TempPotion> component);
    virtual ~Decorator();
};

#endif