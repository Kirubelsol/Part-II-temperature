#include "M5Atom.h"
#include "math.h" //library for basic arthimetics
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#define Data_pin 27 //specific for ATOM matrix


bool IMU6886Flag = false;
float gyroX, gyroY , gyroZ, temp; // declare
int c = 0;
int count = 0;
bool check;
float sumtemp;
uint8_t DisBuff[2 + 5 * 5 * 3];

// function to change the color
void setBuff(uint8_t Rdata, uint8_t Gdata, uint8_t Bdata) // function to change the color
{
  DisBuff[0] = 0x05;
  DisBuff[1] = 0x05;
  for (int i = 0; i < 25; i++)
  {
    DisBuff[2 + i * 3 + 0] = Rdata;
    DisBuff[2 + i * 3 + 1] = Gdata;
    DisBuff[2 + i * 3 + 2] = Bdata;
  }
}

void setup()
{
  M5.begin(true, false, true);
  delay(10);
  //  setBuff(0xff, 0x00, 0x00);
  //  M5.dis.displaybuff(DisBuff);
  if (M5.IMU.Init() != 0)
  {
    IMU6886Flag = false;
  }
  else
  {
    IMU6886Flag = true;
  }
  M5.IMU.getTempData(&sumtemp); //setting the sumtemp to the initial temp
}
uint8_t color = 0; // the state of the color

void loop()
{

    //storing temperature in specific time interval to be diaplayed in Mode 1
    if (currentTime - previoustime1 >= time_interval_1) {
      previoustime1 = currentTime;
      currentTemp = temp;

      // Values of temperature in different units to be used in Mode 5
      currentTempF = ((9 / 5) * (currentTemp)) + 32;
      currentTempK = currentTemp + 273;
      Serial.printf("%.2f, %.2f,%.2f  \r\n", currentTemp, currentTempF, currentTempK);
    }

    // storing average temperature in a day to be displayed in Mode 2
    if (currentTime - previoustime2 >= time_interval_1) {
      previoustime2 = currentTime;
      sumtemp = (sumtemp + temp) / 2; //calculating avg temp using every temp vale in each time interval
      Serial.printf("%.2f, %.2f \r\n", temp, sumtemp);

      // resetting the value of sumtemp in every day (86400000 millisecond)
      if (currentTime - prevtime_day >= 86400000 ) {
        prevtime_day = currentTime;
        sumtemp = temp;
        Serial.printf("%.2f, %.2f \r\n", temp, sumtemp);
      }
    }
}
