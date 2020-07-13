int button_pin = 2;
int random_value;
int LED_pins[9] = {3, 4, 5, 6, 7, 8, 9, 10, 11};

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < 9; i++){
    pinMode(LED_pins[i], OUTPUT);
  }
  pinMode(button_pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int button_state = digitalRead(button_pin);
  if (button_state == HIGH){
    random_value = random(1, 7);
    for(int i = 0; i < 9; i++){
      digitalWrite(LED_pins[i], LOW);
    }
  }
  
  Serial.println(random_value);
  switch (random_value){
    case 1:
      digitalWrite(LED_pins[4], HIGH);
      break;
    case 2:
      digitalWrite(LED_pins[0], HIGH);
      digitalWrite(LED_pins[8], HIGH);
      break;
    case 3:
      digitalWrite(LED_pins[0], HIGH);
      digitalWrite(LED_pins[4], HIGH);
      digitalWrite(LED_pins[8], HIGH);
      break;
    case 4:
      digitalWrite(LED_pins[0], HIGH);
      digitalWrite(LED_pins[2], HIGH);
      digitalWrite(LED_pins[6], HIGH);
      digitalWrite(LED_pins[8], HIGH);
      break;
    case 5:
      digitalWrite(LED_pins[0], HIGH);
      digitalWrite(LED_pins[2], HIGH);
      digitalWrite(LED_pins[4], HIGH);
      digitalWrite(LED_pins[6], HIGH);
      digitalWrite(LED_pins[8], HIGH);
      break;
    case 6:
      digitalWrite(LED_pins[0], HIGH);
      digitalWrite(LED_pins[2], HIGH);
      digitalWrite(LED_pins[3], HIGH);
      digitalWrite(LED_pins[5], HIGH);
      digitalWrite(LED_pins[6], HIGH);
      digitalWrite(LED_pins[8], HIGH);
      break;
  }
  
}
