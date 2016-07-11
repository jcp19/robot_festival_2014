#include <Wire.h>
#include <QTRSensors.h>

#define NUM_SENSORS 6 // number of sensors used
#define NUM_SAMPLES_PER_SENSOR 4 // average 4 analog samples per sensor reading

// sensors 0 through 5 are connected to analog inputs 0 through 5, respectively
QTRSensorsAnalog qtra((unsigned char[]) {8, 9, 10, 11, 12, 13}, NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, QTR_NO_EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];
int r=300;
boolean na_linha = true;

void setup(){
  Serial.begin(9600);
  pinMode(8, OUTPUT);   // sets the pin as output
  pinMode(9, OUTPUT);   // sets the pin as output
  pinMode(10, OUTPUT);   // sets the pin as output
  pinMode(11, OUTPUT);   // sets the pin as output
  pinMode(12, OUTPUT);   // sets the pin as output
  pinMode(13, OUTPUT);   // sets the pin as output
  int i;
  for (i = 0; i < 200; i++)  // make the calibration take about 5 seconds
  {
    qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
  }
}
void loop()
{
  segue_linha();
}
void segue_linha()
{
  qtra.read(sensorValues);
   /*if (sensorValues[1] >= r && sensorValues[2] >= r && sensorValues[3] >= r && sensorValues[4] >= r && sensorValues[5] >= r){
    canto_esquerda();
  }*/
 /* else if (sensorValues[2] >= r && sensorValues[3] >= r && sensorValues[4] >= r && sensorValues[5] >= r && sensorValues[6] >= r){
   verificar_linha();
  }*/
  if(na_linha = true){
   if (sensorValues[1] >= r && sensorValues[2] >= r && sensorValues[3] >= r && sensorValues[4] >= r){
   canto_esquerda();
  }
  else if (sensorValues[2] >= r && sensorValues[3] >= r && sensorValues[4] >= r && sensorValues[5] >= r){
    frente();
  }
  else if (sensorValues[3] >= r && sensorValues[4] >= r && sensorValues[5] >= r && sensorValues[6] >= r){
    direita_canto();
  }
  else if (sensorValues[1] >= r && sensorValues[2] >= r && sensorValues[3] >= r){
    esquerda();
  }
  else if (sensorValues[2] >= r && sensorValues[3] >= r && sensorValues[4] >= r){
    esquerda_pequena();
  }
  else if (sensorValues[3] >= r && sensorValues[4] >= r && sensorValues[5] >= r){
    direita_pequena();
  }
  else if (sensorValues[3] >= r && sensorValues[4] >= r && sensorValues[5] >= r ){
    direita();
  }
  else if (sensorValues[4] >= r && sensorValues[5] >= r && sensorValues[6] >= r){
    direita();
  }
  else if (sensorValues[1] >= r && sensorValues[2] >= r){
    esquerda;
  }
  else if (sensorValues[2] >= r && sensorValues[3] >= r){
    esquerda_pequena();
  }
  else if (sensorValues[3] >= r && sensorValues[4] >= r){
    frente;
  }
  else if (sensorValues[4] >= r && sensorValues[5] >= r){
    direita_pequena();
  }
  else if (sensorValues[5] >= r && sensorValues[6] >= r){
    direita();
  }
  else if (sensorValues[1] >= r){
    esquerda_grande();
  }
  else if (sensorValues[2] >= r){
    esquerda();
  }
  else if (sensorValues[3] >= r || sensorValues[4] >= r){
    frente();
  }
  else if (sensorValues[5] >= r){
    direita();
  }
  else if (sensorValues[6] >= r){
    direita_grande();
  }else if(sensorValues[1] < r && sensorValues[2] < r && sensorValues[3] < r && sensorValues[4] < r && sensorValues[5] < r && sensorValues[6] < r){
    na_linha = false;
  }

}else if(/*aumenta inclinação*/){
  
  }else{
    // manter a distancia ao norte
    for(int j=0; j<6; j++){
      if(sensorValues[j]>=r){
        na_linha=true;
        break;
      }
    }
  }
}
void frente(){
  analogWrite(10, 63);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  analogWrite(11, 65);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
}
void esquerda(){
  analogWrite(10, 95);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  analogWrite(11, 0);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
}
void direita(){
  analogWrite(10, 0);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  analogWrite(11, 90);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
}
  void para(){
  analogWrite(10, 0);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  analogWrite(11, 0);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
}
void canto_esquerda(){
  analogWrite(10, 143);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  analogWrite(11, 0);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
}
void verificar_linha(){
  analogWrite(10, 140);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  analogWrite(11, 140);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
}
void esquerda_pequena(){
  analogWrite(10, 150);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  analogWrite(11, 30);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
}
void direita_pequena(){
  analogWrite(10, 30);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  analogWrite(11, 150);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
}
void esquerda_grande(){
  analogWrite(10, 90);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  analogWrite(11, 90);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
}
void direita_grande(){
  analogWrite(10, 90);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  analogWrite(11, 90);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
}
/*void traz(){
  analogWrite(10, 65);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  analogWrite(11, 65);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
}*/
void direita_canto(){
  analogWrite(10, 0);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  analogWrite(11, 143);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
}
