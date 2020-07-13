#include "DHT.h"
#include "Wire.h"
#include <LiquidCrystal_I2C.h>          //If you have a generic I2C breakout


#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27,16,2);   //If you have a generic I2C breakout

const int lightSensor = A0;
int brightness;
int button = 4; //the button pin to change from C to F temp
int oldButtonState = LOW;

void setup() {
  dht.begin();
  lcd.init();                //If you have a generic I2C breakout
  lcd.backlight();           //If you have a generic I2C breakout
  pinMode(lightSensor, INPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
}

void loop() {
  lcd.setCursor(0, 0);
  // Wait a few seconds between measurements.
  brightness = 1023 - analogRead(lightSensor);
  delay(1000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    lcd.print("Sensor failure");
    Serial.println("Sensor failure");
    return;
  }
  lcd.print("T:");
  
  int newButtonState = digitalRead(button); //is the button pressed?

  //Print the temperature in C or F according to the button
  if (newButtonState == LOW && oldButtonState == LOW ){
    lcd.print(t);
    lcd.setCursor(6, 0);
    lcd.print("C");
  } 
  else if (newButtonState == HIGH && oldButtonState == LOW ){
    lcd.print(f);
    lcd.setCursor(6, 0);
    lcd.print("F");
    oldButtonState = HIGH;
   }
   else if(newButtonState == LOW && oldButtonState == HIGH ) {
    lcd.print(f);
    lcd.setCursor(6, 0);
    lcd.print("F");
   }
   else if(newButtonState == HIGH && oldButtonState == HIGH){
    lcd.print(t);
    lcd.setCursor(6, 0);
    lcd.print("C");
    oldButtonState = LOW;
   }

  //Print Humidity level 
  lcd.print(" H:");
  lcd.print(h);
  lcd.print("%");

  //Print Brightness level
  lcd.setCursor(0, 1); 
  lcd.print("Light:");
  
  if(brightness <= 333){
    lcd.print("Dark  ");
    }
   else if(brightness <= 666){
    lcd.print("Normal");
    }
   else if(brightness <= 1023){
    lcd.print("Bright");
    }  
}
