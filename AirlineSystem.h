#pragma once
#include <vector>
#include <string>
#include "Passenger.h"

class AirlineSystem {
private:
    vector<Passenger> passengers;
    const std::string filename = "passengers.txt";

    int getValidatedInteger(const std::string& prompt);
    void savePassengersToFile();
    void loadPassengersFromFile();
    std::string escape(const std::string& str);
    std::string unescape(const std::string& str);

public:
    AirlineSystem();
    ~AirlineSystem();

    void addPassenger();
    void removePassenger();
    void listPassengers();
    void searchByName();
    void searchByFlightNumber();
    void showMenu();
};
