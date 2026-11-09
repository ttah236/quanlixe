# Hệ Thống Quản Lý Phương Tiện (Vehicle Management System)
> **Chuyển đổi toàn diện từ C++ OOP sang Web Application chuẩn OOP ES6 & Full-Stack Architecture**

---

## 📌 1. Bảng Đối Chiếu Kiến Trúc (C++ vs Web OOP Mapping)

Dự án tuân thủ nghiêm ngặt 4 trụ cột Lập trình Hướng đối tượng (**Tính Trừu tượng, Tính Đóng gói, Tính Kế thừa, Tính Đa hình**), chuyển đổi tương đương 1-1 từ 9 file mã nguồn C++ ban đầu:

| C++ Source File | Thành phần Web tương đương | Vai trò & Trách nhiệm |
| :--- | :--- | :--- |
| `Vehicle.h`, `Vehicle.cpp` | `js/models/Vehicle.js` | **Lớp cơ sở trừu tượng (Abstract Base Class)**: Quản lý thuộc tính `make`, `model`, `maxSpeed`. Khai báo phương thức thuần ảo `calculateTax()` và `toSaveString()`. Không cho phép khởi tạo trực tiếp (`new Vehicle`). |
| `Car.h`, `Car.cpp` | `js/models/Car.js` | **Lớp con kế thừa Vehicle**: Bổ sung `numDoors`, `engineType`. Ghi đè `calculateTax()` (Base $500 + $100 * doors, giảm 20% nếu Electric) và `toSaveString()`. |
| `Truck.h`, `Truck.cpp` | `js/models/Truck.js` | **Lớp con kế thừa Vehicle**: Bổ sung `maxPayload`, `numAxles`. Ghi đè `calculateTax()` (`payload * $150 + axles * $250`) và `toSaveString()`. |
| `VehicleManager.h`, `VehicleManager.cpp` | `js/controllers/VehicleManager.js` | **Lớp điều khiển (Controller)**: Quản lý danh sách phương tiện, thực thi tính toán đa hình, tìm kiếm theo hãng, menu sắp xếp 5 tiêu chí, nạp/lưu file `vehicles.txt`, xuất báo cáo `output.txt` và đồng bộ LocalStorage. |
| `main.cpp` | `js/app.js` & `index.html` | **Giao diện & Điều khiển sự kiện (UI & Event Binding)**: Xử lý tương tác bảng, form thêm xe hơi/xe tải, hiển thị dòng tổng thuế, menu sắp xếp lồng, upload/download file. |
| - | `server.js` & `package.json` | **Full-Stack Node.js Server**: Phục vụ file tĩnh và cung cấp REST API tương tác trực tiếp với file trên đĩa cứng (tùy chọn). |

---

## ⚙️ 2. Công Thức Thuế & Tính Đa Hình (Polymorphism)

### Xe Hơi (Car)
$$\text{Tax}_{\text{Car}} = (500 + \text{numDoors} \times 100) \times (\text{engineType == 'Electric'} \ ? \ 0.8 : 1.0)$$
- **Ví dụ**: Toyota Camry (4 cửa, Petrol) $\rightarrow \$500 + 4 \times \$100 = \$900$.
- **Ví dụ**: Tesla Model 3 (4 cửa, Electric) $\rightarrow (\$500 + 4 \times \$100) \times 0.8 = \$720$.

### Xe Tải (Truck)
$$\text{Tax}_{\text{Truck}} = (\text{maxPayload} \times 150) + (\text{numAxles} \times 250)$$
- **Ví dụ**: Volvo FH16 (25.5 tấn, 4 trục) $\rightarrow 25.5 \times \$150 + 4 \times \$250 = \$3,825 + \$1,000 = \$4,825$.

### Tính Đa Hình (Polymorphism)
`VehicleManager` duyệt qua mảng các đối tượng `Vehicle` mà không cần biết cụ thể là `Car` hay `Truck`, chỉ cần gọi phương thức trừu tượng `calculateTax()` để tính tổng nghĩa vụ thuế toàn bộ hệ thống:
$$\text{TotalTax} = \sum_{i=1}^{N} \text{vehicles}[i].\text{calculateTax}()$$

