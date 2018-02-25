// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
//#define ONEWIRE_SEARCH

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

/*
 * The setup function. We only start the sensors here
 */
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");
/*
  int result = oneWire.reset();
  Serial.print("reset resulted: ");
  Serial.println(result);
  delay(100);

  uint8_t address;
  uint8_t address2;
  uint8_t address3;
  uint8_t address4;
  
  oneWire.reset_search();
  
  int r_search = oneWire.search(&address);
  Serial.print("search resulted: ");
  Serial.println(r_search);
  Serial.print("address: ");
  Serial.println(address);
  
  if (r_search)
  {
    r_search = oneWire.search(&address2);
    Serial.print("search resulted: ");
    Serial.println(r_search);
    Serial.print("address2: ");
    Serial.println(address2);
  }
*/

  // Start up the library
  sensors.begin();
}



/*
 * Main function, get and show the temperature
 */
void loop(void)
{ 
  uint8_t deviceCount = 0;
  Serial.print("Device count : ");
  deviceCount = sensors.getDeviceCount();
  Serial.println(deviceCount);
  
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  for (uint8_t i=0 ; i < deviceCount; i++)
  {
    Serial.print("Temperature for the device ");
    Serial.print(i+1);
    Serial.print(" (index ");
    Serial.print(i);
    Serial.print(") is: ");
    Serial.println(sensors.getTempCByIndex(i));
  }
  delay(2000);
}

