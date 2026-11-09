#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>

class Vehicle {
protected:
    std::string make;
    std::string model;
    float maxSpeed;

public:
    Vehicle(std::string m, std::string mod, float speed);
    virtual ~Vehicle();

    std::string getMake() const;
    std::string getModel() const;
    float getMaxSpeed() const;

    virtual double calculateTax() const = 0;
    virtual std::string toSaveString() const = 0;
    virtual void display(std::ostream& os = std::cout) const;
};

#endif // VEHICLE_H