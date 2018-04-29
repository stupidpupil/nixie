#include "smart_nixie.h"

SmartNixie::SmartNixie(byte i2c_address, String characters)
{
  _i2c_address = i2c_address;
  _characters = characters; //characters shouldn't be longer than 12 (and won't be longer than 9)
  _currentState = (SmartNixieState) {' ', 100};
  _savedState = _currentState;
}

bool SmartNixie::exists()
{
  Wire.beginTransmission(_i2c_address);
  byte error = Wire.endTransmission();
  return (error == 0);
}


bool SmartNixie::setDimmer(int dimmer)
{
  if((dimmer < 0) || (dimmer > 100)) return false;

  Serial.print(F("SmrtNxie - INFO - Set dimmer to "));
  Serial.println(dimmer);

  _currentState.dimmer = dimmer;
  Wire.beginTransmission(_i2c_address);
  Wire.write(byte(SMART_NIXIE_REGISTER_DIMMER));
  Wire.write(byte(dimmer));
  byte error = Wire.endTransmission();
  return (error == 0);
}

bool SmartNixie::setCharReg(byte value)
{

  if( (value > _characters.length()) && (value != SMART_NIXIE_BLANK_CHARACTER)) return false;
  Wire.beginTransmission(_i2c_address);
  Wire.write(byte(SMART_NIXIE_REGISTER_CHARACTER));
  Wire.write(byte(value));
  byte error = Wire.endTransmission();

  return (error == 0);
}

bool SmartNixie::setCharacter(char character)
{
  int charRegValue = (character == ' ') ? SMART_NIXIE_BLANK_CHARACTER : _characters.indexOf(character);

  if( charRegValue < 0 ) return false;

  Serial.print(F("SmrtNxie - INFO - Set char to "));
  Serial.println(character);

  _currentState.character = character;
  return setCharReg((byte) charRegValue);
}

bool SmartNixie::hasCharacter(char character)
{
  return (character == ' ') ? SMART_NIXIE_BLANK_CHARACTER : (_characters.indexOf(character) > -1);
}

void SmartNixie::saveState()
{
  _savedState = _currentState;
}

bool SmartNixie::restoreState()
{
  return ( (setCharacter(_savedState.character)) && (setDimmer(_savedState.dimmer)) );
}
