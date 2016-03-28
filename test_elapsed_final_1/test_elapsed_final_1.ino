// create elapsedMillis outside loop(), to
// retain its value each time loop() runs.
#include <elapsedMillis.h>
#include <Servo.h>
#include <SoftPWM.h>
#include <Math.h>

elapsedMillis timer;
elapsedMillis timerDelta;
elapsedMillis timerDelta1;
elapsedMillis sincePrint;
static int black = 413; //ms
int deltaStep, deltaStep1;//ms
bool isLeft = true;
int indexOpening = 0;
bool setupBassOneShot = true;
bool setupWhisp1 = true;
bool setupWhisp2 = true;
bool setupWhisp3 = true;
bool setupWhisp4 = true;
bool oneShotOff1 = true;
bool oneShotOff2 = true;
bool oneShotOff3 = true;
bool oneShotOff4 = true;
bool oneShotOff5 = true;
bool oneShotOff6 = true;
bool oneShotOff7 = true;
bool oneShotOff8 = true;
bool oneShotOff9 = true;
bool oneShotOff10 = true;
bool oneShotOff11 = true;
bool oneShotOff12 = true;
int beatCpt = 0;
float decrescendo;

int i;
int wIndex = 0;
unsigned int stepIndex;
float flashLed[] = {0, .125, .250, .500, .250, .125, 0};
int flashLedLen = (sizeof(flashLed) / sizeof(int));
float ledShortWhisper[] = {0, .125, .125, .250, .250, .500, .500, .500, .500, .750, .750, .750, .750, 1, 1, 1, 1, .750, .750, .750, .750, .500, .500, .500, .500, .250, .250, .125, .125, 0};
int ledShortWhisperLen = (sizeof(ledShortWhisper) / sizeof(int));
int ledLongWhisper[] = {};
int ledLongWhisperLen = (sizeof(ledLongWhisper) / sizeof(int));
float break1[] = {1, .75, .75, .50, .50, .25, .125, .0725, .0725, .036, .036, .017, .017 , 0, 0, 0 , 0, 0};
int break1Len = (sizeof(break1) / sizeof(int));
int fullHatOpening[] = {};
int fullHatOpeningLen = (sizeof(fullHatOpening) / sizeof(int));

//TIMING
unsigned int startBass = 13244;
unsigned int steps[] = {178, 657, 1148, 1655, 2149, 2631, 3102, 3611, 3958, 4566, 5058, 5575, 6155, 6743, 7299, 7869, 8489, 9039, 9579, 10109, 10606, 11132, 11658, 12227, 12720};
unsigned int stepsLen = (sizeof(steps) / sizeof(unsigned int));
unsigned int whispers[] = {26062, 32740};
unsigned int whispersEnd[] = {27100, 33740};
unsigned int whispersLen = (sizeof(whispers) / sizeof(unsigned int));
unsigned int bigWhispers[] = {39740, 46339};
unsigned int bigWhispersEnd[] = {46310, 52733};
unsigned int bigWhispersLen = (sizeof(bigWhispers) / sizeof(unsigned int));


unsigned int beatStart = 52733;
unsigned measureStart = 52951;
unsigned beatNote = 58772 - 58358;
unsigned int breakStart = 79455;
unsigned beatBreak = 81101 - breakStart;
unsigned int blablaStart = 91881;//Cri Pulsation Led
unsigned int beatBlabla = 92207 - 92097;
unsigned int blablaEndGuitarStart = 92685;//Fin Cri Pulsation led Ouverture Coiffe
unsigned int beatGuitarBeat = 96831 - 96011;
unsigned int endOpeningCoiffe = 105767;
unsigned int openingCoiffe2 = 112483;
unsigned int break2StartEndOpeningCoiff2 = 119179;
unsigned int beatBreak2 = 121253 - break2StartEndOpeningCoiff2;
unsigned int restartBreak = 131174;
unsigned int restartBreakEndSlowBeatStart = 133248;
unsigned int beatSlowBeat = 141522 - 140681;
unsigned int break3Start = 145657;
unsigned int beatBreak3 = 148137 - 147739;
unsigned int endStart = 165751;
unsigned int startVibrato1 = 172131;
unsigned int startVibrato2 = 186411;
unsigned int endTrax = 201978;



