#include <i2c_t3.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP3XX.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <SD.h>
#include <matrix.hpp>

#define SEALEVELPRESSURE_HPA (1013.25)
#define MAX 1000
const int chipSelect = BUILTIN_SDCARD;

const float pi = 3.14159265;
Adafruit_BMP3XX bmp;
Adafruit_BNO055 bno = Adafruit_BNO055(55);
double previous_clock_time;
float dt = 1.0/100.0;
File fout;

int i = 0;
float z_o = 0;
Matrix x(2,1);
Matrix P(2,2);
Matrix Q(2,2);
Matrix R(1,1);
Matrix f(2,2);
Matrix B(2,1);
Matrix H(1,2);

void setup() {
  Wire.begin(); 
  Serial.begin(9600);
  while (!Serial);
  
  if(!SD.begin(chipSelect)){
        Serial.println("init fail");
        while(true){}
  }
  fout = SD.open("test.txt", FILE_WRITE);
  if(fout){
        Serial.println("write test");
        fout.println("test write");
        fout.close();
        Serial.println("write test success");
    }else{
        Serial.println("Fail to open test.txt");
        while(true) {}
    }

  // Initialize BMP
  Serial.println("bmp read");
  if (!bmp.begin_I2C()) {
    Serial.println("Could not find a valid BMP3 sensor, check wiring!");
    while (1);
  }
  Serial.println("fin bmp");
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);

  // Initialize IMU
  Serial.println("bno read");
  if(!bno.begin())
  { 
    Serial.print("Could not find a valid BNO05 IMU, check wiring!");
    while(1);
  }

  delay(1000);

  Serial.println("initial reading");
  bmp.readAltitude(SEALEVELPRESSURE_HPA);

  Serial.println("reading");
  fout = SD.open("init.txt", FILE_WRITE);
  for(int j=0;j<1000;j++){
    float z = bmp.readAltitude(SEALEVELPRESSURE_HPA);
    z_o += z;
    fout.println(z);
    if(j % 100 == 1){
      Serial.println(j);
    }
  }
  z_o /= 1000;
  fout.close();
  fout = SD.open("data.txt", FILE_WRITE);
  bno.setExtCrystalUse(true);

  Serial.println("init successsss");

  x.fill(std::vector<float>({0.0, 0.0}));
  P.fill(std::vector<float>({0.2, 0, 0, 1.2}));
  Q.fill(std::vector<float>({0.001, 0.1, 0.1, 0.001}));
  R.fill(std::vector<float>({4.0}));
  f.fill(std::vector<float>({1, dt, 0, 1}));
  B.fill(std::vector<float>({0.5 * dt * dt, dt}));
  H.fill(std::vector<float>({1,0}));

  pinMode(1, OUTPUT);
  
  digitalWrite(1, HIGH);
  delay(1000);
  digitalWrite(1, LOW);
  
  delay(10000);

  digitalWrite(1, HIGH);
  delay(1000);
  digitalWrite(1, LOW);

  previous_clock_time = millis();
}

void loop() {
  imu::Vector<3> imu_acc_reading = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  float u = imu_acc_reading.z();
  float clock_time = millis();

  Matrix z(1,1);
  z.fill(std::vector<float>({bmp.readAltitude(SEALEVELPRESSURE_HPA) - z_o}));

  Matrix x_bar = (f * x) + (B * u);
  Matrix P_bar = ((f * P) * f.transpose()) + Q;

  Matrix y = z - (H * x_bar);
  Matrix S = (H * P_bar * H.transpose()) + R;
  Matrix K = P_bar * H.transpose() * S.inverse();
  P = P_bar - (K * H * P_bar);
  x = x_bar + K * y;

  Serial.println(x.at(0,0));

  delay((dt * 1000) - (clock_time - previous_clock_time));
}
