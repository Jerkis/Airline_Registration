#include "AirlineSystem.h"
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

AirlineSystem::AirlineSystem() {
    loadPassengersFromFile();
}

AirlineSystem::~AirlineSystem() {
    savePassengersToFile();
}

int AirlineSystem::getValidatedInteger(const std::string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid number.\n";
        } else {
            char leftover;
            if (cin.get(leftover) && !isspace(leftover)) {
                cout << "Invalid input. Please enter numbers only.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                return value;
            }
        }
    }
}

void AirlineSystem::addPassenger() {
    Passenger p;
    cout << "\nEnter passenger name: ";
    cin >> ws;
    getline(cin, p.name);

    p.flightNumber = getValidatedInteger("Enter flight number: ");
    passengers.push_back(p);

    cout << "Passenger added successfully!\n";
}

void AirlineSystem::removePassenger() {
    string name;
    cout << "\nEnter name of passenger to remove: ";
    cin >> ws;
    getline(cin, name);

    bool removed = false;
    for (auto it = passengers.begin(); it != passengers.end(); ++it) {
        if (it->name == name) {
            passengers.erase(it);
            removed = true;
            cout << "Passenger removed.\n";
            break;
        }
    }
    if (!removed) {
        cout << "Passenger not found.\n";
    }
}

void AirlineSystem::listPassengers() {
    cout << "\n=== Registered Passengers ===" << endl;
    if (passengers.empty()) {
        cout << "None registered.\n";
    } else {
        for (const auto& p : passengers) {
            cout << "Name: " << p.name << ", Flight #: " << p.flightNumber << endl;
        }
    }
}

void AirlineSystem::searchByName() {
    cout << "\nEnter name to search: ";
    string name;
    cin >> ws;
    getline(cin, name);

    bool found = false;
    for (const auto& p : passengers) {
        if (p.name.find(name) != string::npos) {
            cout << "Found: " << p.name << ", Flight #: " << p.flightNumber << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No passengers found matching '" << name << "'\n";
    }
}

void AirlineSystem::searchByFlightNumber() {
    int flightNum = getValidatedInteger("\nEnter flight number to search: ");
    bool found = false;
    for (const auto& p : passengers) {
        if (p.flightNumber == flightNum) {
            cout << "Found: " << p.name << ", Flight #: " << p.flightNumber << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No passengers found on flight #" << flightNum << "\n";
    }
}

void AirlineSystem::showMenu() {
    int choice;
    do {
        cout << "\n=== Airline Registration System ===" << endl;
        cout << "1. Add Passenger" << endl;
        cout << "2. Remove Passenger" << endl;
        cout << "3. List Passengers" << endl;
        cout << "4. Search by Name" << endl;
        cout << "5. Search by Flight Number" << endl;
        cout << "6. Exit" << endl;

        choice = getValidatedInteger("Choose an option: ");

        switch (choice) {
            case 1:
                addPassenger();
                break;
            case 2:
                removePassenger();
                break;
            case 3:
                listPassengers();
                break;
            case 4:
                searchByName();
                break;
            case 5:
                searchByFlightNumber();
                break;
            case 6:
                cout << "Saving data and exiting. Goodbye!\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }
    } while (choice != 6);
}

// Escape special characters before saving
string AirlineSystem::escape(const std::string& str) {
    string escaped;
    for (char ch : str) {
        if (ch == '\\' || ch == '|') {
            escaped += '\\';
        }
        escaped += ch;
    }
    return escaped;
}

// Unescape special characters after loading
string AirlineSystem::unescape(const std::string& str) {
    string unescaped;
    bool escapeNext = false;
    for (char ch : str) {
        if (escapeNext) {
            unescaped += ch;
            escapeNext = false;
        } else if (ch == '\\') {
            escapeNext = true;
        } else {
            unescaped += ch;
        }
    }
    return unescaped;
}

void AirlineSystem::savePassengersToFile() {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file for writing.\n";
        return;
    }

    for (const auto& p : passengers) {
        outFile << escape(p.name) << "|" << p.flightNumber << "\n";
    }
    outFile.close();
}

void AirlineSystem::loadPassengersFromFile() {
    ifstream inFile(filename);
    if (!inFile) {
        return; // No passengers yet
    }

    string line;
    while (getline(inFile, line)) {
        size_t delimiterPos = line.find('|');
        if (delimiterPos != string::npos) {
            Passenger p;
            p.name = unescape(line.substr(0, delimiterPos));
            p.flightNumber = stoi(line.substr(delimiterPos + 1));
            passengers.push_back(p);
        }
    }
    inFile.close();
}
