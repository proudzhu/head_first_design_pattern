#include <iostream>
#include <memory>
#include <list>

class Observer
{
  public:
    virtual void update(float temp, float humidity, float pressure) = 0;
};

class Subject
{
  public:
    virtual void registerObserver(std::shared_ptr<Observer> o) = 0;
    virtual void removeObserver(std::shared_ptr<Observer> o) = 0;
    virtual void notifyObservers() = 0;
};

class DisplayElement
{
  public:
    virtual void display() = 0;
};

class WeatherData : public Subject
{
  public:
    WeatherData()
    { }

    ~WeatherData()
    { }

    void registerObserver(std::shared_ptr<Observer> o)
    {
      observers_.push_back(o);
    }

    void removeObserver(std::shared_ptr<Observer> o)
    {
      observers_.remove(o);
    }

    void notifyObservers()
    {
      for (auto &o : observers_)
        o->update(temperature_, humidity_, pressure_);
    }

    void measurementsChanged()
    {
      notifyObservers();
    }

    void setMeasurements(float temperature, float humidity, float pressure)
    {
      temperature_ = temperature;
      humidity_ = humidity;
      pressure_ = pressure;
      measurementsChanged();
    }

  private:
    std::list<std::shared_ptr<Observer>> observers_;
    float temperature_;
    float humidity_;
    float pressure_;
};

class CurrentConditionsDisplay :
  public std::enable_shared_from_this<CurrentConditionsDisplay>,
  public Observer,
  public DisplayElement
{
  public:
    CurrentConditionsDisplay(std::shared_ptr<Subject> weatherData)
      : weatherData_(weatherData)
    { }

    ~CurrentConditionsDisplay()
    { }

    void registerDisplay()
    {
      weatherData_->registerObserver(shared_from_this());
    }

    void update(float temperature, float humidity, float pressure)
    {
      temperature_ = temperature;
      humidity_ = humidity;
      display();
    }

    void display()
    {
      std::cout << "Current conditions: "
                << temperature_
                << "F degrees and "
                << humidity_
                << "% humidity"
                << std::endl;
    }

  private:
    float temperature_;
    float humidity_;
    std::shared_ptr<Subject> weatherData_;
};

int main(int argc, char **argv)
{
  std::shared_ptr<WeatherData> weatherData = std::make_shared<WeatherData>();
  std::shared_ptr<CurrentConditionsDisplay> currentDisplay =
    std::make_shared<CurrentConditionsDisplay>(weatherData);

  currentDisplay->registerDisplay();

  weatherData->setMeasurements(80, 65, 30.4f);
  weatherData->setMeasurements(82, 70, 29.2f);
  weatherData->setMeasurements(78, 90, 29.2f);

  return 0;
}
