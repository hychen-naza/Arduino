int LED_pins[6] = {3, 4, 5, 6, 7, 8};
int LED_index = 0;
int LED_direction = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int i = 0; i < 6; i++){
    pinMode(LED_pins[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int delay_value = analogRead(A0);
  digitalWrite(LED_pins[LED_index], HIGH);
  delay(delay_value * 2);
  digitalWrite(LED_pins[LED_index], LOW);
  if (LED_index == 0 && LED_direction == -1){
    LED_direction = 1;
  }
  if (LED_index == 5 && LED_direction == 1){
    LED_direction = -1;
  }
  LED_index += LED_direction;
  Serial.println(LED_index);
}