---

## 🖥️ 3. Giao Diện & Tính Năng Web Hoàn Chỉnh

1. **Bảng Danh Sách Chuẩn (Vehicle Table)**:
   - Hiển thị đầy đủ các cột: **STT, Loại xe ([CAR]/[TRUCK]), Hãng xe, Dòng xe, Tốc độ tối đa, Số cửa/Tải trọng, Động cơ/Số trục, Tiền thuế, Thao tác xóa**.
   - Phân biệt trực quan huy hiệu xe hơi (màu xanh dương) và xe tải (màu cam), gắn nhãn giảm 20% cho xe điện.
2. **Dòng Tổng Nghĩa Vụ Thuế Ngay Bên Dưới Bảng**:
   - Hiển thị nổi bật theo đúng chuẩn C++:
     `>>> TỔNG NGHĨA VỤ THUẾ TẤT CẢ PHƯƠNG TIỆN PHẢI NỘP: $X,XXX.XX <<<`
   - Tự động cập nhật theo thời gian thực khi thêm, xóa hoặc lọc tìm kiếm.
3. **Tìm Kiếm Theo Hãng (Search by Make)**:
   - Ô tìm kiếm tức thì (live search) theo tên Hãng sản xuất.
   - Hiển thị thông báo kết quả tìm kiếm và nút "Xóa bộ lọc".
4. **Menu Sắp Xếp Lồng (Nested Sub-menu Sort)**:
   Hỗ trợ 5 tiêu chí nguyên bản trong C++:
   - `1`: Theo Hãng xe (A-Z)
   - `2`: Theo Tốc độ tối đa (Giảm dần)
   - `3`: Theo Số cửa xe hơi (Giảm dần)
   - `4`: Theo Loại động cơ (A-Z)
   - `5`: Theo Thuế nộp (Giảm dần)
5. **Quản Lý Dữ Liệu Tệp Tin & Bộ Nhớ (I/O)**:
   - **Lưu file vehicles.txt**: Tải về tệp dạng CSV chuẩn C++ (`Car,make,model,speed,doors,engine` / `Truck,make,model,speed,payload,axles`).
   - **Nạp file vehicles.txt**: Nhập file txt từ máy tính vào ứng dụng web thông qua `FileReader API`.
   - **Xuất báo cáo output.txt**: Hiển thị xem trước modal báo cáo đẹp mắt và tải về file `output.txt` chuẩn định dạng hàm `exportResultsToFile()` của C++.
   - **Đồng bộ LocalStorage**: Tự động lưu trạng thái vào trình duyệt để dữ liệu không bị mất khi tải lại trang.

---

## 🚀 4. Hướng Dẫn Sử Dụng & Khởi Chạy

### Cách 1: Khởi chạy trực tiếp (Không cần cài đặt bất kỳ phần mềm nào)
1. Mở thư mục dự án `c:\Users\Acern\OneDrive\Documents\tat ca moi thu ve prj\webquanlixe\`.
2. Nhấp đúp chuột vào file **`index.html`** để mở trực tiếp trên trình duyệt web (Google Chrome, Microsoft Edge, Firefox, Cốc Cốc, ...).
3. Trải nghiệm đầy đủ tính năng: thêm xe, sắp xếp, tìm kiếm, xuất nhập file.

### Cách 2: Khởi chạy với Node.js (Full-Stack Mode - nếu máy có cài Node.js)
```bash
# Di chuyển vào thư mục dự án
cd "c:\Users\Acern\OneDrive\Documents\tat ca moi thu ve prj\webquanlixe"

# Chạy server (thuần thư viện Node.js, không cần cài npm install)
node server.js
```
Truy cập: `http://localhost:3000` trên trình duyệt.

### Cách 3: Sử dụng VS Code Live Server
Nếu bạn đang dùng VS Code, chỉ cần click chuột phải vào `index.html` và chọn **"Open with Live Server"**.
