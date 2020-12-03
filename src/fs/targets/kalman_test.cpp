#include <i2c_t3.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP3XX.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <lin/core.hpp>

#define SEALEVELPRESSURE_HPA (1013.25)

const float pi = 3.14159265;
Adafruit_BMP3XX bmp;
Adafruit_BNO055 bno = Adafruit_BNO055(55);
double previous_clock_time;
double dt = 1 / 100;
double x_var = 0;
double vx_var = 0;
double Q_var = 2.35;
float z_o = 0;
lin::Vector2d x = {0.0, 0.0};
lin::Matrix2x2d P = {0.2, 0.0, 1.2, 0.0};
lin::Matrix2x2d Q = {0.001, 0.1, 0.1, 0.001};


void setup() {
  Wire.begin(); 
  Serial.begin(9600);
  while (!Serial);
  
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

void loop() {
  imu::Vector<3> imu_acc_reading = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  float z = bmp.readAltitude(SEALEVELPRESSURE_HPA) - z_o;

  double clock_time = millis();
  float dt = 1e-2;
  lin::Matrix2x2d F = {1.0, dt, 0.0, 1.0};
  lin::Vector2d B = {0.5*dt*dt, dt};

  lin::Vector2d x_bar = F*x + B*imu_acc_reading.z();
  P = F*P*lin::transpose(F) + Q;
  lin::Matrixd<1,2> H = {1.0, 0.0};
  
  lin::Matrixd<1,2> y 




  // delay((period * 1000) - clock_time - previous_clock_time);
  previous_clock_time = clock_time;
//   delay(1000);
}
