/* Room thermometer with LED matrix
 * Code by Marius Giedraitis
 * Student of Kaunas University of Applied Sciences, "Kauno Kolegija"
 * Arduino UNO wifi XMAS contest entry
     LED matrix pinout    DHT11 sensor pinout
     DIN - 12                    VCC  - 3.3V
     CLK - 11                    DATA - A0
     CS  - 10                    GND  - GND
     VCC - 5V                  
     GND - GND        

               NOTE: zero indexing will be used in arrays and LED control library. 
               LED's one to eight will be numbered as 0 to 7 in code.
*/


#include <dht.h>
#include <LedControl.h>
LedControl lc=LedControl(12,11,10,1); // 

unsigned long delaytime=1000;

#define dht_dpin A0
dht DHT;

void setup() {
 // Serial.begin(9600);
 // Serial.println(" \n");

  
  lc.shutdown(0,false); // LED controller default state is off/power saving
  lc.setIntensity(0,1); // brightness from 1 to 9
  lc.clearDisplay(0); // clears display
  animation();
}



byte hum;

void loop() {
  
 /*     delay(5000);
  DHT.read11(dht_dpin);
  Serial.print(DHT.humidity);    //this block is for viewing sensor output on serial 
  Serial.print("%  ");
  Serial.print(DHT.temperature);
  Serial.println("C  ");
  */
 tempToBytes();
  
   // number of LED's corresponding to humidity value  1led= >12.5%  2>25% 3>37.5%  4>50%  5>62.5%  6>75% 7>87.5%  
   
if (DHT.humidity>87){
hum=B11111111;
}
else if (DHT.humidity>75){
  hum=B11111110;
}
else if (DHT.humidity>62){
  hum=B11111100;
}
else if (DHT.humidity>50){
  hum=B11111000;
}
else if (DHT.humidity>37){
  hum=B11110000;
}
else if (DHT.humidity>25){
  hum=B11100000;
}
else {
  hum=B10000000;
}

 lc.setRow(0,7,hum); // the corresponding humidity reading is displayed on the 8th(bottom) line of the matrix
}

//TEMPERATURES

void tempToBytes() { 
  int char1=DHT.temperature/10;         // separating first digit
  int char2=DHT.temperature-char1*10;   // separating second digit
  
  // here we hold number codes in byte format. each row of array corresponds to the number
  // to draw each number we use 3 column rows, so we use 3 columns in each row of array
  byte bitai[10][3]={
{B01110000, B10001000, B01110000}, //0
{B00000000, B01000000, B11111000}, //1
{B01001000, B10011000, B01101000}, //2
{B10101000, B10101000, B01010000}, //3
{B11100000, B00100000, B11111000}, //4
{B11101000, B10101000, B10010000}, //5
{B01111000, B10101000, B10010000}, //6
{B10000000, B10111000, B11000000}, //7
{B11111000, B10101000, B11111000}, //8
{B11101000, B10101000, B11111000}}; //9

  /*    for (int col=0;col<5;col++)
    {
     lc.setRow(0,col,B00000000);  // to clear number space
    }
    */
    
    for (int kek=0;kek<3;kek++)
    {
lc.setColumn(0,kek,bitai[char1][kek]);  // lc.setColumn(0,column_number,byte_row ) the cycle prints 0 1 2 columns of the digit.
    }
    
    for (int lel=0;lel<3;lel++)
    {
      lc.setColumn(0,lel+4,bitai[char2][lel]);  // cycle for 2nd digit, starting from the 4th column (zero indexed)
    }
    
    
}

// Stylyzed animation logo with letter K

void animation(){
lc.setRow(0,7,B10000000);
delay(100);
lc.setRow(0,6,B10000000);
lc.setRow(0,7,B01000000);
delay(100);
lc.setRow(0,5,B10000000);
lc.setRow(0,6,B01000000);
lc.setRow(0,7,B00100000);
delay(100);
lc.setRow(0,4,B10000000);
lc.setRow(0,5,B01000000);
lc.setRow(0,6,B00100000);
lc.setRow(0,7,B00010000);
delay(100);
lc.setRow(0,3,B10000000);
lc.setRow(0,4,B01000000);
lc.setRow(0,5,B00100000);
lc.setRow(0,6,B00010000);
lc.setRow(0,7,B00001000);
delay(100);
lc.setRow(0,2,B10000000);
lc.setRow(0,3,B01000000);
lc.setRow(0,4,B00100000);
lc.setRow(0,5,B00010000);
lc.setRow(0,6,B00001000);
lc.setRow(0,7,B00000100);
delay(100);
lc.setRow(0,1,B10000000);
lc.setRow(0,2,B01000000);
lc.setRow(0,3,B00100000);
lc.setRow(0,4,B00010000);
lc.setRow(0,5,B00001000);
lc.setRow(0,6,B00000100);
lc.setRow(0,7,B00000010);
delay(100);
lc.setRow(0,0,B10000000);
lc.setRow(0,1,B01000000);
lc.setRow(0,2,B00100000);
lc.setRow(0,3,B00010000);
lc.setRow(0,4,B00001000);
lc.setRow(0,5,B00000100);
lc.setRow(0,6,B00000010);
lc.setRow(0,7,B00000001);
delay(100);
lc.setRow(0,0,B01000000);
lc.setRow(0,1,B00100000);
lc.setRow(0,2,B00010000);
lc.setRow(0,3,B00001000);
lc.setRow(0,4,B00000100);
lc.setRow(0,5,B00000010);
lc.setRow(0,6,B00000001);
lc.setRow(0,7,B00000000);
delay(100);
lc.setRow(0,0,B00100000);
lc.setRow(0,1,B00010000);
lc.setRow(0,2,B00001000);
lc.setRow(0,3,B00000100);
lc.setRow(0,4,B00000010);
lc.setRow(0,5,B00000001);
lc.setRow(0,6,B00000000);
delay(100);
lc.setRow(0,0,B00010000);
lc.setRow(0,1,B00001000);
lc.setRow(0,2,B00000100);
lc.setRow(0,3,B00000010);
lc.setRow(0,4,B00000001);
lc.setRow(0,5,B00000000);
delay(100);
lc.setRow(0,0,B00001000);
lc.setRow(0,1,B00000100);
lc.setRow(0,2,B00000010);
lc.setRow(0,3,B00000001);
lc.setRow(0,4,B00000000);
delay(100);
lc.setRow(0,0,B00000100);
lc.setRow(0,1,B00000010);
lc.setRow(0,2,B00000001);
lc.setRow(0,3,B00000000);
delay(100);
lc.setRow(0,0,B00000010);
lc.setRow(0,1,B00000001);
lc.setRow(0,2,B00000000);
delay(100);
lc.setRow(0,0,B00000001);
lc.setRow(0,1,B00000000);
delay(100);

lc.setRow(0,0,B00100000);
lc.setRow(0,1,B00100010);
lc.setRow(0,2,B00100100);
lc.setRow(0,3,B00001000);
lc.setRow(0,4,B00001000);
lc.setRow(0,5,B00000100);
lc.setRow(0,6,B00000010);
lc.setRow(0,7,B00000000);
delay(3000);
lc.setRow(0,0,B00000000);
lc.setRow(0,1,B00000000);
lc.setRow(0,2,B00000000);
lc.setRow(0,3,B00000000);
lc.setRow(0,4,B00000000);
lc.setRow(0,5,B00000000);
lc.setRow(0,6,B00000000);
lc.setRow(0,7,B00000000);
}







