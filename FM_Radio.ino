/*
 * Simple Program to set a Frequency and read Statistics 
 * 
 * Licence: GNU GPL
 * 
 * by big12boy 2017
 */

#include <TEA5767.h>
#include <LiquidCrystal.h>
 
// Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
TEA5767 radio = TEA5767();

float frequency = 88.0; //Enter your own Frequency
long baud = 250000; //Enter your own Baudrate

long lmillis = 0;

void setup() {
  //Setup Serial and I2C
  Serial.begin(baud);
  Wire.begin();
  lcd.begin(16, 2);
  pinMode(A0,INPUT_PULLUP); //+
  pinMode(A1,INPUT_PULLUP); //-
    // Clears the LCD screen
  lcd.clear();
  
  //Set Frequency to start with
  radio.setFrequency(frequency);
  LCD();
}
void LCD()
{
  lcd.clear();
  lcd.setCursor(0,0);
    // Print a message to the LCD.
  lcd.print("FM Radio");
  lcd.setCursor(0,1);
  lcd.print("F: ");
  lcd.setCursor(2,1);
  lcd.print(frequency,2);
  lcd.setCursor(8,1);
  lcd.print("MHz");
  delay(100);
  radio.setFrequency(frequency);
}
void loop() {
  //Check for User Input
  if(digitalRead(A0) == LOW)
  {
    delay(60);
    frequency += 0.1;
    if(frequency > 108.0)
    {
      frequency = 108.0;
    }
    LCD();
    while(digitalRead(A0) == LOW);
  }
  if(digitalRead(A1) == LOW)
  {
    delay(60);
    frequency -= 0.1;
    if(frequency < 88.0)
    {
      frequency = 88.0;
    }
    LCD();
    while(digitalRead(A1) == LOW);
  }
  
  
  
  //Check for time (active every second
    
    //Serial.println();
  }


void printFrequency(){
  float frequency = radio.getFrequency(); //Get Frequency
  //Serial.print("Frequency: ");
  //Serial.println(frequency, 2);
}

void printReady(){
  int rdy = radio.getReady(); //Get State
  //Serial.print("Ready: ");
  //Serial.println(rdy);
}

void printStereo(){
  bool stereo = radio.isStereo(); //Get Stereo
  //Serial.print("Stereo: ");
  //Serial.println(stereo);
}

void printSignalLevel(){
  short level = radio.getSignalLevel(); //Get Signal Level
  //Serial.print("Signal (0-15): ");
  //Serial.println(level);
}
