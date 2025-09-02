/*
 *  Soil Mositure Sensor Code Example
 *  Used for Curious Electric Company RS485 mositure sensor
 *  Available here: 
 *  Blog post on development here: 
 *  
 *  
 * Reference post: https://how2electronics.com/connecting-rs485-soil-moisture-temperature-sensor-to-arduino/
 * 
 */
#include "soil_moisture_rs485.h"

void setup() {
  Serial.begin(9600);  // Serial port to show the data
  
  soilMoistureSensor.begin();
}
void loop() {
  Serial.println("Getting data:");

  soilMoistureSensor.readHumiture();      // This line gets the data from the sensor.

  Serial.print("Moisture: ");
  Serial.print(soilMoistureSensor.moisturePercent);
  Serial.println(" %RH");

  Serial.print("Temperature: ");
  Serial.print(soilMoistureSensor.soilTemperatureC);
  Serial.println(" °C");

  delay(3000);
}
