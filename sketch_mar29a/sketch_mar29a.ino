// Khai báo chân kết nối với cảm biến
const int pinAO = A0;   // Chân analog kết nối với chân AO của cảm biến
const int pinCLK = 3;   // Chân kỹ thuật số kết nối với chân CLK của cảm biến
const int pinSI = 2;    // Chân kỹ thuật số kết nối với chân SI của cảm biến

void setup() {
  // Khởi tạo chân kết nối với cảm biến
  pinMode(pinAO, INPUT);
  pinMode(pinCLK, OUTPUT);
  pinMode(pinSI, OUTPUT);
  
  // Bắt đầu giao tiếp với cảm biến
  digitalWrite(pinCLK, LOW);
  digitalWrite(pinSI, LOW);
  
  // Khởi tạo Serial Monitor để theo dõi dữ liệu từ cảm biến
  Serial.begin(9600);
}

void loop() {
  // Bắt đầu lấy dữ liệu từ cảm biến
  digitalWrite(pinSI, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinSI, LOW);
  
  // Đợi cho cảm biến lấy dữ liệu
  delayMicroseconds(10);
  
  // Đọc dữ liệu từ cảm biến
  uint16_t sensorData[128];
  for (int i = 0; i < 128; i++) {
    digitalWrite(pinCLK, HIGH);
    delayMicroseconds(10);
    sensorData[i] = analogRead(pinAO); // Đọc dữ liệu từ cảm biến
    digitalWrite(pinCLK, LOW);
    delayMicroseconds(10);
  }
  
  // In dữ liệu ra Serial Monitor
  for (int i = 0; i < 128; i++) {
    Serial.print(sensorData[i]);
    Serial.print("\t");
  }
  Serial.println(); // Xuống dòng sau khi in hết dữ liệu
  
  // Đợi một khoảng thời gian trước khi lấy dữ liệu tiếp theo

}