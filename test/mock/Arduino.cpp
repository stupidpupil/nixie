#include "Arduino.h"

unsigned long saved_millis = 0;

unsigned long millis() {
  return saved_millis;
}

void set_millis(unsigned long new_millis){
  saved_millis = new_millis;
}