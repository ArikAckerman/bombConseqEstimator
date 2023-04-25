
#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include "BlastEffects.h"
#include "CasualtiesEstimator.h"
#include "ShelterEstimator.h"
#include "weatherconditions.h"

class Server {
public:
    Server() = default;

    void run() {
        int ShelterRadius = 5;
        std::cout << "Welcome to the Nuke Explosion Server!" << std::endl;

        std::string latitude_str, longitude_str, yield_str;
        double latitude, longitude, yield;
        WeatherConditions weather;

        // Read latitude from user input
        std::cout << "Enter the latitude of the explosion (in degrees): ";
        std::cin >> latitude_str;
        latitude = std::stod(latitude_str);

        // Read longitude from user input
        std::cout << "Enter the longitude of the explosion (in degrees): ";
        std::cin >> longitude_str;
        longitude = std::stod(longitude_str);
        Location loc(latitude, longitude);
        // Read yield from user input
        std::cout << "Enter the yield of the explosion (in kilotons): ";
        std::cin >> yield_str;
        yield = std::stod(yield_str);

        // Calculate blast effects
        BlastEffects blastEffects(yield, weather, latitude, longitude);
        double fireballRadius = blastEffects.getFireballRadius();
        double blastRadius = blastEffects.getShockWaveRadius();

        // Estimate casualties
        CasualtiesEstimator casualtiesEstimator(latitude, longitude, blastRadius);
        double estimatedFatalities = casualtiesEstimator.getFatalities();
        double estimatedInjuries = casualtiesEstimator.getInjuries();

        // Estimate shelter needs
        ShelterEstimator shelterEstimator(blastRadius, weather, loc);
        int estimatedShelters = shelterEstimator.getNumberOfSheltersNeeded();
        int estimatedCapacity = shelterEstimator.getShelterCapacity();

        // Print the results
        std::cout << std::endl;
        std::cout << "RESULTS" << std::endl;
        std::cout << "-------" << std::endl;
        std::cout << "Blast effects:" << std::endl;
        std::cout << "Fireball radius: " << fireballRadius << " km" << std::endl;
        std::cout << "Blast radius: " << blastRadius << " km" << std::endl;
        std::cout << std::endl;
        std::cout << "Casualties estimator:" << std::endl;
        std::cout << "Estimated fatalities: " << estimatedFatalities << std::endl;
        std::cout << "Estimated injuries: " << estimatedInjuries << std::endl;
        std::cout << std::endl;
        std::cout << "Shelter estimator:" << std::endl;
        std::cout << "Estimated shelters needed: " << estimatedShelters << std::endl;
        std::cout << "Estimated shelter capacity needed: " << estimatedCapacity << std::endl;
    }
};

#endif // SERVER_H
