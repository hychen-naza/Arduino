#include <LiquidCrystal_I2C.h>  

#define trigPin 13
#define echoPin 12
#define redPin   6
#define greenPin 7
#define bluePin  8

LiquidCrystal_I2C lcd(0x27,16,2);

int buttonPin = 4; 
int buzzerPin = 2;
int unit = 0; // 0 means cm, 1 means inch
float unitTransform = 2.54;

void dangerAlarm(){
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
  digitalWrite(redPin, HIGH);
  tone(buzzerPin, 3000, 1000);
}

void attentionAlarm(){
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, HIGH);
  tone(buzzerPin, 1000, 100);
}

void safeAlarm(){
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
  digitalWrite(redPin, LOW);
  noTone(buzzerPin);
}

void setup() {
  lcd.init();                
  lcd.backlight(); 
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
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
      if (distance < 10){
        dangerAlarm();       
      }
      else if (distance < 20){
        attentionAlarm();        
      }
      else{
        safeAlarm();
      }
    }
    else if (unit == 1){
      distance /= unitTransform;
      lcd.print(distance);
      lcd.print("inch      ");
      if (distance < (10 / unitTransform)){
        dangerAlarm();       
      }
      else if (distance < (20 / unitTransform)){
        attentionAlarm();
      }
      else{
        safeAlarm();
      }
    }
  }
  delay(500);
}
