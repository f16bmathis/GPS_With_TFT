/* Original using GPS_MEGA, so can't use "Kitchen_Sink" Libraries different.
 *  Arduino MEGA
 * Good on Pin19
 * To read on serial monitor @ 115200 baud
 * Blacks screen, writes Position and Lat and value at top
 */

// TFT SETUP START *********************************************************************************************************************
#include <Arduino.h>
#define USE_ADAFRUIT_SHIELD_PINOUT 1
#include <Adafruit_GFX.h>                                      //added Adafruit GFX with BIO Whatever also
#include <MCUFRIEND_kbv.h>                                     //added mcufriend.kbv
MCUFRIEND_kbv tft;

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

float B;
int delta = 50;                  // 50 was middle of screen, 0 is top of screen, 100 at bottom of screen
int clockCenterX=120;            // 120 is center, 60 shifts left, 230 shifts right
int clockCenterY=110+delta;      // 110 is center, 0 is up, 220 is down   (not all the way to the center in both up & down)

#include <Wire.h>
#include <Adafruit_Sensor.h>                                                        
// TFT SETUP END **********************************************************************************************************************
 
#include <TinyGPS.h>
//long   lat,lon; // create variable for latitude and longitude object
float lat,lon;
TinyGPS gps; // create gps object

void setup(){
  
Serial.begin(115200); // connect serial
Serial.println("The GPS Received Signal:");
Serial1.begin(9600); // connect gps sensor

//}

// TFT VOID SETUP BEGIN *****************************************************************************************************
//Serial.begin(9600);

  uint16_t identifier = tft.readID();

    tft.begin(identifier);
    tft.fillScreen(BLACK);                                     // Unsure, seemed to have no effect
    tft.setRotation(0);                                        // Flips Rotation 180 from 0 to 2

    return;
    
  }
  void drawDisplay(float B)

{

  drawDisplay(B);

  delay (1000);

   }
      
// TFT VOID SETUP END *****************************************************************************************************

void loop(){
    while(Serial1.available()){ // check for gps data
    if(gps.encode(Serial1.read()))// encode gps data
    { 
    gps.f_get_position(&lat,&lon); // get latitude and longitude

    tft.setTextColor(GREEN,BLACK);  tft.setTextSize(3);
    tft.setCursor(5, 10);tft.println("Position: ");
 
    //Latitude
    tft.print("LAT    ");
    tft.println(lat,3);             //Limited to 3 digits past decimal point
    
    Serial.print(",");
    
    //Longitude
    tft.print("LONG  ");
    tft.println(lon,3); 

    gps.f_speed_mph();             // SPEED!!!!!
    tft.println("SPEED    ");
    tft.print(gps.speed.mph,0);


    
 delay(2000);                      // Otherwise it erases right away "flashes"
 tft.fillScreen(BLACK);

   }
  }
 } 
