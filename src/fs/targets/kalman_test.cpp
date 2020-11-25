#include <i2c_t3.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP3XX.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <MatrixMath.h>
#include <Gaussian.h>

#define SEALEVELPRESSURE_HPA (1013.25)
const float pi = 3.14159265;
Adafruit_BMP3XX bmp;
Adafruit_BNO055 bno = Adafruit_BNO055(55);
double previous_clock_time;
double dt = 1 / 100;
mtx_type F[2][2] = {{1, dt}, {0, 1}};
mtx_type x[2][1] = {{0}, {0}};
mtx_type B[2][2] = {{0.5*dt*dt, 0}, {0, dt}};
mtx_type u[2][1] = {{0}, {0}}; //0s for initialization?
mtx_type FT[2][2];
Matrix.Transpose((mtx_type*)F, 2, 2, FT);
double x_var = 0;
double vx_var = 0;
mtx_type P[2][2] = {{x_var, 0}, {0, vx_var}};
double Q_var = 2.35;


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
}

void loop() {
  imu::Vector<3> imu_acc_reading = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  double pressure = bmp.pressure / 100.0;

  double clock_time = millis();

  double u = imu_acc_reading.x();
  double Bu[2][1] = {{0.5 * dt * dt * u}, 
                    {dt * u}};
  double Fx[2][1] = {{1 * x[0][0] + dt * x[1][0]},
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

mtx_type kalman_predict(){
  mtx_type Fx;
  Matrix.Multiply((mtx_type*)F, (mtx_type*)x, 2, 2, 1, Fx);
  mtx_type Bu;
  Matrix.Multiply((mtx_type*)B, (mtx_type*)u, 2, 2, 1, Bu);
  mtx_type prior;
  Matrix.Add((mtx_type*)Fx, (mtx_type*)Bu, 2, 1, prior);
  
  mtx_type FP;
  Matrix.Multiply((mtx_type*)F, (mtx_type*)P, 2, 2, 2, FP);
  mtx_type FPFT;
  Matrix.Multiply((mtx_type*)FP, (mtx_type*)FT, 2, 2, 2, FPFT);
  Matrix.Add((mtx_type*)FPFT, (mtx_type*)Q, 2, 2, P);
  return prior;
}
void process_noise(double mean, double variance){
  double [2][2] to_return;
  for(int i = 0; i<2; i++){
    for(int j = 0; j<2; j++){
      double x = random(0, 999)/1000*random(-3*variance, 3*variance)
      to_return [i][j] = (1/sqrt(2*variance*pi))*(exp((-1*pow(x-mean, 2))/(2*variance))) 
    }
  }
  return to_return
}