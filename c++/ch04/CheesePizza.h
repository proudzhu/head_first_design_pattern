#ifndef CHEESEPIZZA_H
#define CHEESEPIZZA_H

#include <memory>
#include <iostream>
#include "Pizza.h"
#include "PizzaIngredientFactory.h"

class CheesePizza :
  public Pizza
{
  public:
    CheesePizza(std::unique_ptr<PizzaIngredientFactory> ingredientFactory)
    {
      ingredientFactory_ = std::move(ingredientFactory);
    }

    void prepare()
    {
      std::cout << "Preparing " << name_ << std::endl;
      dough_ = ingredientFactory_->createDough();
      sauce_ = ingredientFactory_->createSauce();
      cheese_ = ingredientFactory_->createCheese();
    }

  private:
    std::unique_ptr<PizzaIngredientFactory> ingredientFactory_;
};

#endif
