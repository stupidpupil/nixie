#include "MockString.h"

String::String(const String &value){
  *this = value;
}


size_t String::indexOf(char character){
  return find_first_of(character);
}

String F(String aString){
  return aString;
}