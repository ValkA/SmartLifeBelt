#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial bluetooth(2, 3); // RX, TX
Servo airServo;
Servo dropServo;
int led_pin = 13;
int buzzer_pin = 9;

int dropTime = 300;//ms
int airPumpTime = 3500;//ms

//blue servo
int dropServoHold = 60;//degrees
int dropServoDrop = 0;//degrees

//black servo
int airServoClosed = 20;//degrees
int airServoOpen = 60;//degrees

void setup() {
  pinMode(buzzer_pin, OUTPUT);
  pinMode(led_pin, OUTPUT);   
  airServo.attach(3);
  dropServo.attach(5);
  airServo.write(airServoClosed);
  dropServo.write(dropServoHold);
  bluetooth.begin(9600);
  bluetooth.setTimeout(100);
}

void loop() {
  
  if(bluetooth.available()>0){
    char c = bluetooth.read();
    if(c == 'a'){// air only - TRIANGLE
      airServo.write(airServoOpen);
      delay(airPumpTime);
      airServo.write(airServoClosed);
    }
    if(c == 'd'){// drop poly - CIRCLE
      dropServo.write(dropServoDrop);
      delay(dropTime);
//      dropServo.write(dropServoHold);
    }
    if(c == 'r'){// drop then air - X
      dropServo.write(dropServoDrop);
      delay(dropTime);
      airServo.write(airServoOpen);
      delay(airPumpTime);
      airServo.write(airServoClosed);
      delay(50);
//      dropServo.write(dropServoHold);
//      delay(50);

      while(true){
        tone(buzzer_pin, 2400);
        delay(250);
        tone(buzzer_pin, 4800);
        delay(250);
      }
    }
    if(c == 's'){
      airServoOpen = airServoClosed + bluetooth.parseInt();
    }
    if(c == 'z'){
      dropServoDrop = dropServoDrop + bluetooth.parseInt();
    }
  }
}
