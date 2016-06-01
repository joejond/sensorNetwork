#include <ESP8266WiFi.h>
#include <ModbusTCPSlave.h>


ModbusTCPSlave Mb;

unsigned long timer;
unsigned long checkRSSIMillis;

void setup()
{

  //Mb.begin("Telecom-28778737", "passwordwificasa47893000", ip, gateway, subnet);
  Mb.begin("TP-LINK_3E50", "02184319");
  Serial.begin(19200);  
  delay(1000);
  Mb.MBInputRegister[0] = 100;
  Mb.MBInputRegister[1] = 65500;
  Mb.MBInputRegister[2] = 300;
  Mb.MBInputRegister[3] = 400;
  Mb.MBInputRegister[4] = 500;

  Mb.MBHoldingRegister[0] = 1;
  Mb.MBHoldingRegister[1] = 2;
  Mb.MBHoldingRegister[2] = 3;
  Mb.MBHoldingRegister[3] = 4;
  Mb.MBHoldingRegister[4] = 5;

}

void loop()
{
  Mb.Run();
  delay(10);
  int SerialData = Serial.read();
  if (millis() - timer >= 1000) 
  {
    timer = millis();
    Mb.MBInputRegister[1]++;
    Mb.MBHoldingRegister[0] = Serial.read();
  }

  if (millis() - checkRSSIMillis >= 10000) 
  {
    checkRSSIMillis = millis();
    Mb.MBInputRegister[0] = checkRSSI();
  }
}

/*****FUNZIONI*****/

byte checkRSSI() {
  byte quality;
  long rssi = WiFi.RSSI();
  if (rssi <= -100)
    quality = 0;
  else if (rssi >= -50)
    quality = 100;
  else
    rssi = rssi + 100;
  quality = byte(rssi * 2);

  return quality;
}
