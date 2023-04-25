#ifndef WEATHERCONDITIONS_H
#define WEATHERCONDITIONS_H

class WeatherConditions
{
public:
    WeatherConditions(double temp = 15, double windSpeed = 10, double windDirection = 0, bool isRaining = false, double rainIntensity = 0.0);
    double getTemperature() const;
    double getWindSpeed() const;
    double getWindDirection() const;
    bool getIsRaining() const;
    double getRainIntensity() const;
private:
    double temperature;
    double windSpeed;
    double windDirection;
    bool isRaining;
    double rainIntensity;
};

#endif // WEATHERCONDITIONS_H
