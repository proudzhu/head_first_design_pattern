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

class StatisticsDisplay :
  public std::enable_shared_from_this<StatisticsDisplay>,
  public Observer,
  public DisplayElement
{
  public:
    StatisticsDisplay(std::shared_ptr<Subject> weatherData)
      : weatherData_(weatherData)
    { }

    ~StatisticsDisplay()
    { }

    void registerDisplay()
    {
      weatherData_->registerObserver(shared_from_this());
    }

    void update(float temperature, float humidity, float pressure)
    {
      if (temperature > maxTemp_)
        maxTemp_ = temperature;

      if (temperature < minTemp_)
        minTemp_ = temperature;

      tempSum_ += temperature;
      numReadings++;

      display();
    }

    void display()
    {
      std::cout << "Avg/Max/Min temperature = "
                << (tempSum_ / numReadings)
                << "/"
                << maxTemp_
                << "/"
                << minTemp_
                << std::endl;
    }

  private:
    float maxTemp_;
    float minTemp_;
    float tempSum_;
    int numReadings;
    std::shared_ptr<Subject> weatherData_;
};

class ForecastDisplay :
  public std::enable_shared_from_this<ForecastDisplay>,
  public Observer,
  public DisplayElement
{
  public:
    ForecastDisplay(std::shared_ptr<Subject> weatherData)
      : weatherData_(weatherData)
    { }

    ~ForecastDisplay()
    { }

    void registerDisplay()
    {
      weatherData_->registerObserver(shared_from_this());
    }

    void update(float temperature, float humidity, float pressure)
    {
      lastPressure_ = currentPressure_;
      currentPressure_ = pressure;

      display();
    }

    void display()
    {
      std::cout << "Forecast: ";
      if (currentPressure_ > lastPressure_)
        std::cout << "Improving weather on the way!";
      else if (currentPressure_ == lastPressure_)
        std::cout << "More of the same";
      else
        std::cout << "Watch out for cooler, rainy weather";
      std::cout << std::endl;
    }

  private:
    float currentPressure_;
    float lastPressure_;
    std::shared_ptr<Subject> weatherData_;
};

class HeatIndexDisplay :
  public std::enable_shared_from_this<HeatIndexDisplay>,
  public Observer,
  public DisplayElement
{
  public:
    HeatIndexDisplay(std::shared_ptr<Subject> weatherData)
      : weatherData_(weatherData)
    { }

    ~HeatIndexDisplay()
    { }

    void registerDisplay()
    {
      weatherData_->registerObserver(shared_from_this());
    }

    void update(float temperature, float humidity, float pressure)
    {
      heatIndex_ = computeHeatIndex(temperature, humidity);

      display();
    }

    void display()
    {
      std::cout << "Heat index is " << heatIndex_ <<  std::endl;
    }

  private:
    float heatIndex_;
    std::shared_ptr<Subject> weatherData_;

    float computeHeatIndex(float t, float rh) {
      float index = (float)((16.923 + (0.185212 * t) + (5.37941 * rh) - (0.100254 * t * rh) +
            (0.00941695 * (t * t)) + (0.00728898 * (rh * rh)) +
            (0.000345372 * (t * t * rh)) - (0.000814971 * (t * rh * rh)) +
            (0.0000102102 * (t * t * rh * rh)) - (0.000038646 * (t * t * t)) + (0.0000291583 *
            (rh * rh * rh)) + (0.00000142721 * (t * t * t * rh)) +
            (0.000000197483 * (t * rh * rh * rh)) - (0.0000000218429 * (t * t * t * rh * rh)) +
            0.000000000843296 * (t * t * rh * rh * rh)) -
            (0.0000000000481975 * (t * t * t * rh * rh * rh)));
      return index;
    }
};


int main(int argc, char **argv)
{
  std::shared_ptr<WeatherData> weatherData = std::make_shared<WeatherData>();
  std::shared_ptr<CurrentConditionsDisplay> currentDisplay =
    std::make_shared<CurrentConditionsDisplay>(weatherData);
  std::shared_ptr<StatisticsDisplay> statisticsDisplay =
    std::make_shared<StatisticsDisplay>(weatherData);
  std::shared_ptr<ForecastDisplay> forecastDisplay =
    std::make_shared<ForecastDisplay>(weatherData);
  std::shared_ptr<HeatIndexDisplay> heatIndexDisplay =
    std::make_shared<HeatIndexDisplay>(weatherData);

  currentDisplay->registerDisplay();
  statisticsDisplay->registerDisplay();
  forecastDisplay->registerDisplay();
  heatIndexDisplay->registerDisplay();

  weatherData->setMeasurements(80, 65, 30.4f);
  weatherData->setMeasurements(82, 70, 29.2f);
  weatherData->setMeasurements(78, 90, 29.2f);

  return 0;
}
