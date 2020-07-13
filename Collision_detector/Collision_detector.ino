// This project doesn't make sense to me, so I didn't do it

int X_axis = A2;
int Y_axis = A1;
int Z_axis = A0;

int x, y, z;                          // These variables will hold the raw sensor values.                                      
void setup()
{
  Serial.begin(9600);      // sets the serial port to 9600

  delay(1000);
}

void loop()
{
  x = analogRead(X_axis);  
  y = analogRead(Y_axis);       // read analog input pin 1
  z = analogRead(Z_axis);       // read analog input pin 1
  
  Serial.print(x);              // print the raw value in the X axis
  Serial.print("\t");           // prints a tab between the numbers
  Serial.print(y);              // print the raw value in the Y axis
  Serial.print("\t");           // prints a tab between the numbers
  Serial.print(z);              // print the raw value in the Z axis
  Serial.println();
  
  delay(100);              // wait 100ms for next reading
}
