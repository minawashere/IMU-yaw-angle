# Arduino gyroscope code to fetch the yaw angle with offset correction
Calculating offset:

```
for (int i = 0; i < 1000; i++) {
    read();
    base_GyZ += GyZ;
    delay(1);
  }
  base_GyZ /= -1000;
```
Fetching multiple values and calculate their average to calculate the sensor's error.

---
```
  Wire.beginTransmission(MPU);
  Wire.write(0x47);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 2, true);
``` 
The *0x47* is the GyZ register adress, and we request 2 bits from the sensor corresponding to the GyZ data. 
Register adresses can be obtained from the register map in the [datasheet](https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf)

---
```
  yaw += (GyZ+base_GyZ)*1.0 * (millis() - t) / 1000 / 131;
  t = millis();
```
Basic intergration (by left Reimann sum) to obtain the angle from the angular velocity.
division by **131** to transform the gyro lsb to degrees, this is for the range +- 150 deg/ sec. It can be set by configuring the register.

  
