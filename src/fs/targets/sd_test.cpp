#include <Arduino.h>
#include <i2c_t3.h>
#include <SPI.h>

#include <SD.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_BMP3XX.h>

#define SEALEVELPRESSURE_HPA (1013.25)
const int chipSelect = BUILTIN_SDCARD;

const float pi = 3.14159265;
Adafruit_BMP3XX bmp;
Adafruit_BNO055 bno = Adafruit_BNO055(55);
double previous_clock_time;
float dt = 1.0/100.0;

#define MAX 1e5

File fout;
float z_o = 0.0;

void setup(){
    Serial.begin(9600);
    while (!Serial){}

    if(!SD.begin(chipSelect)){
        Serial.println("init fail");
        while(true){}
    }
    Serial.println("init success");

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

void loop(){
  imu::Vector<3> imu_acc_reading = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  float z = bmp.readAltitude(SEALEVELPRESSURE_HPA) - z_o;
  float u = imu_acc_reading.z();
  float clock_time = millis();
  

  Serial.printf("0,%e,%e\n", z, u);
  fout.printf("0,%e,%e\n", z, u);
  delay(dt);
}