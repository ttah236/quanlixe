#include "Vehicle.h"
#include <iomanip> // Thư viện hỗ trợ căn lề cột (std::left, std::setw)

// Hàm khởi tạo (Constructor) sử dụng Member Initializer List
Vehicle::Vehicle(std::string m, std::string mod, float speed)
    : make(m), model(mod), maxSpeed(speed) {}

// Hàm hủy ảo (Virtual Destructor)
Vehicle::~Vehicle() {}

// Các hàm Getter lấy thông tin
std::string Vehicle::getMake() const { 
    return make; 
}

std::string Vehicle::getModel() const { 
    return model; 
}

float Vehicle::getMaxSpeed() const { 
    return maxSpeed; 
}

// Hàm in thông tin chung dạng bảng
void Vehicle::display(std::ostream& os) const {
    os << std::left << std::setw(20) << make 
       << std::setw(18) << model 
       << std::setw(10) << maxSpeed;
}