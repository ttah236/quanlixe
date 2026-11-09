#include "Truck.h"
#include <sstream>
#include <iomanip>

Truck::Truck(std::string m, std::string mod, float speed, float payload, int axles)
    : Vehicle(m, mod, speed), maxPayload(payload), numAxles(axles) {}

double Truck::calculateTax() const {
    return (maxPayload * 150.0) + (numAxles * 250.0);
}

std::string Truck::toSaveString() const {
    std::stringstream ss;
    ss << "Truck," << make << "," << model << "," << maxSpeed << "," << maxPayload << "," << numAxles;
    return ss.str();
}

void Truck::display(std::ostream& os) const {
    os << std::left << std::setw(10) << "[TRUCK]";
    Vehicle::display(os);

    std::stringstream payloadStr, axlesStr;
    payloadStr << maxPayload << " Tan";
    axlesStr << numAxles << " Truc";

    os << std::left << std::setw(18) << payloadStr.str()
       << std::setw(15) << axlesStr.str()
       << "$" << calculateTax() << "\n";
}