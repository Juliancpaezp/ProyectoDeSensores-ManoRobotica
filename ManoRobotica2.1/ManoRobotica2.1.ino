/*A continuacion se muestra el diagrama de conexiones

      .----------------
      |                |
      |                |
      |               .-.
      |               | |<-- (0-50)K
      |               | |
      |               '-'
    (5V)               |
      |                o------------o
      |                |
      |               .-.
      |               | |
      |               | | 30 K   Arduino
      |               '-'
      |                |
      '----------------o------------o
*/

#include <Servo.h>
#include <SoftwareSerial.h>

#define ledV 7
#define ledR 8
#define ledA 2

#define pulgar  4
#define indice  3
#define corazon 2
#define anular  1
#define menique 0
#define calibrationTime 2000

Servo servoPulgar;
Servo servoIndice;
Servo servoCorazon;
Servo servoAnular;
Servo servoMenique;

int posPulgar = 0;
int posIndice = 0;
int posCorazon = 0;
int posAnular = 0;
int posMenique = 0;

int potPulgar[10];
int potIndice = 0;
int potCorazon = 0;
int potAnular = 0;
int potMenique = 0;

int pph;
int pih;
int pch;
int pah;
int pmh;
int ppl;
int pil;
int pcl;
int pal;
int pml;

int p = 0;


void setup() {
  servoPulgar.attach(10);
  servoIndice.attach(9);
  servoCorazon.attach(6);
  servoAnular.attach(5);
  servoMenique.attach(3);
  
  Serial.begin(9600);
  
  pinMode(ledR, OUTPUT);    
  pinMode(ledA, OUTPUT);
  pinMode(ledV, OUTPUT);

  digitalWrite(ledR,HIGH);
  digitalWrite(ledA,HIGH);
  digitalWrite(ledV,HIGH);
  
/*
  Serial.println("Por favor, abra la mano.");
    digitalWrite(ledV, HIGH);
    delay(calibrationTime);
    Serial.println("Guardando datos...");
    pph = analogRead(4);
    pih = analogRead(3);
    pch = analogRead(2);
    pah = analogRead(1);
    pmh = analogRead(0);
    delay(5);
    Serial.println("Por favor, cierre la mano.");
    digitalWrite(ledV, LOW);
    digitalWrite(ledR, HIGH);
    delay(calibrationTime);
    Serial.println("Guardando datos...");
    ppl = analogRead(4);
    pil = analogRead(3);
    pcl = analogRead(2);
    pal = analogRead(1);
    pml = analogRead(0);
    delay(5);
    Serial.println("Hecho.");
    digitalWrite(ledR, LOW);
    
    Serial.print("pph = "); Serial.print(pph); Serial.print(", ppl = "); Serial.println(ppl);
    Serial.print("pih = "); Serial.print(pih); Serial.print(", pil = "); Serial.println(pil);
    Serial.print("pch = "); Serial.print(pch); Serial.print(", pcl = "); Serial.println(pcl);
    Serial.print("pah = "); Serial.print(pah); Serial.print(", pal = "); Serial.println(pal);
    Serial.print("pmh = "); Serial.print(pmh); Serial.print(", pml = "); Serial.println(pml);
    */
}

void loop() {

  potPulgar[1] = potPulgar[0];
  potPulgar[0] = analogRead(4);
  posPulgar = abs(map(potPulgar, 50, 820, 1, 80));  
  servoPulgar.write(posPulgar);
  Serial.print(" Pulgar: "); Serial.print(potPulgar[0]); Serial.print(" , "); Serial.print(posPulgar);

  potIndice = analogRead(3);
  posIndice = abs(map(potIndice, 150, 860,  1, 80));  
  servoIndice.write(posIndice);
  Serial.print(" Indice: "); Serial.print(potIndice); Serial.print(" , "); Serial.print(posIndice);

  potCorazon = analogRead(2);
  posCorazon = abs(map(potCorazon, 50, 900,  1, 50));  
  servoCorazon.write(posCorazon);
  Serial.print(" Corazon: "); Serial.print(potCorazon); Serial.print(" , "); Serial.print(posCorazon);

  potAnular = analogRead(1);
  posAnular = abs(map(potAnular, 50, 900,  1, 50));  
  servoAnular.write(posAnular);
  Serial.print(" Anular: "); Serial.print(potAnular); Serial.print(" , "); Serial.print(posAnular);

  potMenique = analogRead(0);
  posMenique = abs(map(potMenique, 50, 900,  1, 50));  
  servoMenique.write(posMenique);
  Serial.print(" Menique: "); Serial.print(potMenique); Serial.print(" , "); Serial.println(posMenique);

  delay(1);
}

float linealizar(float x, float in_min, float in_max, float out_min, float out_max){
  if (x < in_min){
     return out_min;
  }
  if (x > in_max){
    return out_max;
  }
  if (x > in_min && x < in_max){
     return (log(( x - in_min) * (out_max - out_min) / ((in_max - in_min)))/log(out_max))*out_max;
  }
}
//
//void moverServo (int pin, int angulo)
//{
//   float ang = (angulo*1000)/180;
//   digitalWrite(pin,HIGH);
//   delayMicroseconds(1+ang);
//   digitalWrite(pin,LOW);
//   delayMicroseconds(19-ang);
//}
