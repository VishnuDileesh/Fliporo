#include <Arduino.h>
#include <Wire.h>

const int MPU_ADDR = 0x68;

float GyroX, GyroY, GyroZ; 
float gyroAngleX, gyroAngleY, gyroAngleZ;
float roll, pitch, yaw;
float GyroErrorX, GyroErrorY, GyroErrorZ;
float elapsedTime, currentTime, previousTime;
int c = 0;


void setup() {
  Serial.begin(19200);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
  delay(20); 
}

void loop() {
  // === Read Gyroscope data === //
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x43); // Gyro data first register address 0x43
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  
  // For a 250deg/s range we need to divide first the raw value by 131.0, according to the datasheet
  GyroX = (Wire.read() << 8 | Wire.read()) / 131.0;
  GyroY = (Wire.read() << 8 | Wire.read()) / 131.0;
  GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;

  // Print the values on Serial Monitor
  Serial.print("Gyro: ");
  Serial.print("X = "); Serial.print(GyroX);
  Serial.print(" | Y = "); Serial.print(GyroY);
  Serial.print(" | Z = "); Serial.println(GyroZ);
  
  delay(100);
}

