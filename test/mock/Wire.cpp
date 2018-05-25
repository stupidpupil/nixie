#include "Wire.h"

WireMockTransmission LatestTransmission;

MockWire::MockWire(){
}

void MockWire::beginTransmission(byte i2c_address)
{
  LatestTransmission.i2c_address = i2c_address;
  LatestTransmission.content.clear();
  LatestTransmission.ended = false;
}

void MockWire::write(byte aByte)
{
  LatestTransmission.content.push_back(aByte);
}

byte MockWire::endTransmission()
{
  LatestTransmission.ended = true;
  return 0;
}

MockWire Wire;
