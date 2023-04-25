#pragma once
#ifndef WEATHER_CONDITIONS_H
#define WEATHER_CONDITIONS_H
#include "weatherconditions.h"
#include <cmath>

class BlastEffects {
public:
    BlastEffects(double blastPower, WeatherConditions weather, double latitude, double longitude) {
        calculateEffects(blastPower, weather, latitude, longitude);
    }
    double getFireballRadius() const { return fireballRadius; }
    double getPeakTemperature() const { return peakTemperature; }
    double getShockWaveRadius() const { return shockWaveRadius; }
    double getRadiationRadius() const { return radiationRadius; }

private:
    double fireballRadius = 0.0;
    double peakTemperature = 0.0;
    double shockWaveRadius = 0.0;
    double radiationRadius = 0.0;

    void calculateEffects(double blastPower, WeatherConditions weather, double latitude, double longitude) {
        // Calculate fireball radius
        double blastYield = pow(10, blastPower);
        double fireballRadiusKm = 0.22 * pow(blastYield, 0.4);
        fireballRadius = fireballRadiusKm * 1000;

        // Calculate peak temperature
        double temperatureF = 10 * pow(blastYield, 1/3) - 460;
        peakTemperature = (temperatureF - 32) * 5/9;

        // Calculate shock wave radius
        double psi = 0;
        if (weather.getWindSpeed() > 0) {
            psi = 2.07 * pow(10, -5) * pow(blastYield, 0.38) * pow(weather.getWindSpeed(), -0.5);
        } else {
            psi = 1.5 * pow(blastYield, 0.33);
        }
        shockWaveRadius = psi * 0.3048; // Convert feet to meters

        // Calculate radiation radius
        double latitudeRadians = latitude * M_PI / 180;
        double radiationExponent = 3.3 + 0.25 * weather.getRainIntensity();
        double radiationRadiusKm = 7.8 * pow(blastYield, 1/3) * pow(cos(latitudeRadians), radiationExponent);
        radiationRadius = radiationRadiusKm * 1000;
    }
};

#endif // WEATHER_CONDITIONS_H
