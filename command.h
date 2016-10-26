#ifndef COMMAND_H
#define COMMAND_H

#include "Arduino.h"

struct Command {
  String name;
  void (*function)(String);
};

void evaluateCommand(Command* commands, String cmnd);

#endif /* COMMAND_H */
