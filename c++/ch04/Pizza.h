#ifndef PIZZA_H
#define PIZZA_H

#include <vector>
#include <memory>
#include <iostream>
#include "Dough.h"
#include "Sauce.h"
#include "Veggies.h"
#include "Cheese.h"
#include "Pepperoni.h"
#include "Clams.h"

class Pizza
{
  public:
    virtual void prepare() = 0;

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

    void setName(std::string name)
    {
      name_ = name;
    }

    std::string getName()
    {
      return name_;
    }

    protected:
      std::string name_;
      std::unique_ptr<Dough> dough_;
      std::unique_ptr<Sauce> sauce_;
      std::vector<std::unique_ptr<Veggies>> veggies_;
      std::unique_ptr<Cheese> cheese_;
      std::unique_ptr<Clams> clam_;
};

#endif
