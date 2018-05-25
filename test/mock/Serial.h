#pragma once

#include <string>


class MockSerial
{
public:
  MockSerial();

  void print(std::string aString);
  void print(char aChar);
  void print(int aInt);

  void println(std::string aString);
  void println(char aChar);
  void println(int aInt);

};

extern MockSerial Serial;