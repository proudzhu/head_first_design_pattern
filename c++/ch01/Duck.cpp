#include <iostream>
#include <memory>

class FlyBehavior
{
  public:
    virtual void fly() = 0;
};

class FlyWithWings : public FlyBehavior
{
  public:
    void fly() override
    {
      std::cout << "I'm flying!!" << std::endl;
    }
};

class FlyNoWay : public FlyBehavior
{
  public:
    void fly() override
    {
      std::cout << "I can't fly" << std::endl;
    }
};

class FlyRocketPowered : public FlyBehavior
{
  public:
    void fly() override
    {
      std::cout << "I'm flying with a rocket!" << std::endl;
    }
};


class QuackBehavior
{
  public:
    virtual void quack() = 0;
};

class Quack : public QuackBehavior
{
  public:
    void quack() override
    {
      std::cout << "Quack" << std::endl;
    }
};

class MuteQuack : public QuackBehavior
{
  public:
    void quack() override
    {
      std::cout << "<< Silence >>" << std::endl;
    }
};

class Squeak : public QuackBehavior
{
  public:
    void quack() override
    {
      std::cout << "Squeak" << std::endl;
    }
};

class Duck
{
  public:
    Duck(std::unique_ptr<FlyBehavior> fly, std::unique_ptr<QuackBehavior> quack)
      : flyBehavior(std::move(fly)), quackBehavior(std::move(quack))
    { }

    ~Duck() { }

    void swim()
    {
      std::cout << "All ducks float, even decoys!" << std::endl;
    }

    void display();

    void performFly()
    {
      flyBehavior->fly();
    }

    void performQuack()
    {
      quackBehavior->quack();
    }

    void setFlyBehavior(std::unique_ptr<FlyBehavior> fly)
    {
      flyBehavior = std::move(fly);
    }

    void setQuackBehavior(std::unique_ptr<QuackBehavior> quack)
    {
      quackBehavior = std::move(quack);
    }

  private:
    std::unique_ptr<FlyBehavior> flyBehavior;
    std::unique_ptr<QuackBehavior> quackBehavior;
};

class MallardDuck : public Duck
{
  public:
    MallardDuck()
      : Duck(std::make_unique<FlyWithWings>(), std::make_unique<Quack>())
    { }

    void display()
    {
      std::cout << "I'm a real Mallard duck" << std::endl;
    }
};

class ModelDuck : public Duck
{
  public:
    ModelDuck()
      : Duck(std::make_unique<FlyNoWay>(), std::make_unique<Quack>())
    { }

    void display()
    {
      std::cout << "I'm a model duck" << std::endl;
    }
};

int main(int argc, char **argv)
{
  std::unique_ptr<Duck> mallard = std::make_unique<MallardDuck>();
  mallard->performQuack();
  mallard->performFly();

  std::unique_ptr<Duck> model = std::make_unique<ModelDuck>();
  model->performFly();
  model->setFlyBehavior(std::make_unique<FlyRocketPowered>());
  model->performFly();

  return 0;
}
