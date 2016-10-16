#ifndef HVPS_H
#define HVPS_H

#include "Arduino.h"
#include "uptime.h"

// "Do not switch module on and off rapidly for extended periods,
//  minimum on time should be 10 seconds."
#define HVPS_MINIMUM_POWER_ON_SECONDS 10

/**
 * A class representing a Taylor Electronics 1363/1364-series High Voltage Power Supply.
 * http://www.tayloredge.com/storefront/SmartNixie/DataSheets/Datasheet_1363-1364.pdf
 *
 * CAUTION - The output of a HVPS poses an electrical shock hazard
 */

class HVPS
{
  public:
    HVPS(byte enablePin);

    /**
     * Switch the HVPS on.
     */
    void on();

    /**
     * Try to switch the HVPS off. 
     * WARNING: It can take up to HVPS_MINIMUM_POWER_ON_SECONDS to actually switch the supply off.
     */
    void off();

    bool isOn();


    /**
     * Calculate the rAdjust value required for a given output voltage (assuming that vAdjust is 0V).
     * (Works in the range 152V to 200V.)
     */    
    float rAdjustKOhmsForVOut(int vOut);
  private:
    byte _enablePin;
    unsigned long _earliestPowerOff;
};

#endif /* HVPS_H */
