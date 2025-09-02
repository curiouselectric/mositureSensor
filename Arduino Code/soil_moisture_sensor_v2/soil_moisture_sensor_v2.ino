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
#include <SoftwareSerial.h>

// Request frame for the soil sensor
const byte soilSensorRequest[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B};
byte soilSensorResponse[9];

SoftwareSerial mod(3, 2); // Software serial for RS485 communication

void setup() 
{
  Serial.begin(9600); // Serial port to show the data
  mod.begin(4800);    // Initialize software serial communication at 4800 baud rate
  
}
void loop() {
  Serial.println("Getting data:");
  readHumiture();
  delay(3000);
}

void readHumiture(void) 
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
      Serial.print(soilSensorResponse[index], HEX); // Print the received byte in HEX format
      Serial.print(" ");
      index++;
    }
    Serial.println();
    
    // Parse and calculate the Moisture value
    int Moisture_Int = int(soilSensorResponse[3] << 8 | soilSensorResponse[4]);
    float Moisture_Percent = Moisture_Int / 10.0;
 
    Serial.print("Moisture: ");
    Serial.print(Moisture_Percent);
    Serial.println(" %RH");

    // Parse and calculate the Temperature value
    int Temperature_Int = int(soilSensorResponse[5] << 8 | soilSensorResponse[6]);
    float Temperature_Celsius = Temperature_Int / 10.0;
 
    // Check if temperature is negative and convert accordingly
    if (Temperature_Int > 0x7FFF)
    {
      Temperature_Celsius = 0x10000 - Temperature_Int;
      Temperature_Celsius = -Temperature_Celsius / 10.0;
    }
 
    Serial.print("Temperature: ");
    Serial.print(Temperature_Celsius);
    Serial.println(" °C");
  }
}
