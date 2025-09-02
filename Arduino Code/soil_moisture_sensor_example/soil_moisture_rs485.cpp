
#include "soil_moisture_rs485.h"
#include <SoftwareSerial.h>

moistureSensor soilMoistureSensor;

/****************************************************************************/
/***       Local Variable                                                 ***/
/****************************************************************************/
#define sensorBaudRate  4800
#define sensorTx        2 
#define sensorRx        3 
// Request frame for the soil sensor
const byte soilSensorRequest[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B};
byte soilSensorResponse[9];   // Always expecting 9 bytes from this sensor

SoftwareSerial mod(sensorRx, sensorTx); // Software serial for RS485 communication

/****************************************************************************/
/***       Class member Functions                                         ***/
/****************************************************************************/

void moistureSensor::begin(void)
{
    /* Start Serial */
    mod.begin(sensorBaudRate);    // Initialize software serial communication at 4800 baud rate
}

void moistureSensor::readHumiture(void) 
{
  // Send the request frame to the soil sensor
  mod.write(soilSensorRequest, sizeof(soilSensorRequest));
  delay(10);
  
  // Wait for the response from the sensor or timeout after 1 second
  unsigned long startTime = millis();
  
  while (mod.available() < 9 && millis() - startTime < 1000)
  {
    delay(1);
  }
 
  if (mod.available() >= 9) // If valid response receivedPulse sensor modules
  {
    // Read the response from the sensor
    byte index = 0;
    while (mod.available() && index < 9)
    {
      soilSensorResponse[index] = mod.read();
      //Serial.print(soilSensorResponse[index], HEX); // Print the received byte in HEX format
      //Serial.print(" ");
      index++;
    }
    //Serial.println();
    
    // Parse and calculate the Moisture value
    int Moisture_Int = int(soilSensorResponse[3] << 8 | soilSensorResponse[4]);
    moisturePercent = Moisture_Int / 10.0;
 
    // Parse and calculate the Temperature value
    int Temperature_Int = int(soilSensorResponse[5] << 8 | soilSensorResponse[6]);
    soilTemperatureC = Temperature_Int / 10.0;
 
    // Check if temperature is negative and convert accordingly
    if (Temperature_Int > 0x7FFF)
    {
      soilTemperatureC = 0x10000 - Temperature_Int;
      soilTemperatureC = -soilTemperatureC  / 10.0;
    }
  }
}
