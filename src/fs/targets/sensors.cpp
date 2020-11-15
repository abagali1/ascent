#include <i2c_t3.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP3XX.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
  
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BMP3XX bmp; // I2C
Adafruit_BNO055 bno = Adafruit_BNO055(55);

void setup() {
  Wire.begin(); 
  Serial.begin(9600);
  while (!Serial);
  
  Serial.println("BMP388 test");
  if (!bmp.begin_I2C()) {
    Serial.println("Could not find a valid BMP3 sensor, check wiring!");
    while (1);
  }
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  
  Serial.println("Orientation Sensor Test"); Serial.println("");
  if(!bno.begin())
  {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  delay(1000);  
  bno.setExtCrystalUse(true);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Serial.println("teensy started"); 
}

void loop() {
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  String bno_string = "bno: " + String(euler.x()) + "," + String(euler.y()) +","+ String(euler.z());

  
  if (! bmp.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }
  String bmp_string = "bmp: " + String(bmp.temperature)+"*C, "+String(bmp.pressure/100.0)+" hPa, "+bmp.readAltitude(SEALEVELPRESSURE_HPA)+" m";
  String sender = bno_string +"; "+ bmp_string;
  char buf[sender.length()];
  sender.toCharArray(buf, sender.length());
  Serial.println(buf);
  delay(500);
}