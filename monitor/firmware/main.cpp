#include "Particle.h"

SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);

#define PRINTER D0
#define CONFIRM A0

inline void softDelay(uint32_t msDelay)
{
  for (uint32_t ms = millis(); millis() - ms < msDelay; Particle.process());
}

bool printState = LOW;
bool confirmState = LOW;

void setup() // Put setup code here to run once
{

pinMode(PRINTER, INPUT_PULLUP);
pinMode(CONFIRM, INPUT_PULLUP);

pinMode(D7, OUTPUT);
pinMode(D6, OUTPUT);

Serial.begin(115200);

Particle.connect();
}

void loop() // Put code here to loop forever
{

bool printReading = !digitalRead(PRINTER);
bool confirmReading = !digitalRead(CONFIRM);

digitalWrite(D7, !digitalRead(PRINTER));

if (confirmReading == HIGH)
{
  confirmState = !confirmState;
  digitalWrite(D6, confirmState);
  softDelay(250);
}

if (printReading == HIGH && printState == LOW)
{
  printState = HIGH;
  Serial.print("ON: ");
  Serial.println(printState);

  if (Particle.connected() && confirmState)
  {
    Particle.publish("print_finished", PRIVATE);
  }

  softDelay(100);
}
else if (printReading == LOW && printState == HIGH)
{
  printState = LOW;
  Serial.print("OFF: ");
  Serial.println(printState);
  softDelay(100);
}

}
