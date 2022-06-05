  const int motorR1  = 6;  // L298N'in IN3 Girişi
  const int motorR2  = 7;  // L298N'in IN1 Girişi
  const int motorRE = 9;
  const int motorL1  = 4; // L298N'in IN2 Girişi
  const int motorL2  = 5;  // L298N'in IN4 Girişi
  const int motorLE = 3;

  int state; //Bluetooth cihazından gelecek sinyalin değişkeni
  int vSpeed=255;     // Standart Hız, 0-255 arası bir değer alabilir

void setup() {
    // Pinlerimizi belirleyelim
    pinMode(motorR1, OUTPUT);
    pinMode(motorR2, OUTPUT);
    pinMode(motorL1, OUTPUT);
    pinMode(motorL2, OUTPUT);    
    // 9600 baud hızında bir seri port açalım
    Serial.begin(9600);
}
 
void loop() {
  /*Bluetooth bağlantısı koptuğunda veya kesildiğinde arabayı durdur.
 (Aktif etmek için alt satırın "//" larını kaldırın.)*/
//   if(digitalRead(BTState)==LOW) { state='S'; }

  //Gelen veriyi 'state' değişkenine kaydet
    if(Serial.available() > 0){     
      state = Serial.read();   
    }
  /***********************İleri****************************/
  //Gelen veri 'F' ise araba ileri gider.
    if (state == 'F') {
      digitalWrite(motorR1, HIGH);
      digitalWrite(motorR2, LOW);
      analogWrite(motorRE, vSpeed);

      digitalWrite(motorL1, HIGH);
      digitalWrite(motorL2, LOW);
      analogWrite(motorLE, vSpeed);
    }
  /**********************İleri Sol************************/
  //Gelen veri 'G' ise araba ileri sol(çapraz) gider.
    else if (state == 'G') {
      digitalWrite(motorR1, HIGH);
      digitalWrite(motorR2, LOW);
      analogWrite(motorRE, vSpeed);

      digitalWrite(motorL1, HIGH);
      digitalWrite(motorL2, LOW);
      analogWrite(motorLE, 100);
    }
  /**********************İleri Sağ************************/
  //Gelen veri 'I' ise araba ileri sağ(çapraz) gider.
    else if (state == 'I') {
      digitalWrite(motorR1, HIGH);
      digitalWrite(motorR2, LOW);
      analogWrite(motorRE, 100);

      digitalWrite(motorL1, HIGH);
      digitalWrite(motorL2, LOW);
      analogWrite(motorLE, vSpeed);
    }
  /***********************Geri****************************/
  //Gelen veri 'B' ise araba geri gider.
    else if (state == 'B') {
      digitalWrite(motorR1, LOW);
      digitalWrite(motorR2, HIGH);
      analogWrite(motorRE, vSpeed);

      digitalWrite(motorL1, LOW);
      digitalWrite(motorL2, HIGH);
      analogWrite(motorLE, vSpeed);
    }
  /**********************Geri Sol************************/
  //Gelen veri 'H' ise araba geri sol(çapraz) gider
    else if (state == 'H') {
      digitalWrite(motorR1, LOW);
      digitalWrite(motorR2, HIGH);
      analogWrite(motorRE, 100);

      digitalWrite(motorL1, LOW);
      digitalWrite(motorL2, HIGH);
      analogWrite(motorLE, vSpeed);
    }
  /**********************Geri Sağ************************/
  //Gelen veri 'J' ise araba geri sağ(çapraz) gider
    else if (state == 'J') {
      digitalWrite(motorR1, LOW);
      digitalWrite(motorR2, HIGH);
      analogWrite(motorRE, vSpeed);

      digitalWrite(motorL1, LOW);
      digitalWrite(motorL2, HIGH);
      analogWrite(motorLE, 100);
    }
  /***************************Sol*****************************/
  //Gelen veri 'L' ise araba sola gider.
    else if (state == 'L') {
      digitalWrite(motorR1, HIGH);
      digitalWrite(motorR2, LOW);
      analogWrite(motorRE, vSpeed);

      digitalWrite(motorL1, LOW);
      digitalWrite(motorL2, LOW);
      analogWrite(motorLE, 0);
    }
  /***************************Sağ*****************************/
  //Gelen veri 'R' ise araba sağa gider
    else if (state == 'R') {
      digitalWrite(motorR1, LOW);
      digitalWrite(motorR2, LOW);
      analogWrite(motorRE, 0);

      digitalWrite(motorL1, HIGH);
      digitalWrite(motorL2, LOW);
      analogWrite(motorLE, vSpeed);    
    }
  
  /************************Stop*****************************/
  //Gelen veri 'S' ise arabayı durdur.
    else if (state == 'S'){
      digitalWrite(motorR1, LOW);
      digitalWrite(motorR2, LOW);
      analogWrite(motorRE, 0);

      digitalWrite(motorL1, LOW);
      digitalWrite(motorL2, LOW);
      analogWrite(motorLE, 0);
    }  
}
