#include <QTRSensors.h>

#define NUM_SENSORS             6  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading

// sensors 0 through 5 are connected to analog inputs 0 through 5, respectively
QTRSensorsAnalog qtra((unsigned char[]) {
  8, 9, 10, 11, 12, 13}
,
NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, QTR_NO_EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];


int MOTOR1_PIN1 = 5;

int MOTOR1_PIN2 = 6;

int MOTOR2_PIN1 = 11;

int MOTOR2_PIN2 = 10;

int buton = 2;

unsigned int last_proportional = 0;
long integral = 0;





void setup() {

  pinMode(MOTOR1_PIN1, OUTPUT);

  pinMode(MOTOR1_PIN2, OUTPUT);

  pinMode(MOTOR2_PIN1, OUTPUT);

  pinMode(MOTOR2_PIN2, OUTPUT);

  pinMode(buton, INPUT);


  delay(500);

  int i;
  pinMode(13, OUTPUT);

  while(digitalRead(buton)==LOW)

  {
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13,LOW);
    delay(500);
  }

  delay(2000);

  digitalWrite(13, HIGH);    // turn on LED to indicate we are in calibration mode
  for (i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
  }
  digitalWrite(13, LOW);     // turn off LED to indicate we are through with calibration






  while(digitalRead(buton)==LOW)
  {
    digitalWrite(13,LOW);
  }


  delay(1500);


}





void loop() {


  unsigned int position = qtra.readLine(sensorValues);

  // The "proportional" term should be 0 when we are on the line.
  int proportional = ((int)position) - 2500;

  // Compute the derivative (change) and integral (sum) of the
  // position.
  int derivative = proportional - last_proportional;
  integral += proportional;

  // Remember the last position.
  last_proportional = proportional;

  int power_difference = proportional*4 + integral/10000 + derivative*7;

  // Compute the actual motor settings.  We never set either motor
  // to a negative value.
  const int max = 255;
  if(power_difference > max)
    power_difference = max;
  if(power_difference < -max)
    power_difference = -max;

  if(power_difference < 0)
    go(max+power_difference, max);
  else
    go(max, max-power_difference);




}


void go(int speedLeft, int speedRight) {

  if (speedLeft > 0) {

    analogWrite(MOTOR1_PIN1, speedLeft);

    analogWrite(MOTOR1_PIN2, 0);

  }

  else {

    analogWrite(MOTOR1_PIN1, 0);

    analogWrite(MOTOR1_PIN2, -speedLeft);

  }



  if (speedRight > 0) {

    analogWrite(MOTOR2_PIN1, speedRight);

    analogWrite(MOTOR2_PIN2, 0);

  }

  else {

    analogWrite(MOTOR2_PIN1, 0);

    analogWrite(MOTOR2_PIN2, -speedRight);

  }

}



