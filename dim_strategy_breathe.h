#ifndef DIM_STRATEGY_BREATHE_H
#define DIM_STRATEGY_BREATHE_H

#include "Arduino.h"
#include "dim_strategy.h"

class DimStrategyBreathe : public DimStrategy
{
  public:
    DimStrategyBreathe(byte currentDimmer, int minD = 0, int maxD = 100);
    int nextDimmer();

  private:
    short offsetMillis;
    int minDimmer;
    int dimmerRange;
};


#endif /* DIM_STRATEGY_BREATHE_H */
