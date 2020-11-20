#include <i2c_t3.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP3XX.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
  
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BMP3XX bmp;
Adafruit_BNO055 bno = Adafruit_BNO055(55);
double previous_clock_time;
double x[2][1] = {{0}, {0}};
double period = 1 / 100;

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
  
  // Initialize IMU
  if(!bno.begin())
  {
    Serial.print("Could not find a valid BNO05 IMU, check wiring!");
    while(1);
  }
  delay(1000);
  bno.setExtCrystalUse(true);
  previous_clock_time = millis();
}

void loop() {
  imu::Vector<3> imu_acc_reading = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);

  double clock_time = millis();
  double u = imu_acc_reading.x();
  double Bu[2][1] = {{0.5 * period * period * u}, 
                    {period * u}};
  double Fx[2][1] = {{1 * x[0][0] + period * x[1][0]},
                     {x[1][0]}};

  double x_bar[2][1] = {{Fx[0][0] + Bu[0][0]}, 
                        {Fx[1][0] + Bu[1][0]}};

  Serial.println("X" + String(x_bar[0][0]));
  Serial.println("U" + String(u));
//   Serial.println(String(imu_acc_reading.x()) + ";" + String(imu_acc_reading.y()) + ";" + String(imu_acc_reading.z()));

  delay((period * 1000) - clock_time - previous_clock_time);
  x[0][0] = x_bar[0][0];
  x[1][0] = x_bar[1][0];
  previous_clock_time = clock_time;
//   delay(1000);
}