#ifndef CLAM_PIZZA_H
#define CLAM_PIZZA_H

#include <memory>
#include <iostream>
#include "Pizza.h"
#include "PizzaIngredientFactory.h"

class ClamPizza :
  public Pizza
{
  public:
    ClamPizza(std::unique_ptr<PizzaIngredientFactory> ingredientFactory)
    {
      ingredientFactory_ = std::move(ingredientFactory);
    }

    void prepare()
    {
      std::cout << "Preparing " << name_ << std::endl;
      dough_ = ingredientFactory_->createDough();
      sauce_ = ingredientFactory_->createSauce();
      cheese_ = ingredientFactory_->createCheese();
      clam_ = ingredientFactory_->createClams();
    }

  private:
    std::unique_ptr<PizzaIngredientFactory> ingredientFactory_;
};

#endif
