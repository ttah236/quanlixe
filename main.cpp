#include <iostream>
#include <limits>
#include "VehicleManager.h"
#include <windows.h>

using namespace std;

void displayMenu() {
    cout << "\n================ HỆ THỐNG QUẢN LÝ PHƯƠNG TIỆN ================\n";
    cout << "1. Thêm xe hơi mới (Add Car)\n";
    cout << "2. Thêm xe tải mới (Add Truck)\n";
    cout << "3. Hiển thị danh sách phương tiện (Display All)\n";
    cout << "4. Tính tổng nghĩa vụ thuế (Calculate Total Tax Liability)\n";
    cout << "5. Lưu dữ liệu vào file gốc (Save to vehicles.txt)\n";
    cout << "6. Nạp dữ liệu từ file gốc (Load from vehicles.txt)\n";
    cout << "7. XUẤT BÁO CÁO KẾT QUẢ RA FILE TXT MỚI (Export to output.txt)\n";
    cout << "8. Tìm kiếm xe theo hãng (Search by Make)\n";
    cout << "9. Tùy chọn Sắp xếp danh sách (Sort Menu)\n";
    cout << "0. Thoát chương trình (Exit)\n";
    cout << "==============================================================\n";
    cout << "Lựa chọn của bạn [0-9]: ";
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    VehicleManager manager;
    int choice;

    do {
        displayMenu();

        if (!(cin >> choice)) {
            cerr << "Lựa chọn không hợp lệ! Vui lòng nhập số từ 0 đến 9.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1:
                manager.addCar();
                break;
            case 2:
                manager.addTruck();
                break;
            case 3:
                manager.displayAll();
                break;
            case 4:
                manager.calculateTotalTaxLiability();
                break;
            case 5:
                manager.saveData();
                break;
            case 6:
                manager.loadData();
                break;
            case 7:
                manager.exportResultsToFile();
                break;
            case 8: {
                string searchMake;
                cout << "\nNhập tên hãng xe (Make) cần tìm: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, searchMake);
                manager.searchByMake(searchMake);
                break;
            }
            case 9:
                manager.sortMenu();
                break;
            case 0: {
                char confirm;
                cout << "Bạn có muốn LƯU dữ liệu hiện tại vào 'vehicles.txt' trước khi thoát? (y/n): ";
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    manager.saveData();
                }
                manager.exportResultsToFile();
                cout << "Chương trình kết thúc. Tạm biệt!\n";
                break;
            }
            default:
                cout << "Lựa chọn không nằm trong danh mục Menu! Vui lòng chọn lại.\n";
        }
    } while (choice != 0);

    return 0;
}