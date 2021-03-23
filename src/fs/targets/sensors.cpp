#include <i2c_t3.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP3XX.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <string>


#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BNO055 bno = Adafruit_BNO055(55);

void setup() {
  Wire.begin(); 
  Serial.begin(9600);
  while (!Serial);
  
  Serial.println("Orientation Sensor Test"); Serial.println("");
  if(!bno.begin())
  {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  delay(1000);  
  bno.setExtCrystalUse(true);
  Serial.println("teensy started");
}

void loop() {
  unsigned char sys_c, gyro_c, accel_c, mag_c;

  bno.getCalibration(&sys_c, &gyro_c, &accel_c, &mag_c);
  imu::Quaternion quat = bno.getQuat();

  char buf[60];
  snprintf(buf, 60, "%d;%d;%d;%d;%0.3lf;%0.3lf;%0.3lf;%0.3lf", sys_c, gyro_c, accel_c, mag_c, quat.w(), quat.x(), quat.y(), quat.z());
  Serial.println(buf);
  
  delay(500);
}
