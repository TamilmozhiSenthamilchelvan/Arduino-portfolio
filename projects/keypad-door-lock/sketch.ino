#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal.h>


const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {A0, A1, A2, A3}; // Row pin numbers
byte colPins[COLS] = {8, 7, 6, 5};     // Column pin numbers
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


Servo servo;             
const int servoPin = 9;  
const int buzzerPin = 10; 


LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 


const String correctPasscode = "1234"; 
String enteredPasscode = "";

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(buzzerPin, OUTPUT); 
  digitalWrite(buzzerPin, LOW); 

  lcd.begin(16, 2);       
  lcd.print("Enter Passcode:");
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    if (key == '#') {
      if (enteredPasscode == correctPasscode) {
        unlockDoor();
      } else {
        lcd.clear();
        lcd.print("Incorrect Passcode!");
        tone(10,1000);
        delay(2000);
        noTone(10); 
        lcd.clear();
        lcd.print("Enter Passcode:");
      }
      enteredPasscode = ""; 
    } else {
      enteredPasscode += key;
      lcd.setCursor(0, 1);
      lcd.print("                "); 
      lcd.setCursor(0, 1);
      lcd.print(enteredPasscode);
    }
  }
}

void unlockDoor() {
  lcd.clear();
  lcd.print("Door Unlocked");
  servo.write(90);  
  delay(3000);      
  servo.write(0);   
  delay(1000);
  lcd.clear();
  lcd.print("Enter Passcode:");
}
