#include "dim_strategy_breathe.h"

/* Each entry is a time, in millis, when the dimmer should change. */
/* (The very first entry marks '0' at T0.)
/* The next 125 changes are increases and the following 125 changes are decreases */
const short lookupTable[] = {
  0,731,996,1082,1143,1184,1216,1252,1270,1299,1321,1342,1364,1380,1398,1415,1429,1449,1459,1472,1488,1502,1515,1527,1538,1550,1563,1573,1581,1592,1604,1612,1621,1630,1642,1650,1658,1666,1676,1684,1692,1700,1708,1717,1725,1731,1738,1746,1755,1763,1771,1778,1785,1792,1799,1806,1813,1821,1829,1836,1843,1849,1856,1863,1871,1877,1883,1890,1896,1904,1911,1917,1923,1929,1936,1944,1951,1957,1963,1969,1976,1983,1990,1997,2003,2009,2015,2023,2030,2037,2044,2051,2058,2065,2072,2079,2086,2094,2103,2110,2117,2124,2131,2141,2149,2156,2163,2173,2184,2192,2199,2207,2219,2230,2239,2248,2262,2273,2285,2302,2314,2330,2348,2377,2394,2441,2498,2541,2575,2610,2640,2658,2682,2697,2720,2734,2750,2768,2780,2802,2813,2824,2842,2855,2867,2879,2891,2905,2919,2929,2939,2953,2964,2973,2984,2997,3007,3016,3028,3040,3048,3057,3070,3080,3089,3098,3110,3120,3131,3140,3150,3160,3171,3183,3193,3201,3210,3222,3233,3241,3250,3262,3272,3281,3289,3302,3312,3321,3329,3341,3353,3362,3371,3385,3397,3406,3418,3429,3440,3451,3463,3472,3483,3497,3508,3517,3530,3544,3554,3564,3579,3591,3603,3617,3628,3640,3655,3671,3685,3698,3711,3731,3742,3756,3774,3788,3807,3820,3842,3859,3874,3898,3915,3938,3966,3984,4009,4039,4057,4091,4125,4159,4197,4237,4279,4332,4401,4444,4529,4644,4909
};
const short lookupTableMax = 125;

const short period = 4983; // Selected to minimise millis() rollover impact

DimStrategyBreathe::DimStrategyBreathe(byte currentDimmer)
{
  if (currentDimmer > 100)
    {currentDimmer = 100;}


  // Try to offset the period so that we start at roughly the current brightness
  offsetMillis = lookupTable[(currentDimmer*lookupTableMax/100)];
  short modPeriod = millis() % period;
  offsetMillis = offsetMillis - modPeriod;
}


int DimStrategyBreathe::nextDimmer()
{

  short modPeriod = millis() % period;

  modPeriod = modPeriod + offsetMillis;
  if (modPeriod < 0)
    {modPeriod = period + modPeriod;}


  byte dim = 0;

  while (dim < (lookupTableMax*2) and lookupTable[dim+1] <= modPeriod)
    {dim += 1;}


  if (dim > lookupTableMax)
    {dim = (lookupTableMax*2)-dim;}

  
  return (dim*100/lookupTableMax);

}
