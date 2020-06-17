#include<Servo.h>
#include <AFMotor.h>
String input;

AF_DCMotor motor1(1,MOTOR12_1KHZ);
AF_DCMotor motor2(2,MOTOR12_1KHZ);
Servo myServo;

void setup() {
  myServo.attach(10);
  myServo.write(90);
  Serial.begin(9600);

}

void loop() {
  String way="";
  String amount1="";
  int amount;
  while (Serial.available())
  {
    delay(10);
    String c=Serial.readStringUntil('\n');
    input=input+c;
  }
  int l=input.length();
  for(int i=0;i<l;i++)
  {
    char ch=input.charAt(i);
    if(ch==' ')
    {
    amount1=input.substring(0,i);
    amount=amount1.toInt();
    way=input.substring(i+1,l);
    break;
    }
  }
  if(way=="forward")
  {
    forward_car(amount);
  }
  else if(way=="backward")
  {
    backward_car(amount);
  }
  else if(way=="right")
  {
    right_car(amount);
  }
  else if(way=="left")
  {
    left_car(amount);
  }
  else
  {
    stop_car();
    Serial.println("No Instruction Given");
  }

}
  void forward_car(int n)
{
  int velocity=170;
  motor1.run(FORWARD);
  motor1.setSpeed(velocity);
  motor2.run(FORWARD);
  motor2.setSpeed(velocity);
  double time_required= n/velocity;
  delay(time_required);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}
 void backward_car(int n)
 {
   int velocity=170;
  motor1.run(BACKWARD);
  motor1.setSpeed(velocity);
  motor2.run(BACKWARD);
  motor2.setSpeed(velocity);
  double time_required= n/velocity;
  delay(time_required);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
 }
 void right_car(int n)
{
  myServo.write(0);
  delay(1000);
  myServo.write(90);
  delay(1000);
  int velocity=170;
  motor1.run(FORWARD);
  motor1.setSpeed(velocity);
  motor2.run(BACKWARD);
  motor2.setSpeed(velocity);
  double time_required=n/velocity;
  delay(time_required);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}
void left_car(int n)
{
  myServo.write(180);
  delay(1000);
  myServo.write(90);
  delay(1000);
  int velocity=170;
  motor1.run(FORWARD);
  motor1.setSpeed(velocity);
  motor2.run(BACKWARD);
  motor2.setSpeed(velocity);
  double time_required=n/velocity;
  delay(time_required);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}
void stop_car()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}
  
    
  
  
