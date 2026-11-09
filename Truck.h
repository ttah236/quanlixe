#ifndef TRUCK_H
#define TRUCK_H

#include "Vehicle.h"

class Truck : public Vehicle {
private:
    float maxPayload;
    int numAxles;

public:
    Truck(std::string m, std::string mod, float speed, float payload, int axles);

    double calculateTax() const override;
    std::string toSaveString() const override;
    void display(std::ostream& os = std::cout) const override;
};

#endif // TRUCK_H