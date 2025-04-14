#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Sample structure for Airline system (starter)
struct Passenger {
    string name;
    int flightNumber;
};

class AirlineSystem {
private:
    vector<Passenger> passengers;

public:
    void addPassenger() {
        Passenger p;
        cout << "\nEnter passenger name: ";
        cin >> ws;
        getline(cin, p.name);
        cout << "Enter flight number: ";
        cin >> p.flightNumber;
        passengers.push_back(p);
        cout << "Passenger added successfully!\n";
    }

    void removePassenger() {
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

    void listPassengers() {
        cout << "\n=== Registered Passengers ===" << endl;
        if (passengers.empty()) {
            cout << "None registered." << endl;
        } else {
            for (const auto& p : passengers) {
                cout << "Name: " << p.name << ", Flight #: " << p.flightNumber << endl;
            }
        }
    }

    void showMenu() {
        int choice;
        do {
            cout << "\n=== Airline Registration System ===" << endl;
            cout << "1. Add Passenger" << endl;
            cout << "2. Remove Passenger" << endl;
            cout << "3. List Passengers" << endl;
            cout << "4. Exit" << endl;
            cout << "Choose an option: ";
            cin >> choice;

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
                    cout << "Exiting system. Goodbye!\n";
                    break;
                default:
                    cout << "Invalid option. Try again.\n";
            }
        } while (choice != 4);
    }
};

int main() {
    AirlineSystem system;
    system.showMenu();
    return 0;
}
