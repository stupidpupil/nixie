#ifndef SMART_NIXIE_H
#define SMART_NIXIE_H

#include "Arduino.h"
#include <Wire.h>

#define SMART_NIXIE_REGISTER_CHARACTER 0x00
#define SMART_NIXIE_BLANK_CHARACTER 0x10

#define SMART_NIXIE_REGISTER_DIMMER 0x0B

/**
 * Note that these are _not_ in the order of the cathode pin on the Soviet datasheets
 * for the tubes themselves, but correspond to the index sent to the SmartNixie.
 * (e.g. 0123456789 not 0987654321)
 */
#define SMART_NIXIE_IN12_CHARS  "0123456789"
#define SMART_NIXIE_IN15A_CHARS "un%PkMm+-P"
#define SMART_NIXIE_IN15B_CHARS "WAO SVhH F"
#define SMART_NIXIE_IN15V_CHARS "Vm~PKMA+-O"

struct SmartNixieState{
  char character;
  byte dimmer;
};

/**
 * A class representing a Taylor Electronics 1356/1328/1326/... SmartNixie.
 * http://www.tayloredge.com/storefront/SmartNixie/DataSheets/Datasheet_SmartNixie.pdf
 */
class SmartNixie
{
  public:

    /**
     *
     * Note that the SmartNixie datasheet's /Base Addresses/ need to be 
     * _right_ shifted to produce the 7-bit address expected by the 
     * Arduino's Wire library (and this constructor).
     * e.g. 0x10 << 1 = 0x08
     *  
     * @param i2c_address The 7-bit I2C address for this SmartNixie.
     * @param characters The characters that this SmartNixie's tubes can display. Defaults to the IN12's set.
     *
     */
    SmartNixie(byte i2c_address, String characters = SMART_NIXIE_IN12_CHARS);

    /**
     * Check if this SmartNixie is responding over I2C.
     */

    bool exists();


    /**
     * Check if this SmartNixie can display a particular character.
     *
     * @param character
     *
     */
    bool hasCharacter(char character);
    
    /**
     * Tell the SmartNixie to display a particular character.
     *
     * 
     * @param character
     *
     */
    bool setCharacter(char character);

    /**
     * Tell the SmartNixie to dim the tube (using pulse-width modulation).
     *
     * @param dimmer
     *
     */
    bool setDimmer(int dimmer);    

    void saveState();
    bool restoreState();

  private:
    byte _i2c_address;
    String _characters;
    SmartNixieState _currentState;
    SmartNixieState _savedState;
    bool setCharReg(byte value);

};

#endif /* SMART_NIXIE_H */
