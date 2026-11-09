#include "VehicleManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <iomanip>
#include <algorithm>

void VehicleManager::clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

VehicleManager::VehicleManager() {
    loadData();
}

VehicleManager::~VehicleManager() {
    for (Vehicle* v : vehicles) {
        delete v;
    }
    vehicles.clear();
}

void VehicleManager::loadData() {
    std::ifstream file(dataFilename);
    if (!file.is_open()) {
        std::cout << "[THÔNG BÁO] Không tìm thấy file '" << dataFilename << "'. Sẽ tạo file mới khi lưu.\n";
        return;
    }

    for (Vehicle* v : vehicles) delete v;
    vehicles.clear();

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string type, make, model, segment;

        std::getline(ss, type, ',');
        std::getline(ss, make, ',');
        std::getline(ss, model, ',');

        if (type == "Car") {
            float speed; int doors; std::string engine;
            std::getline(ss, segment, ','); speed = std::stof(segment);
            std::getline(ss, segment, ','); doors = std::stoi(segment);
            std::getline(ss, engine, ',');
            vehicles.push_back(new Car(make, model, speed, doors, engine));
        } else if (type == "Truck") {
            float speed, payload; int axles;
            std::getline(ss, segment, ','); speed = std::stof(segment);
            std::getline(ss, segment, ','); payload = std::stof(segment);
            std::getline(ss, segment, ','); axles = std::stoi(segment);
            vehicles.push_back(new Truck(make, model, speed, payload, axles));
        }
    }
    file.close();
    std::cout << "[THÀNH CÔNG] Đã tải " << vehicles.size() << " phương tiện từ file '" << dataFilename << "'.\n";
}

void VehicleManager::saveData() const {
    std::ofstream file(dataFilename);
    if (!file.is_open()) {
        std::cerr << "[LỖI] Không thể mở file '" << dataFilename << "' để ghi!\n";
        return;
    }

    for (const Vehicle* v : vehicles) {
        file << v->toSaveString() << "\n";
    }
    file.close();
    std::cout << "[THÀNH CÔNG] Đã lưu dữ liệu vào file '" << dataFilename << "'.\n";
}

void VehicleManager::addCar() {
    std::string make, model, engine;
    float speed; int doors;

    std::cout << "\n--- THÊM XE HƠI MỚI ---\n";
    std::cout << "Nhập hãng sản xuất: "; clearInputBuffer(); std::getline(std::cin, make);
    std::cout << "Nhập dòng xe (Model): "; std::getline(std::cin, model);

    std::cout << "Nhập tốc độ tối đa (km/h): ";
    while (!(std::cin >> speed) || speed <= 0) {
        std::cout << "Tốc độ không hợp lệ! Nhập lại: "; clearInputBuffer();
    }

    std::cout << "Nhập số cửa: ";
    while (!(std::cin >> doors) || doors <= 0) {
        std::cout << "Số cửa không hợp lệ! Nhập lại: "; clearInputBuffer();
    }

    std::cout << "Nhập loại động cơ (Petrol/Diesel/Electric): ";
    clearInputBuffer(); std::getline(std::cin, engine);

    vehicles.push_back(new Car(make, model, speed, doors, engine));
    std::cout << "[THÀNH CÔNG] Đã thêm xe hơi " << make << " " << model << ".\n";
}

void VehicleManager::addTruck() {
    std::string make, model;
    float speed, payload; int axles;

    std::cout << "\n--- THÊM XE TẢI MỚI ---\n";
    std::cout << "Nhập hãng sản xuất: "; clearInputBuffer(); std::getline(std::cin, make);
    std::cout << "Nhập dòng xe (Model): "; std::getline(std::cin, model);

    std::cout << "Nhập tốc độ tối đa (km/h): ";
    while (!(std::cin >> speed) || speed <= 0) {
        std::cout << "Tốc độ không hợp lệ! Nhập lại: "; clearInputBuffer();
    }

    std::cout << "Nhập tải trọng tối đa (Tấn): ";
    while (!(std::cin >> payload) || payload <= 0) {
        std::cout << "Tải trọng không hợp lệ! Nhập lại: "; clearInputBuffer();
    }

    std::cout << "Nhập số trục bánh xe: ";
    while (!(std::cin >> axles) || axles <= 0) {
        std::cout << "Số trục không hợp lệ! Nhập lại: "; clearInputBuffer();
    }

    vehicles.push_back(new Truck(make, model, speed, payload, axles));
    std::cout << "[THÀNH CÔNG] Đã thêm xe tải " << make << " " << model << ".\n";
}

