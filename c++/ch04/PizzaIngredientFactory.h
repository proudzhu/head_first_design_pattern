#ifndef PIZZA_INGREDIENT_FACTORY_H
#define PIZZA_INGREDIENT_FACTORY_H

#include <vector>
#include <memory>
#include "Dough.h"
#include "Sauce.h"
#include "Cheese.h"
#include "Veggies.h"
#include "Pepperoni.h"
#include "Clams.h"

class PizzaIngredientFactory
{
  public:
    virtual std::unique_ptr<Dough> createDough() = 0;
    virtual std::unique_ptr<Sauce> createSauce() = 0;
    virtual std::unique_ptr<Cheese> createCheese() = 0;
    virtual std::vector<std::unique_ptr<Veggies>> createVeggies() = 0;
    virtual std::unique_ptr<Pepperoni> createPepperoni() = 0;
    virtual std::unique_ptr<Clams> createClams() = 0;
};

#endif
