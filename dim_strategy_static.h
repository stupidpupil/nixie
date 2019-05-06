#ifndef DIM_STRATEGY_STATIC_H
#define DIM_STRATEGY_STATIC_H

#include "dim_strategy.h"

class DimStrategyStatic : public DimStrategy
{
  public:
    DimStrategyStatic(int dimmer);
    virtual ~DimStrategyStatic() = default;
    int nextDimmer();

  private:
    int staticDimmer;
};


#endif /* DIM_STRATEGY_STATIC_H */
