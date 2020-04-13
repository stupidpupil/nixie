#include <Wire.h>
#include "uptime.h"
#include "hvps.h"
#include "dim_strategy.h"
#include "dim_strategy_static.h"
#include "dim_strategy_breathe.h"
#include "smart_nixie.h"
#include "memory_free.h"
#include "command.h"

HVPS hvps(5);
SmartNixie nixies[] = {
  SmartNixie(0x08),
  SmartNixie(0x09),
  SmartNixie(0x0a, SMART_NIXIE_IN15A_CHARS)
};

DimStrategy* dimStrategy = new DimStrategyStatic(0);
int currentDimmer = 0;

int numberOfNixies()
{
  return (sizeof(nixies)/sizeof(SmartNixie));
}

void command_STATUS(String arguments)
{
  (void) arguments; //Suppress unused parameter warnings

  Serial.print(F("Uptime: "));
  Serial.println(uptimeSeconds());

  Serial.print(F("Nixies: "));
  Serial.println(numberOfNixies());

  for (int i = 0; i < numberOfNixies(); ++i)
  {
    if(!nixies[i].exists())
    {
      Serial.print(F("Nixie "));
      Serial.print(i+1);
      Serial.print(" is missing");
      Serial.println();
    }
  }

  Serial.print(F("HVPS is on? "));
  Serial.println(hvps.isOn());

  Serial.print(F("Free memory: "));
  Serial.println(freeMemory());


}

void command_SET(String arguments)
{
  if ( numberOfNixies() != (int) arguments.length() ) {
    Serial.print(F("Main - ERR - SET arg wrong length: "));
    Serial.println(arguments);
    return;
  }

  // Check if we can set all the SmartNixies
  // and otherwise set none at all
  for (int i = 0; i < numberOfNixies(); ++i) {
    if ( !nixies[i].hasCharacter(arguments.charAt(i)) )
    {
      Serial.print(F("Main - ERR - Char not found: "));
      Serial.println(arguments.charAt(i));
      return;   
    }
  }

  for (int i = 0; i < numberOfNixies(); ++i)
    {nixies[i].setCharacter(arguments.charAt(i));}

}

void command_DIM(String arguments)
{

  if (arguments == "BREATHE")
  {
    delete dimStrategy;
    dimStrategy = new DimStrategyBreathe(currentDimmer, 10, 35);
    return;
  }

  int targetDim = (int) arguments.toInt();

  if (targetDim < 1 || targetDim > 100)
  {
    Serial.print(F("Main - ERR - Invalid DIM arg: "));
    Serial.println(arguments);
    return;
  }

  delete dimStrategy;
  dimStrategy = new DimStrategyStatic(targetDim);
}

void setDimmerForAll(int targetDim)
{
  if (targetDim == currentDimmer)
    {return;}

  for (int i = 0; i < numberOfNixies(); ++i)
    {nixies[i].setDimmer(targetDim);}  

  currentDimmer = targetDim;
}

void command_HVPS(String arguments)
{
  if (arguments == "OFF"){
    hvps.off();
    return;
  }

  if (arguments == "ON")
  {
    hvps.on();
    return;
  }

  Serial.print(F("Main - ERR - Unknown HVPS arg: "));   
  Serial.println(arguments);
}



struct Command commands[] = {
  {"SET", command_SET},
  {"DIM", command_DIM},
  {"HVPS", command_HVPS},
  {"STATUS", command_STATUS}
};

/*
  Main Arduino functions
*/

unsigned long idleSince = 0;
unsigned long lastRanAntidote = 0;

void resetIdle()
{
  idleSince = uptimeSeconds();
}

void antidote()
{
  for (int i = 0; i < numberOfNixies(); ++i)
    {nixies[i].saveState();}

  //evaluateCommand("DIM 100");

  Serial.println("Main - INFO - Running antidote");

  for (int i = 0; i < numberOfNixies(); ++i)
    {nixies[i].restoreState();}

  lastRanAntidote = uptimeSeconds();
}

void setup()
{
  Serial.begin(9600);
  while (!Serial) {}

  Wire.begin();
  Serial.println(F("Main - INFO - Ready"));
  resetIdle();
}

void loop()
{
  String command;

  delay(25);

  /*if ( hvps.isOn() )
  {
    if ( ((uptimeSeconds() - idleSince) > 60) && ((uptimeSeconds() - lastRanAntidote) > 180) )
    {
      antidote();
    }

    if ( (uptimeSeconds() - lastRanAntidote) > 600 )
    {
      antidote();
    }
  }*/

  while(Serial.available() > 0) {
    command = Serial.readStringUntil('\n');
    evaluateCommand(commands, command);
    resetIdle();
  }

  setDimmerForAll(dimStrategy->nextDimmer());

}

