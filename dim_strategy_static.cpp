#include "dim_strategy_static.h"

DimStrategyStatic::DimStrategyStatic(int dimmer)
{
  staticDimmer = dimmer;
}

int DimStrategyStatic::nextDimmer()
{
  return staticDimmer;
}