#include <LiquidCrystal_I2C.h>  
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; // I2C
LiquidCrystal_I2C lcd(0x27,16,2);

float pressure;    //To store the barometric pressure (Pa)
const int historyLen = 180;  // To store pressure value for past 1.5 hours 
float historyPressure[historyLen];
int index = 0;
int predict = 0;  // To show if we have enough data to predict

void setup() {
  Serial.begin(9600); //Begin serial communication at 9600bps
  bmp.begin();    //Begin the sensor
  lcd.init();                
  lcd.backlight(); 
  Serial.println("Adafruit BMP280 test:");
}

void loop() {
  lcd.setCursor(0, 0);
  //Read values from the sensor:
  pressure = bmp.readPressure();
  historyPressure[index] = pressure;


  if (predict == 1){
    lcd.print("Predict:");
    float oldestPressure = historyPressure[(index + 1) % historyLen];
    if (pressure - oldestPressure < -250){
      lcd.print("Rain     ");
    }
    else if (pressure - oldestPressure > 250){
      lcd.print("Sun      ");
    }
    else{
      lcd.print("Sun/Cloud");
    }
  }

  index += 1;
  if (index == historyLen){
    predict = 1;
  }
  index %= historyLen;
  
  lcd.setCursor(0, 2);
  lcd.print("Pressure:");
  lcd.print(pressure);
  lcd.print("pa");
  delay(1000 * 30); //Update every 1 min
}
