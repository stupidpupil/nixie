#ifndef DIM_STRATEGY_H
#define DIM_STRATEGY_H

class DimStrategy
{
  public:
    virtual int nextDimmer() = 0;
    virtual ~DimStrategy() {};

};

#endif /* DIM_STRATEGY_H */
