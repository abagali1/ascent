#include <Arduino.h>
#include <i2c_t3.h>
#include <SPI.h>

#include <SD.h>
#include <Adafruit_BNO055.h>

#define MAX 1e3

File fout;
Adafruit_BNO055 bno;
const int chipSelect = BUILTIN_SDCARD;
int i = 0;

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

    Serial.println("Orientation Sensor Test"); Serial.println("");
    if(!bno.begin()){
        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        while(1);
    }
    delay(1000);  
    bno.setExtCrystalUse(true);

    Serial.println("init finished");
    fout = SD.open("data.txt", FILE_WRITE);
}

void loop(){
    imu::Vector<3> imu_acc_reading = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
    fout.printf("%e %e %e\n", imu_acc_reading.x(), imu_acc_reading.y(), imu_acc_reading.z());
    if(i > MAX){
        Serial.println("test finished");
        fout.close();
        while(true){}
    }
    if(!(i % 100))
        Serial.println(i);
    i++;
    delay(100);
}
