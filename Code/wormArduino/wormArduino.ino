#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

float servo1Value = 120;
float servo2Value = 120;
float servo3Value = 120;
float servo4Value = 120;

float servo1ValuePrev = 120;
float servo2ValuePrev = 120;
float servo3ValuePrev = 120;
float servo4ValuePrev = 120;

float servo1ValueSmoothed = 120;
float servo2ValueSmoothed = 120; 
float servo3ValueSmoothed = 120;
float servo4ValueSmoothed = 120;

int timeDelay = 700;
int shorter = 130;
int longer = 50;

unsigned long currentMillis;
long previousMillis = 0;    // set up timers
long interval = 10;        // time constant for timer

int stepFlag = 0;
long previousStepMillis = 0;

void setup() {
  servo1.attach(8);
  servo2.attach(9);
  servo3.attach(10);
  servo4.attach(11);

  servo1.write(120); 
  servo2.write(120);
  servo3.write(120);
  servo4.write(120); 

  Serial.begin(115200);

 
}

void loop() {


    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {  // start 5ms timed loop  
        previousMillis = currentMillis; 

        if (stepFlag == 0 && currentMillis - previousStepMillis > timeDelay) {
          servo1Value = longer;
          servo2Value = shorter;
          servo3Value = shorter;
          servo4Value = shorter;
          stepFlag = 1;
          previousStepMillis = currentMillis;
        }
             
        else if (stepFlag == 1 && currentMillis - previousStepMillis > timeDelay) {
          servo1Value = shorter;
          servo2Value = longer;
          servo3Value = shorter;
          servo4Value = shorter; 
          stepFlag = 2;
          previousStepMillis = currentMillis;
        }

        else if (stepFlag == 2 && currentMillis - previousStepMillis > timeDelay) {
          servo1Value = shorter;
          servo2Value = shorter;
          servo3Value = longer;
          servo4Value = shorter;
          stepFlag = 3;
          previousStepMillis = currentMillis;
        }

        else if (stepFlag == 3 && currentMillis - previousStepMillis > timeDelay) {
          servo1Value = shorter;
          servo2Value = shorter;
          servo3Value = shorter;
          servo4Value = longer;
          stepFlag = 0;
          previousStepMillis = currentMillis;
        }

        else if (stepFlag == 4 && currentMillis - previousStepMillis > timeDelay) {
          servo1Value = shorter;
          servo2Value = shorter;
          servo3Value = shorter;
          servo4Value = shorter;
          stepFlag = 0;
          previousStepMillis = currentMillis;        } 

        servo1ValueSmoothed = (servo1Value * 0.03) + (servo1ValuePrev * 0.97); 
        servo2ValueSmoothed = (servo2Value * 0.03) + (servo2ValuePrev * 0.97);
        servo3ValueSmoothed = (servo3Value * 0.03) + (servo3ValuePrev * 0.97);
        servo4ValueSmoothed = (servo4Value * 0.03) + (servo4ValuePrev * 0.97); 

        servo1ValuePrev = servo1ValueSmoothed;
        servo2ValuePrev = servo2ValueSmoothed;
        servo3ValuePrev = servo3ValueSmoothed;
        servo4ValuePrev = servo4ValueSmoothed;

        Serial.print(servo2Value);
        Serial.print(" , " );
        Serial.println(servo2ValueSmoothed);
    
        servo1.write(servo1ValueSmoothed); 
        servo2.write(servo2ValueSmoothed);
        servo3.write(servo3ValueSmoothed);
        servo4.write(servo4ValueSmoothed); 


    }
    

}


