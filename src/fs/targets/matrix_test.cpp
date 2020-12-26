#include "arduino.h"
#include "matrix.hpp"
#include <vector>

Matrix x(2,1);
Matrix b(2,1);
Matrix f(2,2);

void setup(){
    Serial.begin(9600);
    x.fill(std::vector<float>({1, 2}));
    b.fill(std::vector<float>({3, 4}));
    f.fill(std::vector<float>({1, 0, 0, 1}));
    Serial.println("inited");
    delay(1000);
}

void loop(){
    Matrix r = x + b;
    Serial.println(r.matrixData.at(0));
    Serial.println(r.matrixData.at(1));
    Serial.println();
    r = f * x;
    Serial.println(r.matrixData.at(0));
    Serial.println(r.matrixData.at(1));
    Serial.println("----------");
}