/*
  unsigned int endFirstWhisper = 27100;
  unsigned int startSecondWhisper = 32.74 * 1000;
  unsigned int endSecondWhisper = 33.74 * 1000;
  unsigned int startThirdWhisper = 39.72 * 1000;
  unsigned int endThirdWhisper = 45.97 * 1000;
  unsigned int startFourthWhisper = 46.51 * 1000;
  unsigned int endFourthdWhisper = 52.76 * 1000;
  unsigned int kick1 = 52.97 * 1000;
  unsigned int snare1 = 53.78 * 1000;
  unsigned int Kick2 = 54 * 1000;
  unsigned int snare2 = 55.44 * 1000;
  unsigned int kick3 = 55.95 * 1000;
  unsigned int pulseVoiceLedStart = 91.76 * 1000;
  unsigned int pulseVoiceLedEnd = 92.71 * 1000;
  unsigned int guitLead1CoiffOpen = 92.71 * 1000;
  unsigned int guitLead2CoiffClose = 105.88 * 1000;
  unsigned int guitLeadVoixEcho = 115.85 * 1000;
  unsigned int guitLeadVoixEchoEnd = 119.16 * 1000;
  unsigned int guitLeadVoixEchoBarkStart = 119.17 * 1000;
  unsigned int BassBarkStart = 132.52 * 1000;
  unsigned int restartBeat = 145.62 * 1000;
  unsigned int lowerIntensity = 172.06 * 1000;
*/

//LED AND SERVO
static int JAMBE_1 = 17;
static int JAMBE_2 = 16;
static int LED_1 = 19;
static int LED_2 = 18;
static int PETALE_1 = 23;
static int PETALE_2 = 22;
static int PETALE_3 = 21;
static int PETALE_4 = 20;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int valLed = 0;
int valWhisper = 0;

int calcIndex(float elapsedTime, float startTime, float endTime, int sizeArray) {
  return constrain((int) ((float)(sizeArray - 1) * (elapsedTime - startTime) / (endTime - startTime)), 0, sizeArray - 1);
}
bool testInTime(float ellapsedTime, float startTime, float endTime) {
  return (ellapsedTime >= startTime) && (ellapsedTime < endTime);
}
int maValue(float input) {
  return map((int)(input * 100), 0, 100, 0, 255);
}


void setup()
{
  Serial.begin(9600);

  SoftPWMBegin();
  servo1.attach(PETALE_1);
  servo2.attach(PETALE_2);
  servo3.attach(PETALE_3);
  servo4.attach(PETALE_4);
  SoftPWMSet(LED_1, 0);
  SoftPWMSet(LED_2, 0);

  SoftPWMSet(JAMBE_1, 0);
  SoftPWMSet(JAMBE_2, 0);
  servo1.write(179);
  servo2.write(179);
  servo3.write(0);
  servo4.write(0);
  //timer = whispers[0] - 1000;
  //timer = beatStart;
  timer = blablaStart;
  timer = blablaEndGuitarStart;
  timer = 0;
  timerDelta = 0;
  timerDelta1 = 0;
  stepIndex = 0;
  int indexOpening;
}

void walk() {

  if (timer >= steps[0] && timer <= steps[stepsLen - 1]) {
    if (timer < steps[stepIndex + 1]) {
      deltaStep = steps[stepIndex + 1] - steps[stepIndex];
      valLed = maValue(flashLed[calcIndex(timerDelta, 0, deltaStep, flashLedLen)]);
      if (isLeft) {
        SoftPWMSet(JAMBE_1, valLed );
        SoftPWMSet(JAMBE_2, 0);
      } else {
        SoftPWMSet(JAMBE_2, valLed );
        SoftPWMSet(JAMBE_1, 0);
      }
    } else {
      timerDelta = 0;
      timerDelta1 = 0;
      stepIndex++;
      if (isLeft == true) {
        isLeft = false;
      } else {
        isLeft = true;
      }

    }
  } else {
    if (oneShotOff1 == true) {
      oneShotOff1 = false;
      SoftPWMSet(JAMBE_1, 0);
      SoftPWMSet(JAMBE_2, 0);
      SoftPWMSet(LED_1, 0);
      SoftPWMSet(LED_2, 0);
    }

    //Serial.println("go for Bass");
  }
}


