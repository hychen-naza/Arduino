#include <LiquidCrystal_I2C.h>  

#define trigPin 13
#define echoPin 12

LiquidCrystal_I2C lcd(0x27,16,2);

int buttonPin = 4; 
int unit = 0; // 0 means cm, 1 means inch


void setup() {
  lcd.init();                
  lcd.backlight(); 
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  lcd.setCursor(0, 0);
  long duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;


  int button_state = digitalRead(buttonPin);
  if (button_state == HIGH){
    unit = (unit + 1) % 2;
  }

  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    
    lcd.print("Object Distance:");
    if (unit == 0){
      lcd.print(distance);
      lcd.print("cm      ");
    }
    else if (unit == 1){
      distance /= 2.54;
      lcd.print(distance);
      lcd.print("inch      ");
    }
  }
  delay(500);
}
