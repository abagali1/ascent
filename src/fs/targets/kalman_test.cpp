#include <i2c_t3.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP3XX.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <lin/core.hpp>
#include <SD.h>
#define SEALEVELPRESSURE_HPA (1013.25)
const int chipSelect = BUILTIN_SDCARD;

const float pi = 3.14159265;
Adafruit_BMP3XX bmp;
Adafruit_BNO055 bno = Adafruit_BNO055(55);
double previous_clock_time;
float dt = 1 / 100;
File fout;

float z_o = 0;
lin::Vector2d x = {0.0, 0.0};
lin::Matrix2x2d P = {0.2, 0.0, 1.2, 0.0};
lin::Matrixd<1,1> R = {4};

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
  fout = SD.open("data.txt", FILE_WRITE);

  // Initialize BMP
  if (!bmp.begin_I2C()) {
    Serial.println("Could not find a valid BMP3 sensor, check wiring!");
    while (1);
  }
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);

  // Initialize IMU
  if(!bno.begin())
  { 
    Serial.print("Could not find a valid BNO05 IMU, check wiring!");
    while(1);
  }
  delay(1000);
  bno.setExtCrystalUse(true);
  previous_clock_time = millis();
  for(int i=0;i<5;i++){
    z_o += bmp.readAltitude(SEALEVELPRESSURE_HPA);
  }
  z_o /= 5;
}

lin::Matrix2x2d inv(lin::Matrix2x2d &A) {
    double a = A(0);
    double b = A(1);
    double c = A(2);
    double d = A(3);

    double det=a*d-b*c;
    lin::Matrix2x2d res = {d/det, -b/det, -c/det, a/det};
    return res;
}

void loop() {
  imu::Vector<3> imu_acc_reading = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  float z = bmp.readAltitude(SEALEVELPRESSURE_HPA) - z_o;
  float u = imu_acc_reading.z();
  float clock_time = millis();

  Serial.println(dt);
  fout.printf("0,%e,%e\n", u, z); // dt, az, z

  delay((dt * 1000) - (clock_time - previous_clock_time));
  previous_clock_time = clock_time;;
}
