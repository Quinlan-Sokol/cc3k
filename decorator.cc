#include "decorator.h"

using namespace std;

Decorator::Decorator(unique_ptr<TempPotion> component): component {move(component)} {}

Decorator::~Decorator() {}