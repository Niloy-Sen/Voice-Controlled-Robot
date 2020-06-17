
const byte MOTOR_A = 3;  // Motor 2 Interrupt Pin - INT 1 - Right Motor
const byte MOTOR_B = 2;  // Motor 1 Interrupt Pin - INT 0 - Left Motor

const float slotnumber = 20.00;  // stores the number of slots in the encoder wheel

const float wheeldiameter = 60.00; // Stores the wheel diameter in millimeter

volatile int counterA = 0;
volatile int counterB = 0;    //Pulse Counter for the 2 motors

// Initialising Motor A

int enableA = 10;
int in1 = 9;
int in2 = 8;

// Initialising Motor B

int enableB = 5;
int in3 = 7;
int in4 = 6;

// Motor A pulse count ISR
void ISR_A()  
{
  counterA++;  // increment Motor A counter value
} 

// Motor B pulse count ISR
void ISR_B()  
{
  counterB++;  // increment Motor B counter value
}

// This function converts a cm value received as a parameter to no. of steps
int Convert(float centi) {

  int result;  
  float circumference = (wheeldiameter * 3.14) / 10; // Calculates wheel circumference in cm
  float cm_step = circumference / slotnumber;  // cm per Step
  
  float f_result = centi / cm_step;  // Calculate result as a float
  result = (int) f_result; // Convert to an integer (note this is NOT rounded)
  
  return result;  // Returns the corresponding steps value

}

// Function for the Robot to Move Forward
void Forward(int steps, int s) 
{
   counterA = 0;  // counterA value is reset to 0
   counterB = 0;  // counterB value is reset to 0

   
   // Setting Motor A forward direction
   digitalWrite(in1, HIGH);
   digitalWrite(in2, LOW);

   // Setting Motor B forward direction
   digitalWrite(in3, HIGH);
   digitalWrite(in4, LOW);
   
   // Go forward until step value is reached
   while (steps > counterA && steps > counterB) {
   
    if (steps > counterA) {
    analogWrite(enableA, s);
    } else {
    analogWrite(enableA, 0);
    }
    if (steps > counterB) {
    analogWrite(enableB, s);
    } else {
    analogWrite(enableB, 0);
    }
   }
    
  // When the step value is reached,the robot will stop
  analogWrite(enableA, 0);
  analogWrite(enableB, 0);
  counterA = 0;  // counterA value is reset to 0
  counterB = 0;  // counterB value is reset to 0


}

// Function to Move in Reverse
void Reverse(int steps, int s) 
{
   counterA = 0;  // counterA value is reset to 0
   counterB = 0;  // counterB value is reset to 0

   // Set Motor A reverse direction
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  // Set Motor B reverse direction
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
   
   // Go in reverse until step value is reached
   while (steps > counterA && steps > counterB) {
   
    if (steps > counterA) {
    analogWrite(enableA, s);
    } else {
    analogWrite(enableA, 0);
    }
    if (steps > counterB) {
    analogWrite(enableB, s);
    } else {
    analogWrite(enableB, 0);
    }
    }
    
  // When the step value is reached,the robot will stop
  analogWrite(enableA, 0);
  analogWrite(enableB, 0);
  counterA = 0;  // counterA value is reset to 0
  counterB = 0;  // counterB value is reset to 0


}

// Function to Turn Right
void Right(int steps, int s) 
{
   counterA = 0;  // counterA value is reset to 0
   counterB = 0;  // counterB value is reset to 0

   // Set Motor A reverse
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  // Set Motor B forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
   
   // The robot will move only until the step value is reahed
   while (steps > counterA && steps > counterB) {
   
    if (steps > counterA) {
    analogWrite(enableA, s);  
    } else {
    analogWrite(enableA, 0);
    }
    if (steps > counterB) {
    analogWrite(enableB, s);
    } else {
    analogWrite(enableB, 0);
    }
   }
    
  // When the step value is reached,the robot will stop
  analogWrite(enableA, 0);
  analogWrite(enableB, 0);
  counterA = 0; // counterA value is reset to 0
  counterB = 0;  // counterB value is reset to 0


}

// Function to Turn Left
void Left(int steps, int s) 
{
   counterA = 0;  // counterA value is reset to 0
   counterB = 0;  // counterB value is reset to 0

   
   // Set Motor A forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  // Set Motor B reverse
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
   
   // Go until step value is reached
   while (steps > counterA && steps > counterB) {
   
    if (steps > counterA) {
    analogWrite(enableA, s);
    } else {
    analogWrite(enableA, 0);
    }
    if (steps > counterB) {
    analogWrite(enableB, s);
    } else {
    analogWrite(enableB, 0);
    }
  }
    
  // When the step value is reached,the robot will stop
  analogWrite(enableA, 0);
  analogWrite(enableB, 0);
  counterA = 0;  // counterA value is reset to 0
  counterB = 0;  // counterB value is reset to 0

}

void setup() 
{
  // The Interrupts are attached to their ISR's
  attachInterrupt(digitalPinToInterrupt (MOTOR_A), ISR_A, RISING);  // Increase counter A when speed sensor pin goes High
  attachInterrupt(digitalPinToInterrupt (MOTOR_B), ISR_B, RISING);  // Increase counter B when speed sensor pin goes High
  Serial.begin(9600);
} 
int velocity=200;
String input;
void loop()
{
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
    Forward(Convert(amount),velocity);
    Serial.println("Robot is moving Forward");
    delay(1000);
  }
  else if(way=="backward")
  {
    Reverse(Convert(amount),velocity);
    Serial.println("Robot is moving Backward");
    delay(1000);
  }
  else if(way=="right")
  {
    Right(Convert(amount),velocity);
    Serial.println("Robot is turning Right");
    delay(1000);
  }
  else if(way=="left")
  {
    Left(Convert(amount),velocity);
    Serial.println("Robot is turning left");
    delay(1000);
  }
  else
  {
    Serial.println("No Instruction Given");
  }

}
