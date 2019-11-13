import processing.serial.*;

Serial myPort;
void setup(){
  
  size(200,200);
  String portName = Serial.list()[7];
  myPort = new Serial(this, portName, 9600);
  print(Serial.list());
}
  void draw() {
    if (mousePressed == true)
    {
      myPort.write('1');
      println("1");
    } else
    {
      myPort.write('0');
    }}
