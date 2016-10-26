#include "command.h"

void evaluateCommand(Command* commands, String cmnd)
{

  struct Command *scan;
  for (scan = commands;  scan -> function; scan++)
  {
    if ( cmnd.substring(0, scan -> name.length()) == scan->name )
    {
      scan -> function( cmnd.substring(scan -> name.length() + 1) );
      return;
    }
  }

  Serial.print(F("Command - ERR - Unknown command: "));   
  Serial.println(cmnd);
}