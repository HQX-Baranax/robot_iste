#include <IRremote.h>
int RECV_PIN = 10;
#include<SoftwareSerial.h>
SoftwareSerial bluetooth1(0,1);
long bileri = 0xFF18E7; 
long bgeri = 0xFF4AB5;
long bdur = 0xFF38C7;
long bsol = 0xFF10EF;
long bsag = 0xFF5AA5;
long b1 = 0xFFA25D;
long b2 = 0xFF629D;
long b3 = 0xFFE21D;
long b4 = 0xFF22DD;
IRrecv irrecv(RECV_PIN);
decode_results results;
#define SensorSol 11
#define SensorOrta 12
#define SensorSag 13
int trig = 2; 
int echo = 8; 
  const int motorR1  = 6;  // L298N'in IN3 Girişi
  const int motorR2  = 7;  // L298N'in IN1 Girişi
  const int motorRE = 9;
  const int motorL1  = 4; // L298N'in IN2 Girişi
  const int motorL2  = 5;  // L298N'in IN4 Girişi
  const int motorLE = 3;
  int vSpeed=255; 
  char state; //Bluetooth cihazından gelecek sinyalin değişkeni  int vSpeed=255; 
int mode = 0;

void setup() 
{
bluetooth1.begin(9600);
Serial.begin(9600); // Alıcıyı başlat.
pinMode(11, INPUT);// sağ çizgi sensör giriş pini
pinMode(12, INPUT);// sol çizgi sensör giriş pini
pinMode(13, INPUT);// orta çizgi sensör giriş pini
    pinMode(motorR1, OUTPUT);
    pinMode(motorR2, OUTPUT);
    pinMode(motorL1, OUTPUT);
    pinMode(motorL2, OUTPUT);   
 pinMode(trig, OUTPUT); // Mesafe sensörü trig pini çıkış için
pinMode(echo, INPUT); // Mesafe sensörü echo pini giriş için

irrecv.enableIRIn();
  
}


void loop() 
{
  if (results.value == bdur ) Dur();
  if (irrecv.decode(&results)) {
 Serial.println(results.value, HEX);
 irrecv.resume(); // Receive the next value
}
  if (results.value == b1 ){
    mode = 1;
    Serial.println("bluetooth");
    }
  else if (results.value == b2 ){
    mode = 2;
    Serial.println("mesafe");
    }
    else if (results.value == b3 ){
    mode = 3;
    Serial.println("ır");
    }
    else if (results.value == b4 ){
    mode = 4;
    Serial.println("çizgi izleme");
    }
  
if (mode == 1 )
  {
    Serial.println("bluetooth");
if(bluetooth1.available())
{
  state= bluetooth1.read();
Serial.println(state);
  if(state=='L')
    Sol();
  else if(state=='S')
    Dur();
  else if(state=='B')
    Geri();
  else if(state=='F')
    Ileri();
  else if(state=='R')
    Sag();  
  else if(state=='I')
    sagIIeri();
  else if(state=='G')
    solIleri();
  else if(state=='J')
    sagGeri();
  else if(state=='H')
    solGeri();
  }}
  if(mode == 2)//mesafe
  {
    Serial.println("mesafe");
  digitalWrite(trig, 1);
delay (1);
digitalWrite(trig, 0);
int sure = pulseIn(echo, 1);
int mesafe = (sure/2) / 28.97;
if (mesafe < 30) // mesafe 30cm’den küçük ise robotu geri al ve döndür.
{
 Geri();
 delay(150);
 Sag();
 delay(250);
}
else // mesafe 30cm’den büyük ise düz git.
{
 Ileri();
}
  }
  if(mode == 3)
  {
    
 Serial.println("ır");
    
    if (irrecv.decode(&results)) {
 Serial.println(results.value, HEX);
if (results.value == bileri ) Ileri();
if (results.value == bgeri ) Geri(); 
if (results.value == bsag ) Sag();
if (results.value == bsol ) Sol();
if (results.value == bdur ) Dur();
 irrecv.resume(); // Yeni verileri al.
}
  }
  if(mode == 4)
  {
    Serial.println("çizgi izleme");
  if (digitalRead(SensorSol) == 0 && digitalRead(SensorOrta) == 1 && digitalRead(SensorSag) == 0) { // Orta sensör çizgiyi gördüğünde robot ileri gitsin.
    Ileri();
  }

  if (digitalRead(SensorSol) == 0 && digitalRead(SensorOrta) == 0 && digitalRead(SensorSag) == 1) { // Sağ sensör çizgiyi gördüğünde robot sağa dönsün.
    Sag();
  }

  if (digitalRead(SensorSol) == 1 && digitalRead(SensorOrta) == 0 && digitalRead(SensorSag) == 0) { // Sol sensör çizgiyi gördüğünde robot sola dönsün.
    Sol();
  }
  if (digitalRead(SensorSol) == 0 && digitalRead(SensorOrta) == 0 && digitalRead(SensorSag) == 0) { // Sol sensör çizgiyi gördüğünde robot sola dönsün.
    Dur();
  }
  if (digitalRead(SensorSol) == 1 && digitalRead(SensorOrta) == 1 && digitalRead(SensorSag) == 1) { // Sol sensör çizgiyi gördüğünde robot sola dönsün.
    Dur();
  }
    }
  }



