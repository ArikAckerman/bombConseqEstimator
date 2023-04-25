
#ifndef CASUALTIESESTIMATOR_H
#define CASUALTIESESTIMATOR_H

#include "blasteffects.h"
#include "weatherconditions.h"
#include <cmath>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "location.h"
using json = nlohmann::json;

class CasualtiesEstimator {
public:
    CasualtiesEstimator() {}
    int getEstimatedPopulation(double lat, double lon);
    CasualtiesEstimator(double blastPower, WeatherConditions weather, Location location) {
        populationDensity = getPopulationDensity(location.latitude(), location.longitude());
        calculateCasualties(blastPower, weather, populationDensity);
    }
    int getFatalities() const { return fatalities; }
    int getInjuries() const { return injuries; }
    double getPopulationDensity(double latitude, double longitude) {
        std::string url = "http://api.worldpop.org/v1/services/stats?data=pop&mask=true&order=pop&precision=3&points=" + std::to_string(latitude) + "," + std::to_string(longitude);
        CURL *curl;
        CURLcode res;
        std::string response;

        curl_global_init(CURL_GLOBAL_DEFAULT);

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "Failed to fetch population density: " << curl_easy_strerror(res) << std::endl;
                populationDensity = 0;
            }
            curl_easy_cleanup(curl);
        }

        curl_global_cleanup();

        if (!response.empty()) {
            json j = json::parse(response);
            if (j.is_array() && !j.empty() && j[0].contains("pop")) {
                return j[0]["pop"];
            } else {
                std::cerr << "Unexpected response from WorldPop API: " << response << std::endl;
            }
        } else {
            std::cerr << "Empty response from WorldPop API" << std::endl;
        }
        return 0;
    }

private:
    int fatalities;
    int injuries;
    double populationDensity;
    std::unordered_map<std::string, int> popDensity;

    void calculateCasualties(double blastPower, WeatherConditions weather, double populationDensity) {
        // Calculate fatalities and injuries
        double blastYield = pow(10, blastPower);
        double area = M_PI * pow(BlastEffects(blastPower, weather, 0, 0).getShockWaveRadius(), 2);
        double populationExposed = populationDensity * area;
        fatalities = 0.025 * pow(blastYield, 0.4) * populationExposed;
        injuries = 0.11 * pow(blastYield, 0.4) * populationExposed;
    }

    static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp) {
        ((std::string *)userp)->append((char *)contents, size * nmemb);
        return size * nmemb;
    }
};

int CasualtiesEstimator::getEstimatedPopulation(double lat, double lon) {
    std::string key = std::to_string(lat) + "," + std::to_string(lon);
    if (popDensity.find(key) != popDensity.end()) {
        return popDensity[key];
    } else {
        int density = getPopulationDensity(lat, lon);
        popDensity[key] = density;
        return density;
    }
}

#endif // CASUALTIESESTIMATOR_H
