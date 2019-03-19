//A - right motor
//B - left motor

int turndelay=70; //turn delay in ms (change this if you change the turning speed)
int aspeed=80; //Forward speed MOTOR A -- !! Difference 50 !!
int bspeed=126; //Forward speed MOTOR B
int acorrectionspeed=180; //path correction speed ( >forward speed )
int bcorrectionspeed=226;
int aturnspeed=186; //turning speed
int bturnspeed=186;
int lowerthresh=15; //Ultrasonic LOWER threshold distance
int upperthresh=35; //Ultrasonic UPPER threshold distance
int garbage=100;
int uppergarbage=225;
int motora1=10; //motor A (IN1)
int motora2=9; //motor A (IN2)
int motorb1=8; //motor B (IN3)
int motorb2=7; //motor B (IN4)
int aspeedpin=11; //Motor A speed control Pin (EN-A - LEFT MOTOR)
int bspeedpin=6; //Motor B speed control pin (EN-B - RIGHT MOTOR)
int pingpin=3; //US ping pin
int trigpin=5; //US trigger pin
int lsenspin=4; //Left IR sensor
int rsenspin=2; //Right IR sensor
int lread=0; //left IR sensor input
int rread=0; //right IR sensor input
int cm=0; //US reading
/* ---------------------------------*/

/* ---------------------------------*/
void setup() { //initialising pins
  Serial.begin(9600);
  pinMode(pingpin, INPUT); 
  pinMode(trigpin, OUTPUT);
  pinMode(motora1,OUTPUT); 
  pinMode(motora2,OUTPUT);
  pinMode(motorb1,OUTPUT); 
  pinMode(motorb2,OUTPUT);
  pinMode(aspeedpin,OUTPUT);
  pinMode(bspeedpin,OUTPUT);
  pinMode(lsenspin,INPUT); //left IR sensor
  pinMode(rsenspin,INPUT); //right IR sensor
}
/* ---------------------------------*/

/* ---------------------------------*/
int ultra()
{  long duration, cm; //US distance measurement
   digitalWrite(trigpin, LOW);
   delayMicroseconds(2);
   digitalWrite(trigpin, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigpin, LOW);
   duration = pulseIn(pingpin, HIGH);
   cm = microsecondsToCentimeters(duration);
   Serial.println(cm);
   return(cm);
   delay(20);   
}

long microsecondsToCentimeters(long microseconds) { //Return value in cm
   return microseconds / 29 / 2;
}
/* ---------------------------------*/

/* ---------------------------------*/
void infra()
{ //read IR sensor values
  lread=digitalRead(lsenspin);
  rread=digitalRead(rsenspin);
  delay(5);
}
/* ---------------------------------*/

/* ---------------------------------*/
void stopp()
{ Serial.println("stopping");
  digitalWrite(motora1,HIGH); 
  digitalWrite(motora2,HIGH);
  digitalWrite(motorb1,HIGH);
  digitalWrite(motorb2,HIGH);
}
/* ---------------------------------*/

/* ---------------------------------*/
void correct() //path correction 
{ 
  if(lread==HIGH && rread==LOW)
  { aspeedpin=acorrectionspeed;
    delay(50);
    Serial.println("correcting path");
  }
  else if(rread==HIGH && lread==LOW)
  { 
  bspeedpin=bcorrectionspeed;
  delay(50);
  Serial.println("correcting path");
  }
  else
  {
    loop();
  }
} 
/* ---------------------------------*/

/* ---------------------------------*/
void forward()
{ analogWrite(aspeedpin,aspeed);
  analogWrite(bspeedpin,bspeed);
  digitalWrite(motora1,LOW); 
  digitalWrite(motora2,HIGH);
  digitalWrite(motorb1,HIGH);
  digitalWrite(motorb2,LOW);
  Serial.println("moving forward");
  correct();
}
/* ---------------------------------*/

/*void forward2()
{ analogWrite(aspeedpin,aspeed);
  analogWrite(bspeedpin,bspeed);
  digitalWrite(motora1,LOW); 
  digitalWrite(motora2,HIGH);
  digitalWrite(motorb1,HIGH);
  digitalWrite(motorb2,LOW);
  Serial.println("moving forward(moredelay)");
  delay(250);                                                                                                                     
}*/

/* ---------------------------------*/

void left()
{ analogWrite(bspeedpin,bturnspeed);
  analogWrite(aspeedpin,aturnspeed);
  if(cm<=upperthresh || cm>=garbage)
  {
 Serial.println("turning left");
 digitalWrite(motora1,LOW);
 digitalWrite(motora2,HIGH);
 digitalWrite(motorb1,LOW);
 digitalWrite(motorb2,HIGH);
 delay(turndelay);
  }
  else
  {
    loop();
  }
}
/* ---------------------------------*/


/* ---------------------------------*/
void right()
{ analogWrite(bspeedpin,bturnspeed);
  analogWrite(aspeedpin,aturnspeed);
 if(cm<=upperthresh || cm>=garbage)
 {
 digitalWrite(motora1,HIGH);
 digitalWrite(motora2,LOW);
 digitalWrite(motorb1,HIGH);
 digitalWrite(motorb2,LOW);
 Serial.println("turning right");
 delay(turndelay);
 }
 else
 {
  loop();
 }
}
/* ---------------------------------*/

/* ---------------------------------*/
void patherror()
{ Serial.println("path error");
  Serial.println("checking right");
  right();
  delay(120); //150

  if(cm>=upperthresh && cm<garbage)
  {
    loop();
  }
  
  else
  { 
   Serial.println("checking left");
   left(); 
   left();
   //delay(700); //for 180   
  }

  
  
  /*else if(cm<=lowerthresh)
  { 
   delay(500);
   Serial.println("checking left");
   left(); 
   left();
   delay(400); //for 180   
   loop();
  } */  
}
/* ---------------------------------*/

/* ---------------------------------*/
void loop() {
  cm=ultra();
  infra();
  if(cm<=lowerthresh || (cm>garbage && cm<uppergarbage))
  {
    stopp();
    if(lread==HIGH && rread==LOW)
    {
      right();
    }

    else if(rread==HIGH  && lread==LOW)
    { 
      left();
    } 

    else if(rread==LOW && lread==LOW)
    {
      patherror();
    } 
  }
  
  else if((cm>lowerthresh && cm<garbage && lread==HIGH && rread==HIGH) || (cm>lowerthresh && cm<garbage) || cm>uppergarbage)
  {
    forward();
  }

  /*else if(rread==HIGH && lread==HIGH)
    {
      forward2();
    } */
  }