void bass() {
  if (timer > startBass && timer <= beatStart) {
    if (setupBassOneShot) {
      setupBassOneShot = false;
      timerDelta = 0;
      timerDelta1 = 0;
      stepIndex = 0;
      valWhisper = 0;
    }
    //WHISPERS
    if (timer > whispers[0] && timer <= bigWhispersEnd[1]) {
      //whispers1
      if (timer > whispers[0] && timer < whispersEnd[0]) {
        Serial.println("whisp1");
        if (setupWhisp1 == true) {
          setupWhisp1 = false;
          timerDelta1 = 0;
        }
        valWhisper =  maValue(ledShortWhisper[calcIndex(timerDelta1, 0, 1000, ledShortWhisperLen)]);

      }
      //whispers2
      if (timer > whispers[1] && timer < whispersEnd[1]) {
        Serial.println("whisp2");
        if (setupWhisp2 == true) {
          setupWhisp2 = false;
          timerDelta1 = 0;
        }
        valWhisper =  maValue(ledShortWhisper[calcIndex(timerDelta1, 0, 1000, ledShortWhisperLen)]);
      }

      //whispers3
      if (timer > bigWhispers[0] && timer < bigWhispersEnd[0]) {
        Serial.println("whisp3");
        if (setupWhisp3 == true) {
          setupWhisp3 = false;
          timerDelta1 = 0;
        }
        valWhisper =  maValue(ledShortWhisper[calcIndex(timerDelta1, 0, bigWhispersEnd[0] - bigWhispers[0], ledShortWhisperLen)]);
      }

      //whispers4
      if (timer > bigWhispers[1] && timer < bigWhispersEnd[1]) {
        Serial.println("whisp4");
        if (setupWhisp4 == true) {
          setupWhisp4 = false;
          timerDelta1 = 0;
        }
        valWhisper =  maValue(ledShortWhisper[calcIndex(timerDelta1, 0, bigWhispersEnd[1] - bigWhispers[1], ledShortWhisperLen)]);
      }
    }
    //BEAT
    if (timerDelta > beatNote) {
      timerDelta = 0;
      if (isLeft == true) {
        isLeft = false;
      } else {
        isLeft = true;
      }
    } else {
      valLed = maValue(flashLed[calcIndex(timerDelta, 0, 100, flashLedLen)]);
      if (isLeft) {
        SoftPWMSet(JAMBE_1, valLed / 2 + valWhisper );
        SoftPWMSet(JAMBE_2, 0);
      } else {
        SoftPWMSet(JAMBE_2, valLed / 2 + valWhisper );
        SoftPWMSet(JAMBE_1, 0);
      }
    }
  } else {
    if (timer > beatStart) {

    }
  }
}
void beatBreak1() {
  if (timer > beatStart && timer < breakStart) {
    if (oneShotOff3 == true) {
      oneShotOff3 = false;
      timerDelta = 0;
      timerDelta1 = 0;
      SoftPWMSet(JAMBE_2, 0);
      SoftPWMSet(JAMBE_1, 0);
    }
    if (timerDelta > beatNote) {
      timerDelta = 0;
      SoftPWMSet(JAMBE_1, 0);
    } else {
      valLed = maValue(flashLed[calcIndex(timerDelta, 0, 100, flashLedLen)]);
      SoftPWMSet(JAMBE_1, valLed);
    }
    if (timerDelta1 > 2 * beatNote) {
      timerDelta1 = 0;
    } else {
      valLed = maValue(flashLed[calcIndex(timerDelta1, 0, 250, flashLedLen)]);
      SoftPWMSet(JAMBE_2, 255 - valLed * 4);
    }
  } else {
    if (oneShotOff4 == true && timer > breakStart) {
      oneShotOff4 = false;
      SoftPWMSet(JAMBE_1, 0);
      SoftPWMSet(JAMBE_2, 0);
    }
  }
}
void break2() {
  if (timer > breakStart && timer < blablaStart) {
    if (oneShotOff5 == true) {
      oneShotOff5 = false;
      timerDelta = 0;
      timerDelta1 = 0;
      SoftPWMSet(JAMBE_2, 0);
      SoftPWMSet(JAMBE_1, 0);
    }
    if (timerDelta > beatBreak) {
      timerDelta = 0;
      SoftPWMSet(JAMBE_1, 0);
      SoftPWMSet(JAMBE_2, 0);
    } else {
      // Serial.println(maValue(break1[calcIndex(timerDelta, 0, beatBreak*2, break1Len)]));
      valLed = maValue(break1[calcIndex(timerDelta, 0, beatBreak, break1Len)]);
      SoftPWMSet(JAMBE_1, valLed );
      SoftPWMSet(JAMBE_2, valLed );
    }
  }
}
void blablateur() {
  if (timer > blablaStart && timer < blablaEndGuitarStart) {
    if (oneShotOff6 == true) {
      oneShotOff6 = false;
      timerDelta = 0;
      timerDelta1 = 0;
      SoftPWMSet(JAMBE_2, 0);
      SoftPWMSet(JAMBE_1, 0);
    }
    float blablaCrescendo = ((float)timer - (float)blablaStart) / ((float)blablaEndGuitarStart - (float)blablaStart);
    Serial.println(blablaCrescendo);
    if (timerDelta > beatBlabla) {
      timerDelta = 0;
      SoftPWMSet(JAMBE_1, 0);
      SoftPWMSet(JAMBE_2, 0);
    } else {
      // Serial.println(maValue(break1[calcIndex(timerDelta, 0, beatBreak*2, break1Len)]));
      valLed = maValue(flashLed[calcIndex(timerDelta, 0, beatBlabla, flashLedLen)]);
      SoftPWMSet(JAMBE_1, (int)(valLed * blablaCrescendo));
      SoftPWMSet(JAMBE_2,  (int)(valLed * blablaCrescendo));
    }
  }
}
void break3() {
  if (timer > blablaEndGuitarStart && timer < blablaStart) {
    if (oneShotOff7 == true) {
      oneShotOff7 = false;
      timerDelta = 0;
      timerDelta1 = 0;
      SoftPWMSet(JAMBE_2, 0);
      SoftPWMSet(JAMBE_1, 0);
    }
    if (timerDelta > beatGuitarBeat) {
      timerDelta = 0;
      SoftPWMSet(JAMBE_1, 0);
      SoftPWMSet(JAMBE_2, 0);
    } else {
      // Serial.println(maValue(break1[calcIndex(timerDelta, 0, beatBreak*2, break1Len)]));
      valLed = maValue(flashLed[calcIndex(timerDelta, 0, beatGuitarBeat, flashLedLen)]);
      SoftPWMSet(JAMBE_1, valLed);
      SoftPWMSet(JAMBE_2, valLed);
    }
  }
}
void break4() {
  if (timer > blablaStart && timer < restartBreak) {
    if (oneShotOff9 == true) {
      oneShotOff9 = false;
      timerDelta = 0;
      SoftPWMSet(JAMBE_2, 0);
      SoftPWMSet(JAMBE_1, 0);
    }
    if (timerDelta > beatGuitarBeat / 2) {
      timerDelta = 0;
      SoftPWMSet(JAMBE_1, 0);
      SoftPWMSet(JAMBE_2, 0);
      if (isLeft == true) {
        isLeft = false;
      } else {
        isLeft = true;
      }
    } else {
      // Serial.println(maValue(break1[calcIndex(timerDelta, 0, beatBreak*2, break1Len)]));
      valLed = maValue((flashLed[calcIndex(timerDelta, 0, 250, flashLedLen)]));
      if (isLeft) {
        SoftPWMSet(JAMBE_1, valLed * 2);
        SoftPWMSet(JAMBE_2, 0);
      } else {
        SoftPWMSet(JAMBE_1, 0);
        SoftPWMSet(JAMBE_2, valLed * 2);
      }
    }
  }
}
void beatBreak2Fn() {
  //measureStart
}
void blabla() {
  //measureStart
}

