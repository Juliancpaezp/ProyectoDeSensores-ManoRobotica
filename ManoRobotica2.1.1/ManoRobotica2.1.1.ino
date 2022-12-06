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
//#include <SoftwareSerial.h>

#define ledV 7
#define ledR 8
#define ledA 2

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

int potPulgar [11];
int potIndice [11];
int potCorazon[11];
int potAnular [11];
int potMenique[11];

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
}

void loop() {

  if(p > 5){
    digitalWrite(ledR,HIGH);
    digitalWrite(ledA,HIGH);
    digitalWrite(ledV,HIGH); 
  }if(p < 5){
    digitalWrite(ledR,LOW);
    digitalWrite(ledA,LOW);
    digitalWrite(ledV,LOW);
  }if(p == 10){
    p = 0;
  }
  p = p + 1;
  
  
  /*potPulgar[9] = potPulgar[8];
  potPulgar[8] = potPulgar[7];
  potPulgar[7] = potPulgar[6];
  potPulgar[6] = potPulgar[5];
  potPulgar[5] = potPulgar[4];*/
  potPulgar[4] = potPulgar[3];
  potPulgar[3] = potPulgar[2];
  potPulgar[2] = potPulgar[1];
  potPulgar[1] = potPulgar[0];
  potPulgar[0] = analogRead(1);
  potPulgar[10] = (potPulgar[1] + potPulgar[2] + potPulgar[3] + potPulgar[4] )/4;// + potPulgar[5] + potPulgar[6] + potPulgar[7] + potPulgar[8] + potPulgar[9])/9;
  //posPulgar = abs(map(potPulgar[10], 0, 20,  1, 70)); 
  servoPulgar.write(posPulgar);
  Serial.print(" Pulgar: "); Serial.print(potPulgar[10]); Serial.print(" , "); Serial.print(posPulgar);
    

  /*potIndice[9] = potIndice[8];
  potIndice[8] = potIndice[7];
  potIndice[7] = potIndice[6];
  potIndice[6] = potIndice[5];
  potIndice[5] = potIndice[4];*/
  potIndice[4] = potIndice[3];
  potIndice[3] = potIndice[2];
  potIndice[2] = potIndice[1];
  potIndice[1] = potIndice[0];
  potIndice[0] = analogRead(0);
  potIndice[10] = (potIndice[1] + potIndice[2] + potIndice[3] + potIndice[4] )/4;// + potIndice[5] + potIndice[6] + potIndice[7] + potIndice[8] + potIndice[9])/9;
  posIndice = abs(map(potIndice[10], 0, 20, 1,60));  
  servoIndice.write(posIndice);
  Serial.print(" Indice: "); Serial.print(potIndice[10]); Serial.print(" , "); Serial.print(posIndice);

  /*potCorazon[9] = potCorazon[8];
  potCorazon[8] = potCorazon[7];
  potCorazon[7] = potCorazon[6];
  potCorazon[6] = potCorazon[5];
  potCorazon[5] = potCorazon[4];*/
  potCorazon[4] = potCorazon[3];
  potCorazon[3] = potCorazon[2];
  potCorazon[2] = potCorazon[1];
  potCorazon[1] = potCorazon[0];
  potCorazon[0] = analogRead(2);
  potCorazon[10] = (potCorazon[1] + potCorazon[2] + potCorazon[3] + potCorazon[4] )/4;// + potCorazon[5] + potCorazon[6] + potCorazon[7] + potCorazon[8] + potCorazon[9])/9;
  posCorazon = abs(map(potCorazon[10],  1, 200, 1, 80));  
  servoCorazon.write(posCorazon);
  Serial.print(" Corazon: "); Serial.print(potCorazon[10]); Serial.print(" , "); Serial.print(posCorazon);


  /*potAnular[9] = potAnular[8];
  potAnular[8] = potAnular[6];
  potAnular[7] = potAnular[5];
  potAnular[6] = potAnular[5];
  potAnular[5] = potAnular[4];*/
  potAnular[4] = potAnular[3];
  potAnular[3] = potAnular[2];
  potAnular[2] = potAnular[1];
  potAnular[1] = potAnular[0];
  potAnular[0] = analogRead(3);
  potAnular[10] = (potAnular[1] + potAnular[2] + potAnular[3] + potAnular[4] )/4;// + potAnular[5] + potAnular[6] + potAnular[7] + potAnular[8] + potAnular[9])/9;
  posAnular = abs(map(potAnular[10], 0, 120, 1, 40));  
  servoAnular.write(posAnular);
  Serial.print(" Anular: "); Serial.print(potAnular[10]); Serial.print(" , "); Serial.print(posAnular);

  /*potMenique[9] = potMenique[8];
  potMenique[8] = potMenique[7];
  potMenique[7] = potMenique[6];
  potMenique[6] = potMenique[5];
  potMenique[5] = potMenique[4];*/
  potMenique[4] = potMenique[3];
  potMenique[3] = potMenique[2];
  potMenique[2] = potMenique[1];
  potMenique[1] = potMenique[0];
  potMenique[0] = analogRead(4);
  potMenique[10] = (potMenique[1] + potMenique[2] + potMenique[3] + potMenique[4] )/4;// + potMenique[5] + potMenique[6] + potMenique[7] + potMenique[8] + potMenique[9])/9;
  posMenique = abs(map(potMenique[10], 30, 220,  1, 70)); 
  servoMenique.write(posMenique);
  Serial.print(" Menique: "); Serial.print(potMenique[10]); Serial.print(" , "); Serial.println(posMenique);

  delay(1);
}