// IN BẢNG VÀ TÍNH TỔNG THUẾ NGAY BÊN DƯỚI BẢNG
void VehicleManager::displayAll() const {
    if (vehicles.empty()) {
        std::cout << "\n[THÔNG BÁO] Danh sách phương tiện trống.\n";
        return;
    }
    std::cout << "\n========================================= DANH SÁCH PHƯƠNG TIỆN =========================================\n";
    std::cout << std::left << std::setw(5)  << "STT"
              << std::setw(10) << "LOAI"
              << std::setw(20) << "HANG XE"
              << std::setw(18) << "DONG XE"
              << std::setw(10) << "TOC DO"
              << std::setw(18) << "CUA / TAI TRONG"
              << std::setw(18) << "DONG CO / TRUC"
              << "THUE\n";
    std::cout << std::string(105, '-') << "\n";

    double totalTax = 0.0;
    for (size_t i = 0; i < vehicles.size(); ++i) {
        std::cout << std::left << std::setw(5) << (i + 1);
        vehicles[i]->display(std::cout);
        totalTax += vehicles[i]->calculateTax(); // Cộng dồn tiền thuế từng xe
    }
    std::cout << std::string(105, '-') << "\n";
    
    // In dòng tổng nghĩa vụ thuế ngay bên dưới bảng
    std::cout << ">>> TỔNG NGHĨA VỤ THUẾ TẤT CẢ PHƯƠNG TIỆN PHẢI NỘP: $" << std::fixed << std::setprecision(2) << totalTax << " <<<\n";
    std::cout << "=========================================================================================\n";
}

void VehicleManager::calculateTotalTaxLiability() const {
    if (vehicles.empty()) {
        std::cout << "\n[THÔNG BÁO] Danh sách trống, tổng thuế = $0.\n";
        return;
    }
    double totalTax = 0.0;
    std::cout << "\n================ BÁO CÁO NGHĨA VỤ THUẾ ================\n";
    for (const Vehicle* v : vehicles) {
        double tax = v->calculateTax();
        totalTax += tax;
        std::cout << "- " << v->getMake() << " " << v->getModel() << " | Thuế: $" << tax << "\n";
    }
    std::cout << "-------------------------------------------------------\n";
    std::cout << ">>> TỔNG NGHĨA VỤ THUẾ TẤT CẢ PHƯƠNG TIỆN: $" << totalTax << " <<<\n";
    std::cout << "=======================================================\n";
}

void VehicleManager::exportResultsToFile() const {
    std::ofstream outFile(outputFilename);
    if (!outFile.is_open()) {
        std::cerr << "[LỖI] Không thể tạo tệp xuất kết quả '" << outputFilename << "'!\n";
        return;
    }

    outFile << "=============================================================\n";
    outFile << "             BÁO CÁO KẾT QUẢ QUẢN LÝ PHƯƠNG TIỆN             \n";
    outFile << "=============================================================\n\n";

    if (vehicles.empty()) {
        outFile << "Danh sách phương tiện hiện đang trống.\n";
    } else {
        outFile << "--- 1. DANH SÁCH CHI TIẾT CÁC PHƯƠNG TIỆN ---\n";
        double totalTax = 0.0;
        for (size_t i = 0; i < vehicles.size(); ++i) {
            outFile << i + 1 << ". ";
            vehicles[i]->display(outFile);
            totalTax += vehicles[i]->calculateTax();
        }

        outFile << "\n--- 2. TỔNG KẾT NGHĨA VỤ THUẾ (TOTAL TAX LIABILITY) ---\n";
        outFile << "Tổng số lượng phương tiện: " << vehicles.size() << " xe\n";
        outFile << "TỔNG NGHĨA VỤ THUẾ PHẢI NỘP: $" << totalTax << "\n";
    }

    outFile << "\n=============================================================\n";
    outFile.close();

    std::cout << "[THÀNH CÔNG] Đã xuất toàn bộ kết quả báo cáo vào tệp mới: '" << outputFilename << "'.\n";
}

