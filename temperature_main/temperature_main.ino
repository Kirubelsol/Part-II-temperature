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
  long currentTime = millis();
 

  if (IMU6886Flag == true)
  {

    M5.IMU.getTempData(&temp); //get the temperature

    if (currentTime - previoustime ==  timeinterval1) {
      temp1 = temp;
      Serial.printf("%.2f Temp1", temp1);

    }
    if (currentTime - previoustime == timeinterval2) {
      temp2 = temp;
      Serial.printf("%.2f Temp2", temp2);
    }
    if (currentTime - previoustime == timeinterval3) {
      temp3 = temp;
      Serial.printf("%.2f Temp3", temp3);
    }
    if (currentTime - previoustime == timeinterval4) {
      temp4 = temp;
      Serial.printf("%.2f Temp4", temp4);
    }
    if (currentTime - previoustime == timeinterval5) {
      temp5 = temp;
      Serial.printf("%.2f Temp5", temp5);
    }
    // for the first column pixels
    if (temp1 < 25 && temp1 > 1) {
      M5.dis.drawpix(20, 0xff0000);
      Serial.printf("Y");
    }
    if (temp1 >= 25 && temp1 < 30) {

      M5.dis.drawpix(15, 0xff0000);
      M5.dis.drawpix(20, 0xff0000);
    }
    if (temp1 >= 30 && temp1 < 35) {
      M5.dis.drawpix(10, 0xff0000);
      M5.dis.drawpix(15, 0xff0000);
      M5.dis.drawpix(20, 0xff0000);
    }
    if (temp1 >= 35 && temp1 < 40) {
      M5.dis.drawpix(5, 0xff0000);
      M5.dis.drawpix(10, 0xff0000);
      M5.dis.drawpix(15, 0xff0000);
      M5.dis.drawpix(20, 0xff0000);
    }
    if (temp1 >= 40) {
      M5.dis.drawpix(0, 0xff0000);
      M5.dis.drawpix(5, 0xff0000);
      M5.dis.drawpix(10, 0xff0000);
      M5.dis.drawpix(15, 0xff0000);
      M5.dis.drawpix(20, 0xff0000);
    }
    ////////

    // for the second column pixels
    if (temp2 < 25 && temp2 > 1) {
      M5.dis.drawpix(21, 0xff0000);
    }
    if (temp2 >= 25 && temp2 < 30) {
      M5.dis.drawpix(16, 0xff0000);
      M5.dis.drawpix(21, 0xff0000);
    }
    if (temp2 >= 30 && temp2 < 35) {
      M5.dis.drawpix(11, 0xff0000);
      M5.dis.drawpix(16, 0xff0000);
      M5.dis.drawpix(21, 0xff0000);
    }
    if (temp2 >= 35 && temp2 < 40) {
      M5.dis.drawpix(6, 0xff0000);
      M5.dis.drawpix(11, 0xff0000);
      M5.dis.drawpix(16, 0xff0000);
      M5.dis.drawpix(21, 0xff0000);
    }
    if (temp2 >= 40) {
      M5.dis.drawpix(1, 0xff0000);
      M5.dis.drawpix(6, 0xff0000);
      M5.dis.drawpix(11, 0xff0000);
      M5.dis.drawpix(16, 0xff0000);
      M5.dis.drawpix(21, 0xff0000);
    }
    ////////

    // for the third column pixels
    if (temp3 < 25 && temp3 > 1) {
      M5.dis.drawpix(22, 0xff0000);
    }
    if (temp3 >= 25 && temp3 < 30) {
      M5.dis.drawpix(17, 0xff0000);
      M5.dis.drawpix(22, 0xff0000);
    }
    if (temp3 >= 30 && temp3 < 35) {
      M5.dis.drawpix(12, 0xff0000);
      M5.dis.drawpix(15, 0xff0000);
      M5.dis.drawpix(22, 0xff0000);
    }
    if (temp3 >= 35 && temp3 < 40) {
      M5.dis.drawpix(7, 0xff0000);
      M5.dis.drawpix(12, 0xff0000);
      M5.dis.drawpix(17, 0xff0000);
      M5.dis.drawpix(22, 0xff0000);
    }
    if (temp3 >= 40) {
      M5.dis.drawpix(2, 0xff0000);
      M5.dis.drawpix(7, 0xff0000);
      M5.dis.drawpix(12, 0xff0000);
      M5.dis.drawpix(17, 0xff0000);
      M5.dis.drawpix(22, 0xff0000);
    }
    ////////

    // for the forth column pixels
    if (temp4 < 25 && temp4 > 1) {
      M5.dis.drawpix(23, 0xff0000);
    }
    if (temp4 >= 25 && temp4 < 30) {
      M5.dis.drawpix(18, 0xff0000);
      M5.dis.drawpix(23, 0xff0000);
    }
    if (temp4 >= 30 && temp4 < 35) {
      M5.dis.drawpix(13, 0xff0000);
      M5.dis.drawpix(18, 0xff0000);
      M5.dis.drawpix(23, 0xff0000);
    }
    if (temp4 >= 35 && temp4 < 40) {
      M5.dis.drawpix(8, 0xff0000);
      M5.dis.drawpix(13, 0xff0000);
      M5.dis.drawpix(18, 0xff0000);
      M5.dis.drawpix(23, 0xff0000);
    }
    if (temp4 >= 40) {
      M5.dis.drawpix(3, 0xff0000);
      M5.dis.drawpix(8, 0xff0000);
      M5.dis.drawpix(13, 0xff0000);
      M5.dis.drawpix(18, 0xff0000);
      M5.dis.drawpix(23, 0xff0000);
    }
    ////////


    // for the fifth column pixels
    if (temp5 < 25 && temp5 > 1) {
      M5.dis.drawpix(24, 0xff0000);
    }
    if (temp5 >= 25 && temp4 < 30) {
      M5.dis.drawpix(19, 0xff0000);
      M5.dis.drawpix(23, 0xff0000);
    }
    if (temp5 >= 30 && temp4 < 35) {
      M5.dis.drawpix(14, 0xff0000);
      M5.dis.drawpix(19, 0xff0000);
      M5.dis.drawpix(24, 0xff0000);
    }
    if (temp5 >= 35 && temp4 < 40) {
      M5.dis.drawpix(9, 0xff0000);
      M5.dis.drawpix(14, 0xff0000);
      M5.dis.drawpix(19, 0xff0000);
      M5.dis.drawpix(24, 0xff0000);
    }
    if (temp5 >= 40) {
      M5.dis.drawpix(4, 0xff0000);
      M5.dis.drawpix(9, 0xff0000);
      M5.dis.drawpix(14, 0xff0000);
      M5.dis.drawpix(19, 0xff0000);
      M5.dis.drawpix(24, 0xff0000);
    }
    ////////

    if (currentTime - previoustime == 30000) {
      previoustime = currentTime;
      temp1 = 0;
      temp2 = 0;
      temp3 = 0;
      temp4 = 0;
      temp5 = 0;
      setBuff(0x00, 0x00, 0x00);
      M5.dis.displaybuff(DisBuff);
      M5.update();

    };


  }
  else
  {
    // Fail to initialize IMU (Maybe)
    M5.dis.clear();
    M5.dis.drawpix(2, 2, CRGB::Red);
    delay(500);
    M5.update();
  }
}
