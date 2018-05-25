#pragma once

#include <vector>
#include "Arduino.h"

struct WireMockTransmission
{
  byte i2c_address;
  std::vector<byte> content;
  bool ended;
};

class MockWire
{
public:
  MockWire();

  void beginTransmission(byte i2c_address);
  void write(byte aByte);
  byte endTransmission();

};

extern MockWire Wire;
extern WireMockTransmission LatestTransmission;