#include <DRV8838MotorShield.h>

//pin definitions are in the library.
DRV8838MotorShield motors(7, 8, 9, 10, 11, 12);
int LightPin_1 = 0;
int LightPin_2 = 1;
int speakerPin = 6;

void setup() {
  motors.init();
  //motors.flipM1();  //flip direction. e.g. if wired opposite, or whatever
  //motors.flipM2();
  Serial.begin(9600);
  pinMode(LightPin_1, INPUT);
  pinMode(LightPin_2, INPUT);
  pinMode(speakerPin, OUTPUT);
  motors.setSpeeds(100);
  delay(1000);
}

void loop() {
  int numReads = 15;
  int iBrightness1, iBrightness2, newBrightness, lastBrightness;
  iBrightness1 = 0;
  iBrightness2 = 0;
  int iFastSpeed = 120;
  int iSlowSpeed = 60;
  
  for (int i = 0; i < numReads; i++)
    {
      iBrightness1 += analogRead(LightPin_1)/numReads;
      iBrightness2 += analogRead(LightPin_2)/numReads;
    }
  newBrightness = iBrightness1 + iBrightness2;
  if (newBrightness < lastBrightness)
  {
    motors.setSpeeds(-iSlowSpeed, iSlowSpeed);
    delay(500);
  }
  lastBrightness = newBrightness;
  int freq = mapBuzzer(iBrightness1, iBrightness2);
  tone(speakerPin, freq);
  Serial.print("\nBrightness 1 = ");
  Serial.print(iBrightness1);
  Serial.print("; Birghtness 2 = ");
  Serial.print(iBrightness2);
  Serial.print(";  freq = ");
  Serial.print(freq);
  if ((iBrightness1 > 600) && (iBrightness2 >600))
  {
    motors.setSpeeds(0);
  }
  else if ((iBrightness1 > 300) || (iBrightness2 > 300))
  {
    if (iBrightness1 - 25 > iBrightness2)
    {
      motors.setSpeeds(iSlowSpeed, 20);
    }
    else if (iBrightness2 - 25 > iBrightness1)
    {
      motors.setSpeeds(20, iSlowSpeed);
    }
    else
    {
      motors.setSpeeds(iSlowSpeed);
    }
  }
  else
  {
    if (iBrightness1 - 15 > iBrightness2)
    {
      motors.setSpeeds(iFastSpeed,50);
    }
    else if (iBrightness2 - 15 > iBrightness1)
    {
      motors.setSpeeds(50, iFastSpeed);
    }
    else
    {
      motors.setSpeeds(iFastSpeed);
    }
  }
    //  motors.sleep();
    delay(20);
  }

int mapBuzzer(int iLight1, int iLight2)
{
  int iLight = (iLight1 + iLight2)/2;
  Serial.print("light = ");
  Serial.print(iLight);
  return iLight*5 + 100;
}