void VehicleManager::searchByMake(const std::string& make) const {
    bool found = false;
    std::cout << "\n--- KẾT QUẢ TÌM KIẾM CHO HÃNG: '" << make << "' ---\n";

    for (size_t i = 0; i < vehicles.size(); ++i) {
        if (vehicles[i]->getMake() == make) {
            std::cout << "- ";
            vehicles[i]->display(std::cout);
            found = true;
        }
    }

    if (!found) {
        std::cout << "[THÔNG BÁO] Không tìm thấy phương tiện nào thuộc hãng '" << make << "'.\n";
    }
}

void VehicleManager::sortMenu() {
    if (vehicles.empty()) {
        std::cout << "\n[THÔNG BÁO] Danh sách trống, không có gì để sắp xếp.\n";
        return;
    }

    int sortChoice;
    std::cout << "\n--- CHỌN TIÊU CHÍ SẮP XẾP ---\n";
    std::cout << "1. Sắp xếp theo Hãng xe (A-Z)\n";
    std::cout << "2. Sắp xếp theo Tốc độ tối đa (Giảm dần)\n";
    std::cout << "3. Sắp xếp theo Số cửa (Giảm dần)\n";
    std::cout << "4. Sắp xếp theo Loại động cơ (A-Z)\n";
    std::cout << "5. Sắp xếp theo Thuế (Giảm dần)\n";
    std::cout << "0. Hủy và quay lại Menu chính\n";
    std::cout << "Lựa chọn của bạn: ";

    if (!(std::cin >> sortChoice)) {
        clearInputBuffer();
        std::cout << "Lựa chọn không hợp lệ!\n";
        return;
    }

    switch (sortChoice) {
        case 1:
            std::sort(vehicles.begin(), vehicles.end(), [](const Vehicle* a, const Vehicle* b) {
                return a->getMake() < b->getMake();
            });
            break;
        case 2:
            std::sort(vehicles.begin(), vehicles.end(), [](const Vehicle* a, const Vehicle* b) {
                return a->getMaxSpeed() > b->getMaxSpeed();
            });
            break;
        case 3:
            std::sort(vehicles.begin(), vehicles.end(), [](const Vehicle* a, const Vehicle* b) {
                const Car* carA = dynamic_cast<const Car*>(a);
                const Car* carB = dynamic_cast<const Car*>(b);
                int doorsA = carA ? carA->getNumDoors() : -1;
                int doorsB = carB ? carB->getNumDoors() : -1;
                return doorsA > doorsB;
            });
            break;
        case 4:
            std::sort(vehicles.begin(), vehicles.end(), [](const Vehicle* a, const Vehicle* b) {
                const Car* carA = dynamic_cast<const Car*>(a);
                const Car* carB = dynamic_cast<const Car*>(b);
                std::string engA = carA ? carA->getEngineType() : "zzz";
                std::string engB = carB ? carB->getEngineType() : "zzz";
                return engA < engB;
            });
            break;
        case 5:
            std::sort(vehicles.begin(), vehicles.end(), [](const Vehicle* a, const Vehicle* b) {
                return a->calculateTax() > b->calculateTax();
            });
            break;
        case 0:
            return;
        default:
            std::cout << "Lựa chọn ngoài danh mục!\n";
            return;
    }
    std::cout << "[THÀNH CÔNG] Đã sắp xếp danh sách.\n";
    displayAll();
}