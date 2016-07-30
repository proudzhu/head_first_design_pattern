#include <string>
#include <memory>
#include <iostream>

class Beverage
{
  public:
    virtual std::string getDescription()
    {
      return description;
    }

    virtual double cost() = 0;

  protected:
    std::string description = "Unknown Beverage";
};

class CondimentDecorator :
  public Beverage
{
  public:
    virtual std::string getDescription() = 0;

  protected:
    std::unique_ptr<Beverage> beverage_;
};

class Espresso :
  public Beverage
{
  public:
    Espresso()
    {
      description = "Espresso";
    }

    ~Espresso()
    { }

    virtual double cost()
    {
      return 1.99;
    }
};

class HouseBlend :
  public Beverage
{
  public:
    HouseBlend()
    {
      description = "House Blend Coffee";
    }

    ~HouseBlend()
    { }

    virtual double cost()
    {
      return 0.89;
    }
};

class DarkRoast :
  public Beverage
{
  public:
    DarkRoast()
    {
      description = "Dark Roast Coffee";
    }

    ~DarkRoast()
    { }

    virtual double cost()
    {
      return 0.99;
    }
};

class Mocha :
  public CondimentDecorator
{
  public:
    Mocha(std::unique_ptr<Beverage> br)
    {
      beverage_ = std::move(br);
    }

    ~Mocha()
    { }

    std::string getDescription() override
    {
      return beverage_->getDescription() + ", Mocha";
    }

    double cost() override
    {
      return 0.20 + beverage_->cost();
    }
};

class Whip :
  public CondimentDecorator
{
  public:
    Whip(std::unique_ptr<Beverage> br)
    {
      beverage_ = std::move(br);
    }

    ~Whip()
    { }

    std::string getDescription() override
    {
      return beverage_->getDescription() + ", Whip";
    }

    double cost() override
    {
      return 0.10 + beverage_->cost();
    }
};

class Soy :
  public CondimentDecorator
{
  public:
    Soy(std::unique_ptr<Beverage> br)
    {
      beverage_ = std::move(br);
    }

    ~Soy()
    { }

    std::string getDescription() override
    {
      return beverage_->getDescription() + ", Soy";
    }

    double cost() override
    {
      return 0.15 + beverage_->cost();
    }
};

int main(int argc, char **argv)
{
  std::unique_ptr<Beverage> beverage = std::make_unique<Espresso>();
  std::cout << beverage->getDescription() << " $" << beverage->cost() << std::endl;

  std::unique_ptr<Beverage> beverage2 = std::make_unique<DarkRoast>();
  beverage2 = std::make_unique<Mocha>(std::move(beverage2));
  beverage2 = std::make_unique<Mocha>(std::move(beverage2));
  beverage2 = std::make_unique<Whip>(std::move(beverage2));
  std::cout << beverage2->getDescription() << " $" << beverage2->cost() << std::endl;

  std::unique_ptr<Beverage> beverage3 = std::make_unique<HouseBlend>();
  beverage3 = std::make_unique<Soy>(std::move(beverage3));
  beverage3 = std::make_unique<Mocha>(std::move(beverage3));
  beverage3 = std::make_unique<Whip>(std::move(beverage3));
  std::cout << beverage3->getDescription() << " $" << beverage3->cost() << std::endl;

  return 0;
}
