#include "Car.h"
#include <sstream>
#include <iomanip>

Car::Car(std::string m, std::string mod, float speed, int doors, std::string engine)
    : Vehicle(m, mod, speed), numDoors(doors), engineType(engine) {}

double Car::calculateTax() const {
    double baseTax = 500.0 + (numDoors * 100.0);
    if (engineType == "Electric" || engineType == "electric") {
        baseTax *= 0.8;
    }
    return baseTax;
}

std::string Car::toSaveString() const {
    std::stringstream ss;
    ss << "Car," << make << "," << model << "," << maxSpeed << "," << numDoors << "," << engineType;
    return ss.str();
}

void Car::display(std::ostream& os) const {
    os << std::left << std::setw(10) << "[CAR]";
    Vehicle::display(os);

    std::stringstream doorStr;
    doorStr << numDoors << " Cua";

    os << std::left << std::setw(18) << doorStr.str()
       << std::setw(15) << engineType
       << "$" << calculateTax() << "\n";
}