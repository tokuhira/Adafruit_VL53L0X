/* This example shows how to take
range measurements with the VL53L0X and M5Stack.

The range readings are in units of mm. */

#include <M5Stack.h>
#include <Wire.h>
#include "Adafruit_VL53L0X.h"
#include <SPI.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup()
{
  Serial.begin(115200);  // start serial for output
  Serial.println("VLX53LOX test started.");
    
  M5.begin();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(10);
  delay(1000);
    
  
  Wire.begin();

  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
}

void loop()
{
  VL53L0X_RangingMeasurementData_t measure;

  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  M5.Lcd.fillScreen(BLACK);
  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.print(measure.RangeMilliMeter);
    M5.Lcd.print("mm");
    Serial.print("ambient count: "); Serial.println(measure.AmbientRateRtnMegaCps);
    Serial.print("signal count: ");  Serial.println(measure.SignalRateRtnMegaCps);
    Serial.print("distance ");       Serial.println(measure.RangeMilliMeter);
    Serial.print("status: ");        Serial.println(measure.RangeStatus);
    Serial.println();
    delay(50);
  } else {
    return;
  }
}
