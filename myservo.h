#include <Servo.h>

#define POS_UP 90
#define POS_DOWN 0

Servo servo1;

void myservo_init(const int servoPin){
  servo1.attach(servoPin);
}

void myservo_open(){
  servo1.write(POS_UP);
  delay(100);
}

void myservo_close(){
  servo1.write(POS_DOWN);
  delay(100);
}
