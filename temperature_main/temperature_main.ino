#include "M5Atom.h"
#include "math.h" //library for basic arthimetics
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#define Data_pin 27 //specific for ATOM matrix


float currentTemp = 1;
float currentTempF = 0; // in Farhenite
float currentTempK = 0; // in Kelvin
float original_gyro = 0.0;


bool IMU6886Flag = false;
float gyroX, gyroY , gyroZ, temp; // declare for measuring the values
int c = 0;
int count = 0;
// used for transition between modes
bool check;
bool check1; // for transit between mode 3 and 4
bool check2; // for internal mode 4
bool checkmode1 = true; // for mode 1
bool checkm1;
bool checkmode2 = true; // for mode 2
bool checkm2;
bool checkm5;
bool checkmode5 = true; // for mode 5
bool check51 = false;
bool check52 = false;
bool check53 = false;
float sumtemp;
uint8_t DisBuff[2 + 5 * 5 * 3];

//for removing 
long previous1 = 0;
long previous2 = 0;
long previous3 = 0;

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

//time related variables for setting the interval of recording time
long previoustime = 0;
long previoustime1 = 0;
long previoustime2 = 0;
long previoustime4 = 0;
long prevtime_day = 0; // for 24 hour change


int counter = 0; //to decide which mode
const long time_interval = 400;
const long time_interval_1 = 3000; //for Mode 1 to store active temperature

// declarations for Mode 4: Temperature graph

float temp1 = 0;
float temp2 = 0;
float temp3 = 0;
float temp4 = 0;
float temp5 = 0;

float timeinterval1 = 5000; // 5 seconds

float timeinterval2 = 10000;

float timeinterval3 = 15000;

float timeinterval4 = 20000;

float timeinterval5 = 25000;

// declerations for displaying the temperatures for mode 1,2 and 5
int tempC = 0;
int tempF = 0;
int tempK = 0;
int avgtempC = 0;
int temp5C = 0;
int temp5F = 0;
int temp5K = 0;

// pixel values for every numbers to be used in displaying the temperatures
void number1()
{
  M5.dis.drawpix(3, 0xf00000);
  M5.dis.drawpix(7, 0xf00000);
  M5.dis.drawpix(8, 0xf00000);
  M5.dis.drawpix(13, 0xf00000);
  M5.dis.drawpix(18, 0xf00000);
  M5.dis.drawpix(23, 0xf00000);
}

void number2()
{
  M5.dis.drawpix(2, 0xf00000);
  M5.dis.drawpix(3, 0xf00000);
  M5.dis.drawpix(6, 0xf00000);
  M5.dis.drawpix(8, 0xf00000);
  M5.dis.drawpix(12, 0xf00000);
  M5.dis.drawpix(16, 0xf00000);
  M5.dis.drawpix(21, 0xf00000);
  M5.dis.drawpix(22, 0xf00000);
  M5.dis.drawpix(23, 0xf00000);
}

void number3()
{
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
}

void number4()
{
  M5.dis.drawpix(2, 0xf00000);
  M5.dis.drawpix(6, 0xf00000);
  M5.dis.drawpix(10, 0xf00000);
  M5.dis.drawpix(11, 0xf00000);
  M5.dis.drawpix(12, 0xf00000);
  M5.dis.drawpix(13, 0xf00000);
  M5.dis.drawpix(17, 0xf00000);
  M5.dis.drawpix(22, 0xf00000);
}


void number5()
{
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
}

void number6()
{
  M5.dis.drawpix(1, 0xf00000);
  M5.dis.drawpix(2, 0xf00000);
  M5.dis.drawpix(3, 0xf00000);
  M5.dis.drawpix(6, 0xf00000);
  M5.dis.drawpix(11, 0xf00000);
  M5.dis.drawpix(12, 0xf00000);
  M5.dis.drawpix(13, 0xf00000);
  M5.dis.drawpix(16, 0xf00000);
  M5.dis.drawpix(18, 0xf00000);
  M5.dis.drawpix(21, 0xf00000);
  M5.dis.drawpix(22, 0xf00000);
  M5.dis.drawpix(23, 0xf00000);
}

void number7()
{
  M5.dis.drawpix(1, 0xf00000);
  M5.dis.drawpix(2, 0xf00000);
  M5.dis.drawpix(3, 0xf00000);
  M5.dis.drawpix(8, 0xf00000);
  M5.dis.drawpix(12, 0xf00000);
  M5.dis.drawpix(16, 0xf00000);
  M5.dis.drawpix(21, 0xf00000);
}

