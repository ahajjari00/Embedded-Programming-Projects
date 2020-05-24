// Amir Hajjari - Temperature Sensor w/ Joystick Project

#include "dht11.h"
#define DHT11PIN 4
dht11 DHT11;

#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,11,5,6,7);

#include <Joystick.h>

const int switch_pin = 8;
const int y_pin = 1; // analog input
const int x_pin = 0; // anlog input

#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;


void setup() {
  // put your setup code here, to run once:

  pinMode(switch_pin, INPUT);
  digitalWrite(switch_pin, HIGH);
  
  lcd.begin(16,2);
  
  Serial.begin(9600);
  // while(!Serial);

  //Serial.println("Please type in '1' for degrees F, '2' for C"); // included here so statement only appears 
                                                                // once during each operation


  if(!rtc.begin())
  {
    Serial.println("RTC is not working!");
    while(1); // keep here until RTC is running
  }

  if(!rtc.isrunning())
  {
    Serial.println("RTC is not running!");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  // *******JOYSTICK TEST CODE************
  /*
  Serial.println("JOYSTICK TEST");
  
  Serial.print("X-pos: ");
  Serial.println(analogRead(x_pin));

  Serial.print("Y-pos: ");
  Serial.println(analogRead(y_pin));
  Serial.println();
  Serial.println();

  if(analogRead(x_pin) > 500)
  {
    Serial.println("Hooray!");
  }

  else
  {
    Serial.println("Boooo!");
  }

  delay(2000);
  
  return;

  */
  //**************************************


  // ***************RTC TEST CODE****************
  /* 
  DateTime now = rtc.now(); // sets the current time!

  int data = DHT11.read(DHT11PIN);

  Serial.print(now.hour() - 1); // RTC module was one hour off
  Serial.print(':');
  Serial.print(now.minute() - 7); // RTC module was 7 minutes off
  //Serial.print(':');
  // Serial.print(now.second()); do not need this much accuracy
  Serial.print("   \n");

  Serial.print(now.month());
  Serial.print('/');
  Serial.print(now.day() - 1);
  Serial.print('/');
  Serial.print(now.year());
  Serial.print("   \n");

  Serial.println();
  Serial.println();

  delay(10000);
  
  return;

  */
  // *************************************
  
  int input;

  lcd.setCursor(0,0);

  DateTime now = rtc.now(); // sets the current time!
  int data = DHT11.read(DHT11PIN); // gets the info for the humidity and temp(in celcius)
  
  // case 1: x >= 900 and y >= 451 - temp in F and humidity %
  // case 2: x <= 20 and y <= 510 - temp in C and humidity %
  // case 3: x >= 450 and y <= 20 - date and time info
  // case 4: x>= 450 and y >= 950 - "no info here!"
  // case 5: DEFAULT display "pick direction" -> x >= 450, x <= 550 ... y >= 450, x <= 550

  
  if(analogRead(x_pin) >= 900 and analogRead(y_pin) >= 451) // case 1 pre-check
  {

 Serial.print("X-pos: ");
  Serial.println(analogRead(x_pin));

  Serial.print("Y-pos: ");
  Serial.println(analogRead(y_pin));
  Serial.println();
  Serial.println();
    
    float farenheit = (((float)DHT11.temperature) * 1.8) + 32;
    lcd.print("Temp F: ");
    lcd.print(farenheit, 2); // farenheit algorithm

    lcd.setCursor(0,1);
    lcd.print("Humidity: ");
    lcd.print((float)DHT11.humidity, 2);
    lcd.print("%");
    
  }

  else if(analogRead(x_pin) <= 100 and analogRead(y_pin) <= 700) // case 2 pre-check
  {


Serial.print("X-pos: ");
  Serial.println(analogRead(x_pin));

  Serial.print("Y-pos: ");
  Serial.println(analogRead(y_pin));
  Serial.println();
  Serial.println();

    
    lcd.print("Temp C: ");
    lcd.print((float)DHT11.temperature, 2);

    lcd.setCursor(0,1);
    lcd.print("Humidity: ");
    lcd.print((float)DHT11.humidity, 2);
    lcd.print("%");
    
  }

  else if(analogRead(x_pin) >= 400 and analogRead(y_pin) <= 50) // case 3
  {




Serial.print("X-pos: ");
  Serial.println(analogRead(x_pin));

  Serial.print("Y-pos: ");
  Serial.println(analogRead(y_pin));
  Serial.println();
  Serial.println();

    
    lcd.print("TIME-> ");

    int correctHour = now.hour();
    int correctMinute = now.minute();
    
    if(correctMinute  >= 60)
    {
      correctMinute -= 60;
      correctHour += 1;
    }
    
    correctMinute -= 7; // RTC module was 7 minutes off
    correctHour -= 1; // RTC module was one hour off (likely to daylight savings??)
    
    lcd.print(correctHour);
    lcd.print(':');
    
    if(correctMinute < 10)
    {
      lcd.print(0);
      lcd.print(correctMinute);
    }
    
    else
    {
      lcd.print(correctMinute);
    }

    if(correctHour < 12)
    {
      lcd.print(" PM");
    }
    else
    {
      lcd.print(" AM");
    }

    lcd.setCursor(0,1);
    lcd.print("DATE-> ");
    lcd.print(now.month());
    lcd.print('/');
    lcd.print(now.day() - 1);
    lcd.print('/');
    lcd.print(now.year());
  }

  else if(analogRead(x_pin) >= 450 and analogRead(y_pin) >= 950) // case 4
  {



Serial.print("X-pos: ");
  Serial.println(analogRead(x_pin));

  Serial.print("Y-pos: ");
  Serial.println(analogRead(y_pin));
  Serial.println();
  Serial.println();

    
    lcd.print("Thanks for");
    lcd.setCursor(0,1);
    lcd.print("watching! :)");
  }

  else // case 5
  {


Serial.print("X-pos: ");
  Serial.println(analogRead(x_pin));

  Serial.print("Y-pos: ");
  Serial.println(analogRead(y_pin));
  Serial.println();
  Serial.println();

    
    lcd.print("Pick direction:");
    lcd.setCursor(0,1);
    lcd.print("N, S , E , or W");
  }

  delay(800); // adjustable, up to desginer
            // if you want quicker screen change, bring down the delay value
            // if you want longer time for each screen, increase the delay value
  lcd.clear();
  
}
