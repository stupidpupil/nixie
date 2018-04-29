#include "hvps.h"

HVPS::HVPS(byte enablePin)
{
  _enablePin = enablePin;
  pinMode(_enablePin, OUTPUT);
  digitalWrite(_enablePin, LOW);
  _earliestPowerOff = uptimeSeconds();
}

void HVPS::on()
{
  Serial.println(F("HVPS - INFO - On"));
  pinMode(_enablePin, OUTPUT);
  digitalWrite(_enablePin, HIGH);
  _earliestPowerOff = uptimeSeconds() + HVPS_MINIMUM_POWER_ON_SECONDS;
}

void HVPS::off()
{
  while ((long)( uptimeSeconds() - _earliestPowerOff ) < 0)
  {
    Serial.println(F("HVPS - WARNING - Delaying power off"));
    // Repeating this message has the (useful) side-effect of flashing the Serial-out LED
    delay(250);
  }

  Serial.println(F("HVPS - INFO - Off"));
  digitalWrite(_enablePin, LOW);
}

bool HVPS::isOn()
{
  return (digitalRead(_enablePin) == HIGH);
}

float HVPS::rAdjustKOhmsForVOut(int vOut)
{
  if (vOut <= 152) return 1518.0;
  if (vOut >= 200) return 0.0;

  float vFloat = (float) vOut;
  return ( (-1.24/(0.124 - ((vFloat-1.24)/1208)) ) -30.1);
}
