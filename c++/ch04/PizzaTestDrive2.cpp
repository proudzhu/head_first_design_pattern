#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "Pizza.h"
#include "CheesePizza.h"
#include "ClamPizza.h"
#include "PizzaIngredientFactory.h"

class PizzaStore
{
  public:
    std::unique_ptr<Pizza> orderPizza(std::string_view type)
    {
      std::unique_ptr<Pizza> pizza = createPizza(type);

      pizza->prepare();
      pizza->bake();
      pizza->cut();
      pizza->box();

      return pizza;
    }

  protected:
    virtual std::unique_ptr<Pizza> createPizza(std::string_view type) = 0;
};

class NYPizzaIngredientFactory :
  public PizzaIngredientFactory
{
  public:
    std::unique_ptr<Dough> createDough(void)
    {
      return std::make_unique<ThinCrustDough>();
    }

    std::unique_ptr<Sauce> createSauce(void)
    {
      return std::make_unique<MarinaraSauce>();
    }

    std::unique_ptr<Cheese> createCheese(void)
    {
      return std::make_unique<ReggianoCheese>();
    }

    std::vector<std::unique_ptr<Veggies>> createVeggies(void)
    {
      std::vector<std::unique_ptr<Veggies>> veggies;
      veggies.push_back(std::make_unique<Garlic>());
      veggies.push_back(std::make_unique<Onion>());
      veggies.push_back(std::make_unique<Mushroom>());
      veggies.push_back(std::make_unique<RedPepper>());
      return veggies;
    }

    std::unique_ptr<Pepperoni> createPepperoni(void)
    {
      return std::make_unique<SlicedPepperoni>();
    }

    std::unique_ptr<Clams> createClams(void)
    {
      return std::make_unique<FreshClams>();
    }
};

class NYPizzaStore :
  public PizzaStore
{
  protected:
    std::unique_ptr<Pizza> createPizza(std::string_view item) override
    {
      std::unique_ptr<Pizza> pizza = nullptr;
      std::unique_ptr<PizzaIngredientFactory> ingredientFactory = std::make_unique<NYPizzaIngredientFactory>();

      if (item == "cheese") {
        pizza = std::make_unique<CheesePizza>(std::move(ingredientFactory));
        pizza->setName("New York Style Cheese Pizza");
      }

      return pizza;
    }
};

class ChicagoPizzaIngredientFactory :
  public PizzaIngredientFactory
{
  public:
    std::unique_ptr<Dough> createDough(void)
    {
      return std::make_unique<ThickCrustDough>();
    }

    std::unique_ptr<Sauce> createSauce(void)
    {
      return std::make_unique<PlumTomatoSauce>();
    }

    std::unique_ptr<Cheese> createCheese(void)
    {
      return std::make_unique<MozzarellaCheese>();
    }

    std::vector<std::unique_ptr<Veggies>> createVeggies(void)
    {
      std::vector<std::unique_ptr<Veggies>> veggies;
      veggies.push_back(std::make_unique<BlackOilves>());
      veggies.push_back(std::make_unique<Spinach>());
      veggies.push_back(std::make_unique<EggPlant>());
      return veggies;
    }

    std::unique_ptr<Pepperoni> createPepperoni(void)
    {
      return std::make_unique<SlicedPepperoni>();
    }

    std::unique_ptr<Clams> createClams(void)
    {
      return std::make_unique<FrozenClams>();
    }
};

class ChicagoPizzaStore :
  public PizzaStore
{
  protected:
    std::unique_ptr<Pizza> createPizza(std::string_view item) override
    {
      std::unique_ptr<Pizza> pizza = nullptr;
      std::unique_ptr<PizzaIngredientFactory> ingredientFactory = std::make_unique<ChicagoPizzaIngredientFactory>();

      if (item == "cheese") {
        pizza = std::make_unique<CheesePizza>(std::move(ingredientFactory));
        pizza->setName("Chicago Style Cheese Pizza");
      }

      return pizza;
    }
};

int main(int argc, char **argv)
{
  auto nyStore = std::make_unique<NYPizzaStore>();
  auto chicagoStore = std::make_unique<ChicagoPizzaStore>();

  auto pizza = nyStore->orderPizza("cheese");
  std::cout << "Ethan ordered a " << pizza->getName() << "\n" << std::endl;

  pizza = chicagoStore->orderPizza("cheese");
  std::cout << "Joel ordered a " << pizza->getName() << "\n" << std::endl;

  return 0;
}
