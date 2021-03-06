//SD Karte
#include <SPI.h>
#include <SD.h>

int pinCS = 53;
File myFile;

//UHR
#include <Wire.h>
#include <RtcDS1307.h>
RtcDS1307<TwoWire> Rtc(Wire);

//THERMOMETER

#include <OneWire.h> 
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2 

OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);



 
void setup(void) 
{ 
 Serial.begin(9600); 
 sensors.begin(); 
 Rtc.Begin();
 pinMode(pinCS, OUTPUT);
   if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
   myFile = SD.open("test.txt", FILE_WRITE);
    myFile.println("Time; Temperature °C");
    myFile.close(); 
    

}

void loop(void) 
{ 
 //Temp
 sensors.requestTemperatures(); 

 //UHR
 RtcDateTime now = Rtc.GetDateTime();


   
  //Anzeige
 Serial.print("Temperatur um ");
 printDateTime(now);
 Serial.print(": ");
 Serial.print(sensors.getTempCByIndex(0)); 
 Serial.print("°C");
 Serial.println();

//SD Karte
   myFile = SD.open("test.txt", FILE_WRITE);
  if (myFile) {
    myFile.print("; ");    
    myFile.println(sensors.getTempCByIndex(0));
    myFile.close(); 
  }
  
  else {
    Serial.println("error opening test.txt");
  }

 delay(10000);
 
}


#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u:%02u:%02u"),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.print(datestring);
    
    myFile = SD.open("test.txt", FILE_WRITE);  
    myFile.print(datestring);
    myFile.close(); 

    
}