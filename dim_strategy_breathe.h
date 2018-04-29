#ifndef DIM_STRATEGY_BREATHE_H
#define DIM_STRATEGY_BREATHE_H

#include "Arduino.h"
#include "dim_strategy.h"

class DimStrategyBreathe : public DimStrategy
{
  public:
    DimStrategyBreathe(byte currentDimmer);
    int nextDimmer();

  private:
    short offsetMillis;
};


#endif /* DIM_STRATEGY_BREATHE_H */
