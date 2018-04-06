#include <bmp280.h>

bmp280 sensor(10);

void setup() {
  Serial.begin(9600);
  
  sensor.initSPI();
  if (!sensor.connect()) {  
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }

}

void loop() {
  Serial.println(sensor.readPress());
}
