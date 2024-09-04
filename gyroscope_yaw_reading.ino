#include<Wire.h>
const int MPU=0x68; 
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
long base_GyZ = 0;


void  setup(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  
  Wire.write(0);    
  Wire.endTransmission(true);
  Serial.begin(9600);

  for (int i = 0; i < 1000; i++) {
    read();
    base_GyZ += GyZ;
    delay(1);
  }
  base_GyZ /= -1000;

}


void read() {
  Wire.beginTransmission(MPU);
  Wire.write(0x47);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 2, true); 
  // AcX=Wire.read()<<8|Wire.read();    
  // AcY=Wire.read()<<8|Wire.read();  
  // AcZ=Wire.read()<<8|Wire.read();  
  GyZ=Wire.read()<<8|Wire.read();  
  // GyX=Wire.read()<<8|Wire.read();  
  // GyY=Wire.read()<<8|Wire.read(); 
}


void loop(){

  static unsigned long t = millis();
  static float yaw = 0;


  read();


  yaw += (GyZ+base_GyZ)*1.0 * (millis() - t) / 1000 / 131;
  t = millis();

  Serial.println(yaw);
}