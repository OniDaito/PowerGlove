/* INITIALIZATION */

int flex = 23; // set the wiggle pin
int latch = 21; // set the latch pin
int clock = 22; // set the clock pin
int datin = 20;// set the data in pin
byte controller_data = 0;
int ledpin = 13;
bool init_glove = false;

/* SETUP */
void setup() {
  Serial.begin(9600);
  pinMode(latch,OUTPUT);
  pinMode(flex,OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(datin,INPUT);
  pinMode(ledpin, OUTPUT);

  delay(60);
  //digitalWrite(glove_power,HIGH);
  clear();
}

void clear(){
  digitalWrite(latch,HIGH);
  digitalWrite(clock,HIGH);
  digitalWrite(flex,LOW);
}


void controllerRead() {
  controller_data = 255;
  digitalWrite(latch,LOW);
  digitalWrite(clock,LOW);
  delayMicroseconds(12);
  
  digitalWrite(latch,HIGH);
  delayMicroseconds(12);

  if (digitalRead(datin) == LOW) {
    bitClear(controller_data, 0);
  }

  digitalWrite(latch,LOW);
  delayMicroseconds(6);
  
  for (int i = 1; i < 8; i ++) {
    digitalWrite(clock,HIGH);
    delayMicroseconds(6);
    //controller_data = controller_data << 1;
    //controller_data = controller_data + digitalRead(datin) ;
    if (digitalRead(datin) == LOW) {
      bitClear(controller_data, i);
    }
    digitalWrite(clock,LOW);
    delayMicroseconds(6);
  }
}

void loop() {
  
  if (controller_data == B11111011 && init_glove == false){
    digitalWrite(flex,LOW);
    digitalWrite(ledpin,LOW);
    delay(12);
    //digitalWrite(flex,HIGH); 
    init_glove = true;
  } else {
    
    digitalWrite(flex,LOW);
    digitalWrite(ledpin,LOW);
    delay(12);
    
    digitalWrite(flex,HIGH);
    digitalWrite(ledpin,HIGH);
    controllerRead();
  }
    
  Serial.println(controller_data, BIN); 

  // Easier to invert and have 1 for pressed I think
  controller_data = ~controller_data;
  
  // Now work on the joystick section
  if (controller_data & B00010000){
    if (controller_data & B10000000){
      Joystick.hat(45);
    } else {
      Joystick.hat(0);
    }
  }
 
  else if (controller_data & B10000000){
    if (controller_data & B00100000) {
      Joystick.hat(135); 
    } else {
      Joystick.hat(90);
    }
  }
  
  else if (controller_data & B00100000){
    if (controller_data & B01000000){
      Joystick.hat(225);
    } else {
      Joystick.hat(180);
    }
  }
  
  else if (controller_data & B01000000){
    if (controller_data & B00010000){
      Joystick.hat(315);
    } else {
      Joystick.hat(270);
    }
  }
  
  else {
    Joystick.hat(-1);
  }

  if (controller_data & B00000001){ 
    Joystick.button(1, 1);
  } else {
    Joystick.button(1, 0);
  }
  if (controller_data & B00000010){ 
    Joystick.button(2, 1);
  } else {
    Joystick.button(2, 0);
  }

  if (controller_data & B00000100){ 
    Joystick.button(9, 1);
  } else {
    Joystick.button(9, 0);
  }

  if (controller_data & B00001000){ 
    Joystick.button(10, 1);
  } else {
    Joystick.button(10, 0);
  }
  
  //for REFERENCE:  
  //UP = 11110111
  //DOWN=11111011
  //LEFT=11111101
  //RIGHT=11111110
  //SELECT=11011111
  //START=11101111
  //A=01111111
  //B=10111111
 
  delay(30); 

 }
