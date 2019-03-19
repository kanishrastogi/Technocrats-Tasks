#include<Servo.h>
int LM_1 = 2;    // Left motor direction control pins 
int LM_2 = 4;
int LMS = 3;     // speed control pin for left motor
int RM_1 = 7;    // Right motor direction control pins 
int RM_2 = 6;
int RMS = 5;     // speed control pin for right motor
int IR = 8;     // pin to which IR sensor is connected
Servo myservo;
char data;
void setup() {
  pinMode(IR,INPUT);  
  myservo.attach(9);  //assign servo motor to pin 8
  Serial.begin(9600);
  }
void right(int S, int TS){ 
  Stop();
  digitalWrite(LM_1,HIGH);
  digitalWrite(LM_2,LOW);
  digitalWrite(RM_1,LOW);
  digitalWrite(RM_2,HIGH);
  analogWrite(LMS,TS);
  analogWrite(RMS,S);
}
void left(int S, int TS){
  Stop(); 
  digitalWrite(LM_1,LOW);
  digitalWrite(LM_2,HIGH);
  digitalWrite(RM_1,HIGH);
  digitalWrite(RM_2,LOW);
  analogWrite(LMS,S);
  analogWrite(RMS,TS);
}
void Forward(int RS,int LS){
  digitalWrite(LM_1,HIGH);
  digitalWrite(LM_2,LOW);
  digitalWrite(RM_1,HIGH);
  digitalWrite(RM_2,LOW);
  analogWrite(LMS,LS);
  analogWrite(RMS,RS);
}
void Reverse(int RS,int LS){
  digitalWrite(LM_1,LOW);
  digitalWrite(LM_2,HIGH);
  digitalWrite(RM_1,LOW);
  digitalWrite(RM_2,HIGH);
  analogWrite(LMS,RS);
  analogWrite(RMS,LS); 
}
void Stop(){
  digitalWrite(LM_1,LOW);
  digitalWrite(LM_2,LOW);
  digitalWrite(RM_1,LOW);
  digitalWrite(RM_2,LOW);
  analogWrite(LMS,0);
  analogWrite(RMS,0); 
}
void loop() {
  if (Serial.available()>0) {   //To check if ble connection is active
    data=Serial.read(); //Reading the data from the bluetooth module sent from the device
    Serial.println(data);
    switch(data){                                 //to call the approprate function
      case 's' :Stop();Serial.println("Stop");break;                   
      case 'f' :Forward(190,130);delay(50);Serial.println("Forward");break;
      case 'r' :Reverse(130,190);delay(50);Serial.println("Reverse");break;
      case 'l' :left(110,110);delay(50);Serial.println("Left Turn");break;
      case 'z' :right(110,110);delay(50);Serial.println("Right Turn");break;         
      }      
  }
  if(digitalRead(IR)==HIGH){     //for black line,IR gets adsorbed and hence no o/p will be given
    myservo.write(90);    //To lift the flag
    delay(50);    //To make the flag stay up for 1 sec
    myservo.write(0);     //To take down the flag
  } 
}
 
  
