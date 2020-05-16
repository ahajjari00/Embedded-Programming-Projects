// Amir Hajjari

#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,6,7,9);
//RS, E, D3-D7

const int green_led = 46;
const int red_led = 44;

#define RST_PIN   5     // Configurable, see typical pin layout above
#define SS_PIN    53   // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

#define NEW_UID {0xDE, 0xAD, 0xBE, 0xEF}
MFRC522::MIFARE_Key key;

void setup() {

  lcd.begin(16,2);
  
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  
  Serial.begin(9600);  // Initialize serial communications with the PC
  SPI.begin();         // Init SPI bus
  mfrc522.PCD_Init();  // Init MFRC522 card 

  while (!Serial);

  for (byte i = 0; i < 6; i++)
  {
    key.keyByte[i] = 0xFF;
  }
  
}

void loop() {


  // Look for new cards, and select one if present
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() )
  {
    delay(50);
    return;
  }

  String UID="";

  Serial.print(F("Card UID:"));
  
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    UID += String(mfrc522.uid.uidByte[i], HEX);
  } 
 
  Serial.println();


  lcd.setCursor(0,0);
  lcd.print("ACCESS");
  lcd.setCursor(0,1);
  
  if (UID == "41ec8cbb")
  {
    Serial.println("Access Granted");
    lcd.print("GRANTED");
    digitalWrite(green_led, HIGH);
    
    delay(4000);
    lcd.clear();
    digitalWrite(green_led, LOW);
  }
  
  else if (UID == "89c6db2a")
  {
    Serial.println("Access Denied");
    lcd.print("DENIED");
    digitalWrite(red_led, HIGH);
    
    delay(4000);
    lcd.clear();
    digitalWrite(red_led, LOW);
  }
  
}
