#include <Servo.h>
// constants won't change. They're used here to set pin numbers:
const int BUTTON_PIN = 7; // the number of the pushbutton pin
Servo myservo;  
// Variables will change:
int lastState = HIGH; // the previous state from the input pin
int currentState;    // the current reading from the input pin
int pos = 90;  
const int buzzer = 3;
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(90);
  pinMode(buzzer, OUTPUT);
  // initialize the pushbutton pin as an pull-up input
  // the pull-up input pin will be HIGH when the switch is open and LOW when the switch is closed.
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // read the state of the switch/button:
  currentState = digitalRead(BUTTON_PIN);

  if(lastState == LOW && currentState == HIGH)
    {Serial.println("The state changed from LOW to HIGH");
     for (pos = 90; pos <= 180; pos += 1) // change here in the place 0 and 180 , into any two degrees you wish the servo to sweep.
     { 
     myservo.write(pos); 
     digitalWrite(buzzer, HIGH);
     Serial.println(pos);          
     delay(100); 
     digitalWrite(buzzer, LOW);                      
     }
     delay(3000);
     for (pos = 180; pos >= 90; pos -= 1)  // change here also  in the place 0 and 180 , into any two degrees you wish the servo to sweep.
    { 
     myservo.write(pos);
     Serial.println(pos);
     digitalWrite(buzzer, HIGH);            
     delay(100);                    
     digitalWrite(buzzer, LOW);  
     }
     }
    delay(100);    
  // save the last state
  lastState = currentState;
  //myservo.write(0);  
}