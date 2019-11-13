
char val;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
//  Serial.print(Serial.available());
  
  if (Serial.available())
  {
    val = Serial.read();
    Serial.println(val);

  }
  if (val == '1')
  {
    digitalWrite(10,HIGH);
    digitalWrite(11, HIGH);
  }
  if (val =='0')
  {  
     digitalWrite(11, LOW);
     digitalWrite(10,LOW);
  }
}


