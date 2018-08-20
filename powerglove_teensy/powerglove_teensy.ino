/* INITIALIZATION */

int flex = 12; // set the wiggle pin
int latch = 5; // set the latch pin
int clock = 11; // set the clock pin
int datin = 8;// set the data in pin
//int glove_power = 22;
byte controller_data = 0;
int ledpin = 13;
bool init_glove = false;

/* SETUP */
void setup() {
  Serial.begin(9600);
  pinMode(latch,OUTPUT);
  pinMode(flex,OUTPUT);
  pinMode(clock,OUTPUT);
  //pinMode(glove_power, OUTPUT);
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
  //flexRead();
  //digitalWrite(flex,HIGH);
  
  Serial.println(controller_data, BIN); 
  
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
