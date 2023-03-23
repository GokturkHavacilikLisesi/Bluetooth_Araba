#include <NewPing.h>

#define TRIGGER_PIN 11  //Sensörün TRİGGER pinini atıyoruz
#define ECHO_PIN 10     //Sensörün ECHO pinini atıyoruz
#define MAX_DISTANCE 400  //Sensörün maximum mesafesini ayarlıyoruz
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
float duration, distance;

char t; //Serial verisini atıyoruz
 
void setup() {
pinMode(13,OUTPUT);   //Sol motor ileri
pinMode(12,OUTPUT);   //Sol motor tersi
pinMode(11,OUTPUT);   //Sağ motor ileri
pinMode(10,OUTPUT);   //Sağ motor tersi
pinMode(8,OUTPUT);    //Led
pinMode(9,OUTPUT);    //Buzzer
Serial.begin(9600);
 
}

void YakinikKontrol(){
  distance = sonar.ping_cm();
  if (distance <= 12) {.   //Bir cisim 12cm den daha yakına gelir ise motorlara GERİ komutu ver.
    Serial.println("YAKIN!");
    digitalWrite(12,HIGH);
    digitalWrite(10,HIGH);
  }
  Serial.print(distance);Serial.println(" cm");
}

 
void loop() {
  YakinikKontrol();
  
  if(Serial.available()){ //Serial Bağlantı Olduğunda Çalışacak Fonksiyon
    t = Serial.read();
    Serial.println(t);
  }
 
  if(t == 'F'){            // İLERİ (F) Komutu Geldiğinde Çalışacak Fonksiyon
    t = Serial.read();
    digitalWrite(13,HIGH);
    digitalWrite(11,HIGH);
  }
 
  else if(t == 'B'){      // GERİ (B) Komutu Geldiğinde Çalışacak Fonksiyon
    digitalWrite(12,HIGH);
    digitalWrite(10,HIGH);
  }
 
  else if(t == 'L'){      // SOL (L) Komutu Geldiğinde Çalışacak Fonksiyon
    digitalWrite(13,HIGH);
  }
  
  else if(t == 'R'){      // SAĞ (R) Komutu Geldiğinde Çalışacak Fonksiyon
    digitalWrite(11,HIGH);
  }
  else if(t == 'S'){      //TÜM MOTORLARI DURDURACAK FONKSİYON
    digitalWrite(13,LOW);
    digitalWrite(12,LOW);
    digitalWrite(11,LOW);
    digitalWrite(10,LOW);
  }

  else if(t == 'W'){        // IŞIKLARI ÇALIŞTIRIR
    digitalWrite(9,HIGH);
  }
  else if(t == 'w'){.     // IŞIKLARI KAPATIR
    digitalWrite(9,LOW);
  } 
  else if(t == 'V'){      // KORNAYI ÇALAR
    digitalWrite(7,HIGH);
  }
  else if(t == 'v'){      // KORNAYI DURDURUR
    digitalWrite(7,LOW);
  }

}
