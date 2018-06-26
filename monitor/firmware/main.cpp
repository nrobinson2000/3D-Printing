#include "Particle.h"

SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);

#define PRINTBED D4
#define CONFIRMBTN A0
#define CONFIRMLED A5
#define PUBLISHLED D7

bool confirmState = false;

void setup() // Put setup code here to run once
{
        pinMode(PRINTBED, INPUT_PULLUP);
        pinMode(CONFIRMBTN, INPUT_PULLUP);

        pinMode(PUBLISHLED, OUTPUT);
        pinMode(CONFIRMLED, OUTPUT);

        Serial.begin(115200);

        Particle.connect();
}

void loop() // Put code here to loop forever
{
        digitalWrite(CONFIRMLED, confirmState);

        if (digitalRead(CONFIRMBTN) == LOW)
        {
                confirmState = !confirmState;
                delay(250);
        }

        if (digitalRead(PRINTBED) == LOW && confirmState == true)
        {
          bool tempState = true;

                if (Particle.connected() && confirmState == true)
                {
                        Serial.print("Button is: ");
                        Serial.println(digitalRead(PRINTBED));

                        if (digitalRead(PRINTBED) == LOW)
                        {
                          digitalWrite(PUBLISHLED, HIGH);
                          Serial.println("Publishing...");
                          Particle.publish("print-done", "good", PRIVATE);
                          delay(3000);
                          tempState = false;
                        }
                }
                digitalWrite(PUBLISHLED, LOW);
                confirmState = tempState;
        }
}