void Ileri(){
      digitalWrite(motorR1, HIGH);
      digitalWrite(motorR2, LOW);
      analogWrite(motorRE, vSpeed);

      digitalWrite(motorL1, HIGH);
      digitalWrite(motorL2, LOW);
      analogWrite(motorLE, vSpeed);
  } 

  void Sol(){
      digitalWrite(motorR1, HIGH);
      digitalWrite(motorR2, LOW);
      analogWrite(motorRE, vSpeed);

      digitalWrite(motorL1, LOW);
      digitalWrite(motorL2, LOW);
      analogWrite(motorLE, 0);
  } 

    void Sag(){
      digitalWrite(motorR1, LOW);
      digitalWrite(motorR2, LOW);
      analogWrite(motorRE, 0);

      digitalWrite(motorL1, HIGH);
      digitalWrite(motorL2, LOW);
      analogWrite(motorLE, vSpeed);  
  } 

    void Dur(){
      digitalWrite(motorR1, LOW);
      digitalWrite(motorR2, LOW);
      analogWrite(motorRE, 0);

      digitalWrite(motorL1, LOW);
      digitalWrite(motorL2, LOW);
      analogWrite(motorLE, 0);
  } 
  void Geri(){
      digitalWrite(motorR1, LOW);
      digitalWrite(motorR2, HIGH);
      analogWrite(motorRE, vSpeed);

      digitalWrite(motorL1, LOW);
      digitalWrite(motorL2, HIGH);
      analogWrite(motorLE, vSpeed);
  }
  void sagIIeri(){
      digitalWrite(motorR1, HIGH);
      digitalWrite(motorR2, LOW);
      analogWrite(motorRE, 100);

      digitalWrite(motorL1, HIGH);
      digitalWrite(motorL2, LOW);
      analogWrite(motorLE, vSpeed);
  } 
  void solIleri(){
      digitalWrite(motorR1, HIGH);
      digitalWrite(motorR2, LOW);
      analogWrite(motorRE, vSpeed);

      digitalWrite(motorL1, HIGH);
      digitalWrite(motorL2, LOW);
      analogWrite(motorLE, 100);
  } 
  void sagGeri(){
      digitalWrite(motorR1, LOW);
      digitalWrite(motorR2, HIGH);
      analogWrite(motorRE, vSpeed);

      digitalWrite(motorL1, LOW);
      digitalWrite(motorL2, HIGH);
      analogWrite(motorLE, 100);
  } 
  void solGeri(){
      digitalWrite(motorR1, LOW);
      digitalWrite(motorR2, HIGH);
      analogWrite(motorRE, 100);

      digitalWrite(motorL1, LOW);
      digitalWrite(motorL2, HIGH);
      analogWrite(motorLE, vSpeed);
  } 
