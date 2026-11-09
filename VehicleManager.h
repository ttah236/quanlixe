#ifndef VEHICLEMANAGER_H
#define VEHICLEMANAGER_H

#include "Vehicle.h"
#include "Car.h"
#include "Truck.h"
#include <vector>
#include <string>

class VehicleManager {
private:
    std::vector<Vehicle*> vehicles;
    const std::string dataFilename = "vehicles.txt";
    const std::string outputFilename = "output.txt";

    void clearInputBuffer();

public:
    VehicleManager();
    ~VehicleManager();

    void loadData();
    void saveData() const;

    void addCar();
    void addTruck();

    void displayAll() const;
    void calculateTotalTaxLiability() const;

    void exportResultsToFile() const;
    void searchByMake(const std::string& make) const;
    void sortMenu();
};

#endif // VEHICLEMANAGER_H