void openingCoiffe1() {

  if (timer > blablaEndGuitarStart && timer < break2StartEndOpeningCoiff2) {
    if (oneShotOff8 == true) {
      oneShotOff8 = false;
      timerDelta1 = 0;
      indexOpening = 0;
      servo1.write(179);
      servo2.write(179);
      servo3.write(0);
      servo4.write(0);
    }
    int deltaT = (break2StartEndOpeningCoiff2 - blablaEndGuitarStart) / 4;
    if (timerDelta1 > deltaT) {
      timerDelta1 = 0;
      indexOpening = indexOpening + 1;
      //close the coiffe
    } else {
      float crescendo = ((float)timerDelta1 / (float)deltaT);
      //crescendo = crescendo * crescendo;
      int i = (float)(crescendo * 127);
      Serial.println(indexOpening);
      if (indexOpening < 2) {
        servo1.write(map(i, 0, 127, 179 , 179 / 2));              // sets the servo position according to the scaled value
        servo2.write(map(i, 0, 127, 179, 179 / 2));              // sets the servo position according to the scaled value
        servo3.write(map(i, 0, 127, 0, 179 / 2));                // sets the servo position according to the scaled value
        servo4.write(map(i, 0, 127, 0, 179 / 2));                // sets the servo position according to the scaled value
        SoftPWMSet(19, map(i, 0, 127, 0, 255 / 2));               // sets the servo position according to the scaled value
        SoftPWMSet(18, map(i, 0, 127, 0, 255 / 2));
      } else if (indexOpening <= 4) {
        servo1.write(map(i, 0, 127, 179 * .75, 0));              // sets the servo position according to the scaled value
        servo2.write(map(i, 0, 127, 179 * .75, 0));              // sets the servo position according to the scaled value
        servo3.write(map(i, 0, 127, 0, 179 * .75));              // sets the servo position according to the scaled value
        servo4.write(map(i, 0, 127, 0, 179 * .75));              // sets the servo position according to the scaled value
        SoftPWMSet(19, map(i, 0, 127, 0, 255));               // sets the servo position according to the scaled value
        SoftPWMSet(18, map(i, 0, 127, 0, 255));
      }
      //var valueCoiffe= (int)(crescendo*255);
      //open the coiffe
    }
  } else {
    servo1.write(179);                // sets the servo position according to the scaled value
    servo2.write(179);                // sets the servo position according to the scaled value
    servo3.write(0);                // sets the servo position according to the scaled value
    servo4.write(0);                // sets the servo position according to the scaled value
    SoftPWMSet(19, map(0, 0, 127, 0, 255));               // sets the servo position according to the scaled value
    SoftPWMSet(18, map(0, 0, 127, 0, 255));
  }
}
void break5() {
  if (timer > restartBreak && timer < startVibrato1 ) {
    if (oneShotOff10 == true) {
      oneShotOff10 = false;
      timerDelta = 0;
      SoftPWMSet(JAMBE_2, 0);
      SoftPWMSet(JAMBE_1, 0);
    }
    if (timerDelta > beatGuitarBeat / 4) {
      timerDelta = 0;
      SoftPWMSet(JAMBE_1, 0);
      SoftPWMSet(JAMBE_2, 0);
      if (isLeft == true) {
        isLeft = false;
      } else {
        isLeft = true;
      }
    } else {
      // Serial.println(maValue(break1[calcIndex(timerDelta, 0, beatBreak*2, break1Len)]));
      valLed = maValue(break1[calcIndex(timerDelta, 0, beatGuitarBeat / 4, break1Len)]);
      if (isLeft == true) {
        SoftPWMSet(JAMBE_1, valLed * 2);
        SoftPWMSet(JAMBE_2, 0);
      } else {
        SoftPWMSet(JAMBE_1, 0);
        SoftPWMSet(JAMBE_2, valLed * 2);
      }

    }
  }
}
void outtro() {
  if (timer > startVibrato1 && timer < endTrax ) {
    decrescendo = 1.00 - ((float)timer - (float)startVibrato1) / ((float)endTrax - (float)startVibrato1);
    Serial.println(decrescendo);
    if (oneShotOff11 == true) {
      oneShotOff11 = false;
      timerDelta = 0;
      SoftPWMSet(JAMBE_2, 0);
      SoftPWMSet(JAMBE_1, 0);
    }
    if (timerDelta > beatGuitarBeat / 16) {
      timerDelta = 0;
      SoftPWMSet(JAMBE_1, 0);
      SoftPWMSet(JAMBE_2, 0);
      if (isLeft == true) {
        isLeft = false;
      } else {
        isLeft = true;
      }
    } else {
      // Serial.println(maValue(break1[calcIndex(timerDelta, 0, beatBreak*2, break1Len)]));
      valLed = maValue(break1[calcIndex(timerDelta, 0, beatGuitarBeat / 16, break1Len)]);
      if (isLeft == true) {
        SoftPWMSet(JAMBE_1, valLed  * decrescendo);
        SoftPWMSet(JAMBE_2, 0);
      } else {
        SoftPWMSet(JAMBE_1, 0);
        SoftPWMSet(JAMBE_2, valLed * decrescendo);
      }

    }
  }

}
void loop()
{
  walk();
  bass();
  beatBreak1();
  break2();
  blablateur();
  break3();
  break4();
  openingCoiffe1();
  break5();
  outtro();
}
