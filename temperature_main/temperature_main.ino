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
 if (currentTime - previoustime >= time_interval) {
      previoustime = currentTime;


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

            M5.dis.clear();
            M5.dis.drawpix(1, 0xf00000);
            M5.dis.drawpix(2, 0xf00000);
            M5.dis.drawpix(3, 0xf00000);
            M5.dis.drawpix(8, 0xf00000);
            M5.dis.drawpix(11, 0xf00000);
            M5.dis.drawpix(12, 0xf00000);
            M5.dis.drawpix(13, 0xf00000);
            M5.dis.drawpix(18, 0xf00000);
            M5.dis.drawpix(21, 0xf00000);
            M5.dis.drawpix(22, 0xf00000);
            M5.dis.drawpix(23, 0xf00000); 
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
