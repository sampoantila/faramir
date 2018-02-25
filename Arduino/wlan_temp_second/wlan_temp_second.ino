#include <Arduino.h>

#include <SoftwareSerial.h>
#define DEBUG true

#define OK 1
#define ERROR 0

// make RX Arduino line is pin 2, make TX Arduino line is pin 3.
// This means that you need to connect the TX line from the esp to the Arduino's pin 2
// and the RX line from the esp to the Arduino's pin 3
#define rxPin 2
#define txPin 3

#define SSID "Reepicheep"
#define PASS "sakoulu0"

#define SERVERIP "88.113.15.213" // http://aslan.datacodex.fi
#define METERAPI "/meterapi/api.php/meters"


SoftwareSerial esp8266(rxPin, txPin);

/*
 * Setup
 */
void setup()
{
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  Serial.begin(115200); // for Arduino IDE serial monitor
  esp8266.begin(9600); // your esp's baud rate might be different

  waitForSystemReady(10000);

  send("AT+CWMODE=1");
  send("AT+CIPMUX=0"); // set single connection mode

  // Connect Reepicheep
  String cmd="AT+CWJAP=\"";
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";
  send(cmd, 15000); // connection takes long time

  send("AT+CWJAP?"); // query if connected
  send("AT+CIFSR"); // query IP address
}

int waitForSystemReady(const int wait)
{
  String response = "";
  long starttime = millis();
  long timeout = starttime + wait;
  bool initialized = false;

  Serial.println("Wait ESP to become ready...");

  send("AT"); // reset module
  send("AT+CIOBAUD=9600");
  
  /*
  while(timeout > millis())
  {
    if (esp8266.available())
    {
      response += readEspData();
      if (esp8266.available() == 0 && response.indexOf("System Ready") > -1)
      {
        initialized = true;
        long delta = millis() - starttime;
        Serial.print("System ready, took ");
        Serial.print(delta);
        Serial.println(" ms");
        break;
      }
    }
  }
  */
/*
  if (DEBUG)
  {
    Serial.println("sendEspData response = '" + response + "'");
  }
*/
/*
  if (initialized == false)
  {
    Serial.println("Error: module init failed");
  }
  */
}

/*
 * Loop
 */
void loop()
{
  static bool first = true;
  String command = "";

  if (first)
  {
    Serial.println("### Main Loop started");
    first = false;
  }

  if (esp8266.available()) // check if the esp is sending a message
  {
    String readval = read();
    Serial.println("read:'"+readval+"'");
  }

  if (Serial.available())
  {
    // the following delay is required because otherwise the arduino will read the first letter of the command but not the rest
    // In other words without the delay if you use AT+RST, for example, the Arduino will read the letter A send it, then read the rest and send it
    // but we want to send everything at the same time.
    delay(1000);

    while(Serial.available()) // read the command character by character
    {
      // read one character
      command+=(char)Serial.read();
    }

    send(command);
  }

  // read temperature
  int m1_id = 1;
  float m1_value = 25.3;

  // do temperature storing
  //storeMeterValue(m1_id, m1_value);

  //delay(5000);
}

void storeMeterValue(int meter_id, float value)
{

  // AT+CIPSTART="TCP","88.113.15.213",80
  String cmd = "AT+CIPSTART=\"TCP\",\""; //set up TCP connection
  cmd += SERVERIP;
  cmd += "\",80";
  send(cmd);

  // AT+CIPSEND=36
  // GET /meterapi/api.php/meters/1/25.3
  cmd = "GET ";
  cmd += METERAPI;
  cmd += "/";
  cmd += meter_id;
  cmd += "/";
  cmd += value;
  cmd += "\r\n";

  esp8266.print("AT+CIPSEND="); // send TCP data
  esp8266.println(cmd.length());

  delay(1000);
  if (Serial.find(">"))
  {
    Serial.println(cmd);
  }
  else
    Serial.println("AT+CIPSEND error");

  String response = read();
  Serial.println(response);
}

void send(String command)
{
  send(command, 2000);
}

void send(String command, int timeout)
{
  String response = sendEspData(command, timeout, DEBUG);

  //if (response.indexOf("OK") > -1)
    //return OK;
  //else
    //return ERROR;
}

void send(String command, String replyToWait, int waitTime)
{
  String retval = sendEspData(command, waitTime, false);
  if (retval.indexOf(replyToWait) > -1)
  {

  }
}

String read()
{
  return read(2000);
}

String read(int wait)
{
  String response = "";
  long int timeout = millis() + wait;

  while(timeout > millis())
  {
    if (esp8266.available())
    {
      response += readEspData();
    }
  }

  return response;
}

String readEspData()
{
  String retval = "";

  while(esp8266.available())
  {
    // The esp has data so display its output to the serial window
    char c = esp8266.read(); // read the next character.
    retval += c;
  }

  return retval;
}

String sendEspData(String command, int wait, bool debug)
{
  String response = "";
  long timeout = millis() + wait;

  // send characters to the esp8266
  esp8266.println(command);

  response = read(wait);

  if (debug)
  {
    Serial.println(response);
  }

  return response;
}
