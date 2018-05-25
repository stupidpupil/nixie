#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_DISABLE_MATCHERS
#include "catch/catch.hpp"

#include <cstdio>
#include <unistd.h>
#include <stdlib.h>

#include "Arduino.h"
#include "../dim_strategy.h"
#include "../dim_strategy_breathe.h"

TEST_CASE("DimStrategyBreathe respects current dimmer value", "[DimStrategyBreathe]") {

  for (int i = 0; i < 101; ++i)
  {
    DimStrategy* dimStrategy;
    short diff;
    set_millis(0);
    dimStrategy = new DimStrategyBreathe((byte) i);
    set_millis(10);

    diff = i - (dimStrategy->nextDimmer());

    REQUIRE( abs(diff) < 3 );

    delete dimStrategy;
  }
}

TEST_CASE("DimStrategyBreathe has a period of about 5 seconds", "[DimStrategyBreathe]") {

  set_millis(0);
  DimStrategy* dimStrategy = new DimStrategyBreathe((byte) 0);
  set_millis(2500);
  REQUIRE (dimStrategy->nextDimmer() > 96);
  set_millis(5000);
  REQUIRE (dimStrategy->nextDimmer() < 4);
  delete dimStrategy;
}