void number8()
{
  M5.dis.drawpix(1, 0xf00000);
  M5.dis.drawpix(2, 0xf00000);
  M5.dis.drawpix(3, 0xf00000);
  M5.dis.drawpix(6, 0xf00000);
  M5.dis.drawpix(8, 0xf00000);
  M5.dis.drawpix(11, 0xf00000);
  M5.dis.drawpix(12, 0xf00000);
  M5.dis.drawpix(13, 0xf00000);
  M5.dis.drawpix(16, 0xf00000);
  M5.dis.drawpix(18, 0xf00000);
  M5.dis.drawpix(21, 0xf00000);
  M5.dis.drawpix(22, 0xf00000);
  M5.dis.drawpix(23, 0xf00000);
}

void number9()
{
  M5.dis.drawpix(1, 0xf00000);
  M5.dis.drawpix(2, 0xf00000);
  M5.dis.drawpix(3, 0xf00000);
  M5.dis.drawpix(6, 0xf00000);
  M5.dis.drawpix(8, 0xf00000);
  M5.dis.drawpix(11, 0xf00000);
  M5.dis.drawpix(12, 0xf00000);
  M5.dis.drawpix(13, 0xf00000);
  M5.dis.drawpix(18, 0xf00000);
  M5.dis.drawpix(23, 0xf00000);
}

void number0()
{
  M5.dis.drawpix(1, 0xf00000);
  M5.dis.drawpix(2, 0xf00000);
  M5.dis.drawpix(3, 0xf00000);
  M5.dis.drawpix(6, 0xf00000);
  M5.dis.drawpix(8, 0xf00000);
  M5.dis.drawpix(11, 0xf00000);
  M5.dis.drawpix(13, 0xf00000);
  M5.dis.drawpix(16, 0xf00000);
  M5.dis.drawpix(18, 0xf00000);
  M5.dis.drawpix(21, 0xf00000);
  M5.dis.drawpix(22, 0xf00000);
  M5.dis.drawpix(23, 0xf00000);

}

// the characters C, F, and K for the units
void charaC()
{
  M5.dis.drawpix(1, 0xf00000);
  M5.dis.drawpix(2, 0xf00000);
  M5.dis.drawpix(3, 0xf00000);
  M5.dis.drawpix(6, 0xf00000);
  M5.dis.drawpix(11, 0xf00000);
  M5.dis.drawpix(16, 0xf00000);
  M5.dis.drawpix(21, 0xf00000);
  M5.dis.drawpix(22, 0xf00000);
  M5.dis.drawpix(23, 0xf00000);
}

void charaF()
{
  M5.dis.drawpix(1, 0xf00000);
  M5.dis.drawpix(2, 0xf00000);
  M5.dis.drawpix(3, 0xf00000);
  M5.dis.drawpix(6, 0xf00000);
  M5.dis.drawpix(11, 0xf00000);
  M5.dis.drawpix(12, 0xf00000);
  M5.dis.drawpix(13, 0xf00000);
  M5.dis.drawpix(16, 0xf00000);
  M5.dis.drawpix(21, 0xf00000);
}

void charaK()
{
  M5.dis.drawpix(1, 0xf00000);
  M5.dis.drawpix(4, 0xf00000);
  M5.dis.drawpix(3, 0xf00000);
  M5.dis.drawpix(6, 0xf00000);
  M5.dis.drawpix(8, 0xf00000);
  M5.dis.drawpix(11, 0xf00000);
  M5.dis.drawpix(12, 0xf00000);
  M5.dis.drawpix(16, 0xf00000);
  M5.dis.drawpix(18, 0xf00000);
  M5.dis.drawpix(21, 0xf00000);
  M5.dis.drawpix(24, 0xf00000);
}

// function to display the numbers when called
void shownumbers(int numbe)
{
  if (numbe == 1)
    number1();
  else if (numbe == 2)
    number2();
  else if (numbe == 3)
    number3();
  else if (numbe == 4)
    number4();
  else if (numbe == 5)
    number5();
  else if (numbe == 6)
    number6();
  else if (numbe == 7)
    number7();
  else if (numbe == 8)
    number8();
  else if (numbe == 9)
    number9();
  else if (numbe == 0)
    number0();

}

