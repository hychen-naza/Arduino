const int LED_pin = 8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int delay_value = analogRead(A0);
  digitalWrite(LED_pin, HIGH);
  delay(delay_value * 2);
  digitalWrite(LED_pin, LOW);
  delay(delay_value * 2);
}
