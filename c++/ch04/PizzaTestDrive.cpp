#include <string>
#include <vector>
#include <memory>
#include <iostream>

class Pizza
{
  public:
    virtual void prepare()
    {
      std::cout << "Preparing " << name_ << std::endl;
      std::cout << "Tossing dough..." << std::endl;
      std::cout << "Add sauce..." << std::endl;
      std::cout << "Add toppings: " << std::endl;
      for (auto s : toppings_)
        std::cout << "   " << s << std::endl;
    }

    virtual void bake()
    {
      std::cout << "Bake for 25 minutes at 350" << std::endl;
    }

    virtual void cut()
    {
      std::cout << "Cutting the pizza into diagonal slices" << std::endl;
    }

    virtual void box()
    {
      std::cout << "Place pizza in official PizzaStore box" << std::endl;
    }

    std::string getName()
    {
      return name_;
    }

    protected:
      std::string name_;
      std::string dough_;
      std::string sauce_;
      std::vector<std::string> toppings_;
};

class NYStyleCheesePizza :
  public Pizza
{
  public:
    NYStyleCheesePizza()
    {
      name_ = "NY Style Sauce and Cheese Pizza";
      dough_ = "Thin Crust Dough";
      sauce_ = "Marinara Sauce";

      toppings_.push_back("Grated Reggiano Cheese");
    }

    ~NYStyleCheesePizza()
    { }
};

class ChicagoStyleCheesePizza :
  public Pizza
{
  public:
    ChicagoStyleCheesePizza()
    {
      name_ = "Chicago Style Deep Dish and Cheese Pizza";
      dough_ = "Extra Thick Crust Dough";
      sauce_ = "Plum Tomato Sauce";

      toppings_.push_back("Shredded Mozzarella Cheese");
    }

    void cut()
    {
      std::cout << "Cutting the pizza into square slices" << std::endl;
    }

    ~ChicagoStyleCheesePizza()
    { }
};

class PizzaStore
{
  public:
    std::unique_ptr<Pizza> orderPizza(std::string type)
    {
      std::unique_ptr<Pizza> pizza = createPizza(type);

      pizza->prepare();
      pizza->bake();
      pizza->cut();
      pizza->box();

      return pizza;
    }

  protected:
    virtual std::unique_ptr<Pizza> createPizza(std::string type) = 0;
};

class NYPizzaStore :
  public PizzaStore
{
  protected:
    std::unique_ptr<Pizza> createPizza(std::string item) override
    {
      if (item == std::string("cheese"))
        return std::make_unique<NYStyleCheesePizza>();
      else
        return nullptr;
    }
};

class ChicagoPizzaStore :
  public PizzaStore
{
  protected:
    std::unique_ptr<Pizza> createPizza(std::string item) override
    {
      if (item == std::string("cheese"))
        return std::make_unique<ChicagoStyleCheesePizza>();
      else
        return nullptr;
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
