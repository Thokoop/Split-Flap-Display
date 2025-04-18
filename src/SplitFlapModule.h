#pragma once

#include <Arduino.h>
#include <Wire.h>

class SplitFlapModule {
  public:
    // Constructor declarationS
    SplitFlapModule(); // default constructor required to allocate memory for
    // SplitFlapDisplay class
    SplitFlapModule(uint8_t I2Caddress, int stepsPerFullRotation, int stepOffset, int magnetPos, int charSetSize);

    void init();

    void step(bool updatePosition = true);                   // step motor
    void stop();                                             // write all motor input pins to low
    void start();                                            // re-energize coils to last position, not stepping motor

    int getMagnetPosition() const { return magnetPosition; } // position where magnet is detected
    int getCharPosition(char inputChar);                     // get integer position given single character
    int getPosition() const { return position; }             // get integer position
    int getCharsetSize() const { return numChars; }          // getter for charset size

    bool readHallEffectSensor();                             // return the value read by the hall effect
    // sensor
    void magnetDetected() {
        position = magnetPosition;
    } // update position to magnetposition, called when magnet is detected

    bool getHasErrored() const { return hasErrored; }

  private:
    uint8_t address;                // i2c address of module
    int position;                   // character drum position
    int stepNumber;                 // current position in the stepping order, to make motor move
    int stepsPerRot;                // number of steps per rotation
    bool hasErrored = false;        // flag to indicate if an error has occurred

    void writeIO(uint16_t data);    // write to motor in pins

    int magnetPosition;             // altered by offsets
    static const int motorPins[];   // Array of motor pins
    static const int HallEffectPIN; // Hall Effect Sensor Pin (On PCF8575)

    const char *chars;              // pointer to active character set
    int charPositions[48];          // support up to 48 characters
    int numChars;                   // current number of characters
    int charSetSize;

    static const char StandardChars[37];
    static const char ExtendedChars[48];
};

// //PINs on the PCF8575 Board
// #define P00  	0
// #define P01  	1
// #define P02  	2
// #define P03  	3
// #define P04  	4
// #define P05  	5
// #define P06  	6
// #define P07  	7
// #define P10  	8
// #define P11  	9
// #define P12  	10
// #define P13  	11
// #define P14  	12
// #define P15  	13
// #define P16  	14
// #define P17  	15
