
#ifndef SHELTERESTIMATOR_H
#define SHELTERESTIMATOR_H

#pragma once

#include "CasualtiesEstimator.h"
#include <cmath>
#include "location.h"

class ShelterEstimator {
public:
    ShelterEstimator() {}
    ShelterEstimator(double blastPower, WeatherConditions weather, Location loc) {
        calculateShelterNeeds(blastPower, weather, loc);
    }

    int getNumberOfSheltersNeeded() const { return numberOfSheltersNeeded; }
    int getShelterCapacity() const { return shelterCapacity; }

private:
    static const int ShelterRadius = 5; // km
    constexpr static const double SquareKilometerToSquareMile = 0.386102;
    static const int SquareMileToSquareFoot = 27878400;
    constexpr static const double SquareFootPerPerson = 10;
    static const int MinimumShelterCapacity = 10;

    int numberOfSheltersNeeded;
    int shelterCapacity;

    void calculateShelterNeeds(double blastPower, WeatherConditions weather, Location loc) {
        CasualtiesEstimator casualtiesEstimator(blastPower, weather, loc);
        int population = casualtiesEstimator.getEstimatedPopulation(loc.latitude(), loc.longitude());

        double populationDensity = casualtiesEstimator.getPopulationDensity(loc.latitude(), loc.longitude());

        double affectedArea = M_PI * pow(ShelterRadius, 2);
        double populationInAffectedArea = populationDensity * affectedArea;

        int sheltersNeeded = ceil(populationInAffectedArea / (SquareFootPerPerson * SquareMileToSquareFoot));
        if (sheltersNeeded == 0) {
            sheltersNeeded = 1;
        }
        numberOfSheltersNeeded = sheltersNeeded;

        int capacity = ceil(populationInAffectedArea / sheltersNeeded);
        if (capacity < MinimumShelterCapacity) {
            capacity = MinimumShelterCapacity;
        }
        shelterCapacity = capacity;
    }
};


#endif // SHELTERESTIMATOR_H
