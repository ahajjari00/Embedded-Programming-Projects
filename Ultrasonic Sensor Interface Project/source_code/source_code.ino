// Amir Hajjari - Ultrasonic Sensor Interface Project
// Created on 5-12-20

#include <LiquidCrystal.h>

LiquidCrystal lcd(7,8,9,10,11,12);


const int buzzer = 5;

const int triggerPin = 4;
const int echoPin1 = 3;
const int echoPin2 = 2;

int sound_brightness = 100; // element to control
// both the brightness of the LED and the sound
// frequency of the buzzer

volatile long pulseTime = 0;
volatile long returnTime = 0;
volatile bool echoReceived = false;

const int timeout = 150000;

const double divider = 2 * 74.0525;
// takes about 74 uSec for sound to travel an inch


void PulsePin(int pinNumber, int numMicroseconds = 50)
{
  digitalWrite(pinNumber, HIGH);
  delayMicroseconds(numMicroseconds);
  digitalWrite(pinNumber, LOW);
}


void setup()
{
  // put your setup code here, to run once:
  pinMode(buzzer, OUTPUT);
  
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  Serial.begin(115200);

  attachInterrupt(digitalPinToInterrupt(echoPin2), PulseSent, RISING);
  attachInterrupt(digitalPinToInterrupt(echoPin1), EchoReceived, FALLING); // NOTICE - NOT echoReceived
  
  lcd.begin(16,2);
}


void loop()
{
  // put your main code here, to run repeatedly:


  PulsePin(triggerPin, 50);
  delayMicroseconds(1000);


  while(!echoReceived)
  {
    if (micros() > pulseTime + timeout)
    {
      echoReceived = true;
      returnTime = micros();
    }
  }

  
  if((returnTime - pulseTime) < timeout)
  {
    double output = (returnTime - pulseTime) / divider;
    lcd.setCursor(0,0);
    lcd.print((String)output);
    lcd.setCursor(0,1);
    lcd.print("inches  away");
    tone(buzzer, output * 1000);
    Serial.println(output);
  }

  delay(1000);
}




// interrupts

void PulseSent(void)
{
  pulseTime = micros();
  echoReceived = false;
}

void EchoReceived(void)
{
  returnTime = micros();
  echoReceived = true;
}
