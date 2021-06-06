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
uint8_t color = 0; // the state of the color.

void loop()
{


  
  if (currentTime - previoustime >= time_interval) {
      previoustime = currentTime;



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
      
      if ((gyroY ) > 60 && (gyroY) < 300) {
        counter++;

      }


      switch (counter)
      {

        case 1:

          M5.dis.clear();
          M5.dis.drawpix(3, 0xf00000);
          M5.dis.drawpix(7, 0xf00000);
          M5.dis.drawpix(8, 0xf00000);
          M5.dis.drawpix(13, 0xf00000);
          M5.dis.drawpix(18, 0xf00000);
          M5.dis.drawpix(23, 0xf00000);

          break;
        case 2:

         
          M5.dis.clear();
          M5.dis.drawpix(2, 0xf00000);
          M5.dis.drawpix(3, 0xf00000);
          M5.dis.drawpix(6, 0xf00000);
          M5.dis.drawpix(8, 0xf00000);
          M5.dis.drawpix(12, 0xf00000);
          M5.dis.drawpix(16, 0xf00000);
          M5.dis.drawpix(21, 0xf00000);
          M5.dis.drawpix(22, 0xf00000);
          M5.dis.drawpix(23, 0xf00000);

          break;

        case 3:

if (M5.Btn.wasPressed())
          {
            // make check false so it will only display the colors
            //with temperature range (the task) with out displaying
            //number 3 till tilted

            check = false;
            M5.dis.clear();
            M5.IMU.getTempData(&temp);


            if (temp <= 10)
            { //setting lights to blue
              M5.dis.drawpix(0, 0xf000ff);
              M5.dis.drawpix(1, 0xf00800);
              M5.dis.drawpix(2, 0xffffff);
              M5.dis.drawpix(3, 0xffff00);
              M5.dis.drawpix(4, 0x00f000);
              M5.dis.drawpix(5, 0xf000ff);
              M5.dis.drawpix(6, 0xf00800);
              M5.dis.drawpix(7, 0xffffff);
              M5.dis.drawpix(8, 0xffff00);
              M5.dis.drawpix(9, 0x00f000);
              M5.dis.drawpix(10, 0xf000ff);
              M5.dis.drawpix(11, 0xf00800);
              M5.dis.drawpix(12, 0xffffff);
              M5.dis.drawpix(13, 0xffff00);
              M5.dis.drawpix(14, 0x00f000);
              M5.dis.drawpix(14, 0xf000ff);
              M5.dis.drawpix(15, 0xf000ff);
              M5.dis.drawpix(16, 0xf000ff);
              M5.dis.drawpix(17, 0xf000ff);
              M5.dis.drawpix(18, 0xf000ff);
              M5.dis.drawpix(19, 0xf000ff);
              M5.dis.drawpix(20, 0xf000ff);
              M5.dis.drawpix(21, 0xf000ff);
              M5.dis.drawpix(22, 0xf000ff);
              M5.dis.drawpix(23, 0xf000ff);
              M5.dis.drawpix(24, 0xf000ff);


            }


            if (temp >= 10 && temp < 20)
            { // settign lights to green\ M5.dis.drawpix(0, 0xf000ff);
              M5.dis.drawpix(1, 0xf00800);
              M5.dis.drawpix(2, 0xffffff);
              M5.dis.drawpix(3, 0xffff00);
              M5.dis.drawpix(4, 0x00f000);
              M5.dis.drawpix(5, 0xf000ff);
              M5.dis.drawpix(6, 0xf00800);
              M5.dis.drawpix(7, 0xffffff);
              M5.dis.drawpix(8, 0xffff00);
              M5.dis.drawpix(9, 0x00f000);
              M5.dis.drawpix(10, 0xf000ff);
              M5.dis.drawpix(11, 0xf00800);
              M5.dis.drawpix(12, 0xffffff);
              M5.dis.drawpix(13, 0xffff00);
              M5.dis.drawpix(14, 0x00f000);
              M5.dis.drawpix(14, 0xf00800);
              M5.dis.drawpix(15, 0xf00800);
              M5.dis.drawpix(16, 0xf00800);
              M5.dis.drawpix(17, 0xf00800);
              M5.dis.drawpix(18, 0xf00800);
              M5.dis.drawpix(19, 0xf00800);
              M5.dis.drawpix(20, 0xf00800);
              M5.dis.drawpix(21, 0xf00800);
              M5.dis.drawpix(22, 0xf00800);
              M5.dis.drawpix(23, 0xf00800);
              M5.dis.drawpix(24, 0xf00800);

            }

            if (temp >= 20 && temp < 30)
            { //setting lights to white\ M5.dis.drawpix(0, 0xf000ff);
              M5.dis.drawpix(1, 0xf00800);
              M5.dis.drawpix(2, 0xffffff);
              M5.dis.drawpix(3, 0xffff00);
              M5.dis.drawpix(4, 0x00f000);
              M5.dis.drawpix(5, 0xf000ff);
              M5.dis.drawpix(6, 0xf00800);
              M5.dis.drawpix(7, 0xffffff);
              M5.dis.drawpix(8, 0xffff00);
              M5.dis.drawpix(9, 0x00f000);
              M5.dis.drawpix(10, 0xf000ff);
              M5.dis.drawpix(11, 0xf00800);
              M5.dis.drawpix(12, 0xffffff);
              M5.dis.drawpix(13, 0xffff00);
              M5.dis.drawpix(14, 0x00f000);
              M5.dis.drawpix(14, 0xffffff);
              M5.dis.drawpix(15, 0xffffff);
              M5.dis.drawpix(16, 0xffffff);
              M5.dis.drawpix(17, 0xffffff);
              M5.dis.drawpix(18, 0xffffff);
              M5.dis.drawpix(19, 0xffffff);
              M5.dis.drawpix(20, 0xffffff);
              M5.dis.drawpix(21, 0xffffff);
              M5.dis.drawpix(22, 0xffffff);
              M5.dis.drawpix(23, 0xffffff);
              M5.dis.drawpix(24, 0xffffff);

            }
            if (temp >= 30  && temp < 40)
            {
              M5.dis.drawpix(0, 0xf000ff);
              M5.dis.drawpix(1, 0xf00800);
              M5.dis.drawpix(2, 0xffffff);
              M5.dis.drawpix(3, 0xffff00);
              M5.dis.drawpix(4, 0x00f000);
              M5.dis.drawpix(5, 0xf000ff);
              M5.dis.drawpix(6, 0xf00800);
              M5.dis.drawpix(7, 0xffffff);
              M5.dis.drawpix(8, 0xffff00);
              M5.dis.drawpix(9, 0x00f000);
              M5.dis.drawpix(10, 0xf000ff);
              M5.dis.drawpix(11, 0xf00800);
              M5.dis.drawpix(12, 0xffffff);
              M5.dis.drawpix(13, 0xffff00);
              M5.dis.drawpix(14, 0x00f000);
              M5.dis.drawpix(14, 0xffff00);
              M5.dis.drawpix(15, 0xffff00);
              M5.dis.drawpix(16, 0xffff00);
              M5.dis.drawpix(17, 0xffff00);
              M5.dis.drawpix(18, 0xffff00);
              M5.dis.drawpix(19, 0xffff00);
              M5.dis.drawpix(20, 0xfffff00);
              M5.dis.drawpix(21, 0xffff00);
              M5.dis.drawpix(22, 0xffff00);
              M5.dis.drawpix(23, 0xffff00);
              M5.dis.drawpix(24, 0xffff00);

            }

            if (temp >= 40)
            {
              M5.dis.drawpix(0, 0xf000ff);
              M5.dis.drawpix(1, 0xf00800);
              M5.dis.drawpix(2, 0xffffff);
              M5.dis.drawpix(3, 0xffff00);
              M5.dis.drawpix(4, 0x00f000);
              M5.dis.drawpix(5, 0xf000ff);
              M5.dis.drawpix(6, 0xf00800);
              M5.dis.drawpix(7, 0xffffff);
              M5.dis.drawpix(8, 0xffff00);
              M5.dis.drawpix(9, 0x00f000);
              M5.dis.drawpix(10, 0xf000ff);
              M5.dis.drawpix(11, 0xf00800);
              M5.dis.drawpix(12, 0xffffff);
              M5.dis.drawpix(13, 0xffff00);
              M5.dis.drawpix(14, 0x00f000);
              M5.dis.drawpix(14, 0x00f000);
              M5.dis.drawpix(15, 0x00f000);
              M5.dis.drawpix(16, 0x00f000);
              M5.dis.drawpix(17, 0x00f000);
              M5.dis.drawpix(18, 0x00f000);
              M5.dis.drawpix(19, 0x00f000);
              M5.dis.drawpix(20, 0x00f000);
              M5.dis.drawpix(21, 0x00f000);
              M5.dis.drawpix(22, 0x00f000);
              M5.dis.drawpix(23, 0x00f000);
              M5.dis.drawpix(24, 0x00f000);

            }


          }
}  
          break;

        case 4:

          M5.dis.clear();
          M5.dis.drawpix(2, 0xf00000);
          M5.dis.drawpix(6, 0xf00000);
          M5.dis.drawpix(10, 0xf00000);
          M5.dis.drawpix(11, 0xf00000);
          M5.dis.drawpix(12, 0xf00000);
          M5.dis.drawpix(13, 0xf00000);
          // M5.dis.drawpix(16, 0xf00000);
          M5.dis.drawpix(17, 0xf00000);
          M5.dis.drawpix(22, 0xf00000);
          break;

        case 5:

          M5.dis.clear();
          M5.dis.drawpix(1, 0xf00000);
          M5.dis.drawpix(2, 0xf00000);
          M5.dis.drawpix(3, 0xf00000);
          M5.dis.drawpix(6, 0xf00000);
          M5.dis.drawpix(11, 0xf00000);
          M5.dis.drawpix(12, 0xf00000);
          M5.dis.drawpix(13, 0xf00000);
          M5.dis.drawpix(18, 0xf00000);
          M5.dis.drawpix(21, 0xf00000);
          M5.dis.drawpix(22, 0xf00000);
          M5.dis.drawpix(23, 0xf00000);
          M5.update();

          break;
      }


      if ((gyroY) > 300) {
        setBuff(0x00, 0x00, 0x00);
        M5.dis.displaybuff(DisBuff); //add M5.update later
        counter = 0;

        M5.update();
      }
     
      if (counter == 6) {
        counter = 1;
      }

    }

  }
    }
}

