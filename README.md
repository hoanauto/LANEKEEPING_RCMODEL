# LANEKEEPING_RCMODEL
1. Khai báo các chân của linear TSL1401 gồm: VCC, GND, AO, SI, CLK được kết nối với Arduino mega 2560.
2. Khai báo thư viện Servo trong Arduino
3. Set up chân của Linear: AO – INPUT, SI – OUTPUT, ClK – OUTPUT.
4. Set up chân của H brid: ENA , IN1, IN2 – OUTPUT.
5. Tạo hàm đọc tín hiệu từ Linear TSL1401 và gán tín hiệu vừa đọc vào mảng gồm 128 kí tự.
6. Xử lý ảnh được gán vào mảng bằng phương pháp như sau:
- Chia 128 Pixel được gán thành 2 mảng gồm 1 mảng giảm từ 63 (vị trí của Pixel thứ 63) về 0 để xác định lane trái, 1 mảng tăng từ 64 (vị trí của Pixel thứ 64) đến 127 để xác định lane phải. 
- Tạo 1 chương trình khác để xuất tín hiệu ra của Linear TSL1401 và dùng tool vẽ lại sơ đồ để phân tích tín hiệu thay đổi giữa giải màu trắng với giải màu đen.
- Tạo biến đếm Pixel màu trắng lane trái (countL), khi Pixel có giá trị màu trắng thì biến đếm tăng lên 1 đơn vị. Tương tự với lane phải và biến đếm (countR).
7. Tính toán góc quay của Servo motor dựa vào biến đếm thu được ở bước 6:
- Tạo biến “denta = countL – countR” để so sánh Pixel màu trắng của lane phải và trái. Nếu giá trị denta dương thì số lượng Pixel màu trắng của lane trái nhiều hơn lane phải từ đây có thể suy ra xe đang có xe hướng lệch sang lane phải. Trường hợp denta âm thì ngược lại, xe đang có xu hương lệch sang lane phải.  
-  Do trong quá trình hoạt động, Linear có thể bị nhiễu bởi nhiều nguyên nhân khác nhau vì thế nếu dùng trực tiếp tín hiệu Pixel trắng đêr điều khiển servo sẽ làm xe điều khiến thiếu chính xác. Để xe được điều khiển ổn định thì cần chọn sai số cho denta và gán vào hàm điều kiện if.
- Từ denta dùng hàm map() để tính toán ra góc quay của Servo theo denta.
