#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_DISABLE_MATCHERS
#include "catch/catch.hpp"

#include <cstdio>
#include <unistd.h>
#include <stdlib.h>

#include "Arduino.h"
#include "../smart_nixie.h"


TEST_CASE("SmartNixie exists", "[SmartNixie]") {

  SmartNixie* nixie;
  nixie = new SmartNixie((byte) 0x09);
  REQUIRE( (nixie->exists()) == true );
  REQUIRE( (LatestTransmission.i2c_address) == 0x09 );
  REQUIRE( (LatestTransmission.ended) == true );

}

TEST_CASE("SmartNixie set character", "[SmartNixie]") {

  SmartNixie* nixie;
  nixie = new SmartNixie((byte) 0x09);
  nixie->setCharacter('0');

  REQUIRE( (LatestTransmission.i2c_address) == 0x09 );
  REQUIRE( (LatestTransmission.content[0]) == 0x00 );
  REQUIRE( (LatestTransmission.content[1]) == 0x00 );
  REQUIRE( (LatestTransmission.ended) == true );

}

TEST_CASE("SmartNixie set blank", "[SmartNixie]") {

  SmartNixie* nixie;
  nixie = new SmartNixie((byte) 0x09);
  nixie->setCharacter(' ');

  REQUIRE( (LatestTransmission.i2c_address) == 0x09 );
  REQUIRE( (LatestTransmission.content[0]) == 0x00 );
  REQUIRE( (LatestTransmission.content[1]) == 0x10 );
  REQUIRE( (LatestTransmission.ended) == true );

}