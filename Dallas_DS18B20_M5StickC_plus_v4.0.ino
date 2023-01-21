// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>
#include <M5StickCPlus.h>
#include "BluetoothSerial.h"

// Data wire is plugged into port 32 on the M5stick
#define ONE_WIRE_BUS 32

// BT Parameters
#define BT_WAITTIME 30
#define BT_STARTFLAG 18
#define BT_ACK 19
#define BT_ABORD 27

BluetoothSerial SerialBT;

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

//VariablesMax y Min
float maxTemp =-100;
float minTemp=100;
unsigned long tiempo1 = 0;
unsigned long tiempo2 = 0;


void setup(void)
{
   M5.begin();
   sensors.begin();
   tiempo1 = millis();
   Serial.begin(115200);
   
   // BT Name
   SerialBT.begin("TerC_Plus");
   
}


void loop(void)
{ 
   sensors.requestTemperatures(); // Send the command to get temperatures
   float tempC = sensors.getTempCByIndex(0);

    // Maxima y Minima
    if (tempC>maxTemp){maxTemp = tempC;}
    if (tempC<minTemp){minTemp = tempC;}

    M5.update();  // Lectura de estado pulsadores
    if (M5.BtnA.wasPressed()) {  // Boton A
      M5.Lcd.writecommand(ST7789_DISPON);
      M5.Axp.ScreenBreath(9); // Brillo de pantalla
      tiempo1 = millis();
    } 

     if (M5.BtnB.wasPressed()) {  // Boton B
       maxTemp = tempC;
       minTemp = tempC;
    }
  tiempo2 = millis();
  if(tiempo2 > (tiempo1+2000)){  //Si ha pasado 5 segundo ejecuta el IF
  tiempo1 = millis();
 
  // Check if reading was successful
  if(tempC != DEVICE_DISCONNECTED_C) 
  {
    // Temperatura Actual
    M5.Lcd.writecommand(ST7789_DISPOFF);
    M5.Axp.ScreenBreath(0); // Brillo de pantalla
    M5.Lcd.setRotation(3);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(30, 5);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(3);
    M5.Lcd.println(tempC);
    M5.Lcd.setCursor(120, 5);
    M5.Lcd.setTextColor(YELLOW);
    M5.Lcd.println("C");
    
   
   
    // Max display
    M5.Lcd.setTextColor(RED);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(10, 35);
    M5.Lcd.println("Max");
    M5.Lcd.setCursor(10, 55);
    M5.Lcd.println(maxTemp);
   
    // Min display
    M5.Lcd.setTextColor(BLUE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(90, 35);
    M5.Lcd.println("Min");
    M5.Lcd.setCursor(90, 55);
    M5.Lcd.println(minTemp);

    Serial.println(tempC);
    SerialBT.print(" Real ");
    SerialBT.print(tempC);
    SerialBT.print(" Max ");
    SerialBT.print(maxTemp);
    SerialBT.print(" Min ");
    SerialBT.println(minTemp);
    
    
  } 
  else
  {
    
    M5.Lcd.setRotation(3);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(30, 5);
    M5.Lcd.setTextColor(YELLOW);
    M5.Lcd.setTextSize(3);
    M5.Lcd.println("Sonda");
  }
   }   
  /* cambio luminosidad Pantalla*/
  
  
  
}
