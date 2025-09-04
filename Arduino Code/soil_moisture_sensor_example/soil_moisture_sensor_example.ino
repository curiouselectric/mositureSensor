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

bool changeIDflag = false;

void setup() {
  Serial.begin(9600);  // Serial port to show the data
  soilMoistureSensor.begin();
}
void loop() {

  // Flip around the ID - this test the ID change sub-routine
  if (changeIDflag == false) {
    soilMoistureSensor.changeID(1, 2);
    changeIDflag = true;
    Serial.println("ID should be 2");
  } else {
    soilMoistureSensor.changeID(2, 1);
    changeIDflag = false;
    Serial.println("ID should be 1");
  }


  Serial.println("Getting data:");
  // This will only return data 
  if (soilMoistureSensor.readHumiture(1))  // This line gets the data from the sensor.
  {
    Serial.print("Moisture: ");
    Serial.print(soilMoistureSensor.moisturePercent);
    Serial.println(" %RH");

    Serial.print("Temperature: ");
    Serial.print(soilMoistureSensor.soilTemperatureC);
    Serial.println(" °C");
  }

  delay(5000);
}
