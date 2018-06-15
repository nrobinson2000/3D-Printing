#include "Particle.h"

SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);

#define PRINTER D4
#define CONFIRM A0

/* inline void softDelay(uint32_t msDelay)
{
        for (uint32_t ms = millis(); millis() - ms < msDelay; Particle.process());
} */

bool confirmState = false;

void setup() // Put setup code here to run once
{

        pinMode(PRINTER, INPUT_PULLUP);
        pinMode(CONFIRM, INPUT_PULLUP);

        pinMode(D7, OUTPUT);
        pinMode(A5, OUTPUT);

        Serial.begin(115200);

        Particle.connect();
}

void loop() // Put code here to loop forever
{
        digitalWrite(A5, confirmState);

        if (digitalRead(CONFIRM) == LOW)
        {
                confirmState = !confirmState;
                delay(250);
        }


        if (digitalRead(PRINTER) == LOW && confirmState == true)
        {
          bool tempState = true;

                if (Particle.connected() && confirmState == true)
                {
                        Serial.print("Button is: ");
                        Serial.println(digitalRead(PRINTER));

                        if (digitalRead(PRINTER) == LOW)
                        {
                          digitalWrite(D7, HIGH);
                          Serial.println("Publishing...");
                          Particle.publish("print-done", "good", PRIVATE);
                          delay(3000);
                          tempState = false;
                        }


                }
                digitalWrite(D7, LOW);
                confirmState = tempState;
        }

/*

        if (printReading == LOW && printState == HIGH)
        {
                printState = LOW;
                Serial.print("ON: ");
                Serial.println(printState);

                if (Particle.connected() && confirmState == true)
                {
                        Particle.publish("print_finished", "good", PRIVATE);
                        confirmState = false;
                }

                delay(3000);
        }
        else if (printReading == HIGH && printState == LOW)
        {
                printState = HIGH;
                Serial.print("OFF: ");
                Serial.println(printState);
                delay(100);
        }

 */
}