void loop()
{
  long currentTime = millis();  // measure the current time
  // declare variables to store the temperature in different units

  if (IMU6886Flag == true)
  {
    M5.IMU.getTempData(&temp); //get the temperature
    M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ); //get the orientation


    //storing temperature in specific time interval to be diaplayed in Mode 1
    if (currentTime - previoustime1 >= time_interval_1) {
      previoustime1 = currentTime;
      currentTemp = temp;
      Serial.println(currentTemp);

      // Values of temperature in different units to be used in Mode 5
      currentTempF = ((9 / 5) * (currentTemp)) + 32;
      currentTempK = currentTemp + 273;
      //    Serial.printf("%.2f, %.2f,%.2f  \r\n", currentTemp, currentTempF, currentTempK);
    }

    // storing average temperature in a day to be displayed in Mode 2
    if (currentTime - previoustime2 >= time_interval_1) {
      previoustime2 = currentTime;
      sumtemp = (sumtemp + temp) / 2; //calculating avg temp using every temp vale in each time interval
      //   Serial.printf("%.2f, %.2f \r\n", temp, sumtemp);

      // resetting the value of sumtemp in every day (86400000 millisecond)
      if (currentTime - prevtime_day >= 86400000 ) {
        prevtime_day = currentTime;
        sumtemp = temp;
        //     Serial.printf("%.2f, %.2f \r\n", temp, sumtemp);
      }
    }

    //solving for tilting

    //if clause to measure orientation change is specified interval
    if (currentTime - previoustime >= time_interval) {
      previoustime = currentTime;

      //specified orientation change to change modes
      if ((gyroY ) > 60 && (gyroY) < 300) {
        counter++;

      }

      //switch for the five modes
      switch (counter)
      {

        // case for active temperature
        case 1:
          checkmode5 = true; // related to the end of code to enable mode 5
          if (checkmode1 == true) {
            //display 1 to show first mode
            M5.dis.clear();
            M5.dis.drawpix(3, 0xf00000);
            M5.dis.drawpix(7, 0xf00000);
            M5.dis.drawpix(8, 0xf00000);
            M5.dis.drawpix(13, 0xf00000);
            M5.dis.drawpix(18, 0xf00000);
            M5.dis.drawpix(23, 0xf00000);
          }

          // if button is pressed start the task
          if (M5.Btn.wasPressed())
          {
            checkmode1 = false;
            checkm1 = true;
          }
          Serial.printf("%.2f", currentTemp);
          if (checkm1 == true) {
            long current1 = millis();
            tempC = currentTemp; // store the current temperature


            //loop to display individual numbers of the temperature

            if (current1 - previous1 <= 1500) {

              int individualnum = ( tempC / 10) % 10;
              shownumbers(individualnum);
              Serial.printf("%d", individualnum);
            }

            if ((current1 - previous1 > 1505) && (current1 - previous1 <= 1800)) {
              setBuff(0x00, 0x00, 0x00);
              M5.dis.displaybuff(DisBuff);
            }
            M5.update ();
            if ((current1 - previous1 > 1810) && (current1 - previous1 <= 3400)) {
              int individualnum = ( tempC) % 10;
              shownumbers(individualnum);
              Serial.printf("%d", individualnum);
            }


            if ((current1 - previous1 > 3400) && (current1 - previous1 <= 3700)) {
              setBuff(0x00, 0x00, 0x00);
              M5.dis.displaybuff(DisBuff);
              Serial.printf("true");

            }
            M5.update ();
            if ((current1 - previous1 > 3700) && (current1 - previous1 <= 5800)) {

              charaC(); // display C for celcius

            }

            if (current1 - previous1 > 5500) {
              previous1 = current1;
              M5.dis.clear ();
              M5.update ();
            }

          }
          M5.update();
          break;

        // case for average temperature
        case 2:
          checkmode1 = true;
          checkm1 = false;
          // display 2 to show second mode
          if (checkmode2 == true) {
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
          }
          // if button is pressed start the task
          if (M5.Btn.wasPressed())
          {
            checkmode2 = false;
            checkm2 = true; // to start the task
          }

          if (checkm2 == true) {
            avgtempC = sumtemp; // store the avg temperature
            long current2 = millis();

            //loop to display individual numbers of the average temperature

            if (current2 - previous2 <= 1500) {

              int individualnum = ( avgtempC / 10) % 10;
              shownumbers(individualnum);
              Serial.printf("%d", individualnum);
            }

            if ((current2 - previous2 > 1505) && (current2 - previous2 <= 1800)) {
              setBuff(0x00, 0x00, 0x00);
              M5.dis.displaybuff(DisBuff);
            }
            M5.update ();
            if ((current2 - previous2 > 1810) && (current2 - previous2 <= 3400)) {
              int individualnum = ( avgtempC) % 10;
              shownumbers(individualnum);
              Serial.printf("%d", individualnum);
            }


            if ((current2 - previous2 > 3400) && (current2 - previous2 <= 3700)) {
              setBuff(0x00, 0x00, 0x00);
              M5.dis.displaybuff(DisBuff);
              Serial.printf("true");

            }
            M5.update ();
            if ((current2 - previous2 > 3700) && (current2 - previous2 <= 5800)) {

              charaC(); // display C for celcius

            }

            if (current2 - previous2 > 5500) {
              previous2 = current2;
              M5.dis.clear ();
              M5.update ();
            }

          }

          check = true; // used to enable the 3 case, related with the case 3 code

          M5.update();
          break;

       
        case 3:
          checkmode2 = true;
          checkm2 = false;
          // if it comes from the second case
          if (check) {
            //display 3 to show case 3
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
          }


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
            { // settign lights to green
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
            { //setting lights to white
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
            { // setting lights to yellow
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
            { // setting lights to red
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

          check1 = true;
          M5.update();
          break;

        // case to show temperature graph
        case 4:

          // display number 4 to show forth mode
          // check if it comes from case 3
          if (check1) {
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
          }
          if (M5.Btn.wasPressed()) {
            check2 = true;
          }

          if  (check2 == true) {

            if (M5.Btn.wasPressed()) {
              previoustime4 = currentTime; // set previoustime4 to be used in getting the temperatures in interval
              check1 = false;
            }




            M5.dis.clear();

            // store temp in five variables at specific intervals (with the five variables altering each column height pixel of
            //M5 atom)
            if ((currentTime - previoustime4 >  timeinterval1) && (currentTime - previoustime4 <  timeinterval1 + 500) ) {
              temp1 = temp;

            }
            if  ((currentTime - previoustime4 >  timeinterval2) && (currentTime - previoustime4 <  timeinterval2 + 500) ) {
              temp2 = temp;

            }
            if ((currentTime - previoustime4 >  timeinterval3) && (currentTime - previoustime4 <  timeinterval3 + 500) ) {
              temp3 = temp;
            }
            if  ((currentTime - previoustime4 >  timeinterval4) && (currentTime - previoustime4 <  timeinterval4 + 500) ) {
              temp4 = temp;

            }
            if  ((currentTime - previoustime4 >  timeinterval5) && (currentTime - previoustime4 <  timeinterval5 + 500) ) {
              temp5 = temp;

            }

            // for the first column pixels
            if (temp1 < 25 && temp1 > 1) {
              M5.dis.drawpix(20, 0xff0000);   // display only for the bottom pixel of first column
            }
            if (temp1 >= 25 && temp1 < 30) {

              M5.dis.drawpix(15, 0xff0000);  // display for two pixels of first column from bottom
              M5.dis.drawpix(20, 0xff0000);
            }
            if (temp1 >= 30 && temp1 < 35) {
              M5.dis.drawpix(10, 0xff0000);
              M5.dis.drawpix(15, 0xff0000);   // display for three pixels of first column from bottom
              M5.dis.drawpix(20, 0xff0000);
            }
            if (temp1 >= 35 && temp1 < 40) {
              M5.dis.drawpix(5, 0xff0000);
              M5.dis.drawpix(10, 0xff0000);     // display for four pixels of first column from bottom
              M5.dis.drawpix(15, 0xff0000);
              M5.dis.drawpix(20, 0xff0000);
            }
            if (temp1 >= 40) {
              M5.dis.drawpix(0, 0xff0000);    // display for all five pixels of first column
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

            // after certain time (all five column temp shown)
            if ((currentTime - previoustime4 > 32500) && (currentTime - previoustime4 < 34000)) {
              previoustime4 = currentTime; // reset previousTime4
              temp1 = 0;    //reinitialize all temp values to 0
              temp2 = 0;
              temp3 = 0;
              temp4 = 0;
              temp5 = 0;
              setBuff(0x00, 0x00, 0x00);    // make all pixels black to start displaying graph again
              M5.dis.displaybuff(DisBuff);
              M5.update();

            };
          }

          M5.update();
          break;

        //case to show change units

        case 5:

          check2 = false;
          // display number 5 to indicate fifth mode
          if (checkmode5 == true) {
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
          }
          if (M5.Btn.wasPressed())
          {
            checkmode5 = false;
            checkm5 = true;
          }

          if (checkm5 == true) {
            // record the temperature in all units
            temp5C = currentTemp;
            temp5F = currentTempF;
            temp5K = currentTempK;
            long current3 = millis();


            //loop to display individual numbers of the temperature in celcius

            if (current3 - previous3 <= 1500) {

              int individualnum = ( temp5C / 10) % 10;
              shownumbers(individualnum);
              Serial.printf("%d", individualnum);
            }

            if ((current3 - previous3 > 1505) && (current3 - previous3 <= 1800)) {
              setBuff(0x00, 0x00, 0x00);
              M5.dis.displaybuff(DisBuff);
            }
            M5.update ();
            if ((current3 - previous3 > 1810) && (current3 - previous3 <= 3400)) {
              int individualnum = ( temp5C) % 10;
              shownumbers(individualnum);

            }


            if ((current3 - previous3 > 3400) && (current3 - previous3 <= 3700)) {
              setBuff(0x00, 0x00, 0x00);
              M5.dis.displaybuff(DisBuff);

            }
            M5.update ();
            if ((current3 - previous3 > 3700) && (current3 - previous3 <= 5800)) {

              charaC(); // display C for celcius

            }

            if ((current3 - previous3 > 5800) && (current3 - previous3 <= 6100)) {

              setBuff(0x00, 0x00, 0x00);
              M5.dis.displaybuff(DisBuff);

            }

            // Farhenite display
            if ((current3 - previous3 > 6110) && (current3 - previous3 <= 7710)) {
              int individualnum = ( temp5F / 10) % 10;
              shownumbers(individualnum);
            }
            if ((current3 - previous3 > 7110) && (current3 - previous3 <= 7400)) {
              setBuff(0x00, 0x00, 0x00);
              M5.dis.displaybuff(DisBuff);
            }
            if ((current3 - previous3 > 7400) && (current3 - previous3 <= 9200)) {
              int individualnum = ( temp5F) % 10;
              shownumbers(individualnum);
            }
            if ((current3 - previous3 > 9200) && (current3 - previous3 <= 9500)) {
              setBuff(0x00, 0x00, 0x00);
              M5.dis.displaybuff(DisBuff);
            }
            if ((current3 - previous3 > 9500) && (current3 - previous3 <= 11300)) {
              charaF(); // show letter F for farhenite
            }
            if ((current3 - previous3 > 11300) && (current3 - previous3 <= 11700)) {
              setBuff(0x00, 0x00, 0x00);
              M5.dis.displaybuff(DisBuff);
            }

            // Kelvin display
            if ((current3 - previous3 > 11700) && (current3 - previous3 <= 13400)) {
              int individualnum = ( temp5K / 100) % 10;
              shownumbers(individualnum);
            }
            if ((current3 - previous3 > 13400) && (current3 - previous3 <= 13700)) {
              setBuff(0x00, 0x00, 0x00);
              M5.dis.displaybuff(DisBuff);
            }
            if ((current3 - previous3 > 13700) && (current3 - previous3 <= 15500)) {
              int individualnum = ( temp5K / 10) % 10;
              shownumbers(individualnum);
            }
            if ((current3 - previous3 > 15500) && (current3 - previous3 <= 15800)) {
              setBuff(0x00, 0x00, 0x00);
              M5.dis.displaybuff(DisBuff);
            }
            if ((current3 - previous3 > 15800) && (current3 - previous3 <= 17600)) {
              int individualnum = ( temp5K) % 10;
              shownumbers(individualnum);
            }
            if ((current3 - previous3 > 17600) && (current3 - previous3 <= 17900)) {
              setBuff(0x00, 0x00, 0x00);
              M5.dis.displaybuff(DisBuff);
            }
            if ((current3 - previous3 > 17900) && (current3 - previous3 <= 19700)) {
              charaK(); // show letter K for kelvin
            }

            if (current3 - previous3 > 19700) {
              previous3 = current3;
              M5.dis.clear ();
              M5.update ();
            }
          }

          M5.update();
          break;
      }

      // if the tilt is above a certain range
      //in case of face down turn screen off
      if ((gyroY) > 300) {
        setBuff(0x00, 0x00, 0x00);
        M5.dis.displaybuff(DisBuff); //add M5.update later

        // reset case numbers
        counter = 0;

        M5.update();
      }
      //another if statement to reset count when all modes are reached
      if (counter == 6) {
        counter = 1;
      }

    }

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
