#include <LiquidCrystal_I2C.h>  

LiquidCrystal_I2C lcd(0x27,16,2);

int buttonPin = 4; 
int buzzerPin = 2;
int pirPin = 9;

int intruderNum = 0;
int calibrationTime = 5;

unsigned long lastAlarmCanceledTime = 0;
unsigned long quietTime = 15000;

void setup() {
  Serial.begin (9600);
  
  lcd.init();                
  lcd.backlight(); 
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(pirPin, INPUT);

  delay(calibrationTime * 1000); // warm up pir sensor
}

void loop() {  
  lcd.setCursor(0, 0);
  
  int button_state = digitalRead(buttonPin);
  if (button_state == HIGH){
    intruderNum += 1;
    noTone(buzzerPin);
    lastAlarmCanceledTime = millis();
    Serial.print("lastAlarmCanceledTime ");
    Serial.println(lastAlarmCanceledTime);
  }

  int hasIntruder = digitalRead(pirPin);
  Serial.println(lastAlarmCanceledTime);
  Serial.println(millis());
  Serial.println(hasIntruder);
  if (hasIntruder == HIGH && (millis() - lastAlarmCanceledTime  > quietTime)){
    Serial.println("here");
    tone(buzzerPin, 1000);       
  }
 
  lcd.print("Intruder Num:");
  lcd.print(intruderNum);
  delay(500);
}
