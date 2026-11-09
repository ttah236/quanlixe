#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"
#include <string>

class Car : public Vehicle {
private:
    int numDoors;
    std::string engineType;

public:
    Car(std::string m, std::string mod, float speed, int doors, std::string engine);

    double calculateTax() const override;
    std::string toSaveString() const override;
    void display(std::ostream& os = std::cout) const override;

    int getNumDoors() const { return numDoors; }
    std::string getEngineType() const { return engineType; }
};

#endif // CAR_H