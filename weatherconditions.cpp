#include "weatherconditions.h"

WeatherConditions::WeatherConditions(double temp, double windSpeed, double windDirection, bool isRaining, double rainIntensity)
    : temperature(temp), windSpeed(windSpeed), windDirection(windDirection), isRaining(isRaining), rainIntensity(rainIntensity)
{}

double WeatherConditions::getTemperature() const
{
    return temperature;
}

double WeatherConditions::getWindSpeed() const
{
    return windSpeed;
}

double WeatherConditions::getWindDirection() const
{
    return windDirection;
}

bool WeatherConditions::getIsRaining() const
{
    return isRaining;
}

double WeatherConditions::getRainIntensity() const {
    if (isRaining) {
        return rainIntensity;
    } else {
        return 0.0;
    }
}
