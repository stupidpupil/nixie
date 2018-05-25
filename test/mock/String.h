#pragma once

#include <string>


class String : public std::string
{
public:
  size_t indexOf(char character);

  String() : std::string() {} 
  String(const char *cs) : std::string(cs) {} 
  String(const String &value);

};

String F(String aString);
