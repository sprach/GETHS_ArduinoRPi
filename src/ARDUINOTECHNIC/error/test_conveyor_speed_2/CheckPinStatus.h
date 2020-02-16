#ifndef __CheckPinStatus__
#define __CheckPinStatus__

#include <inttypes.h>
#include <Arduino.h>

class CheckPinStatus {
public:
    CheckPinStatus(uint8_t pinNo, void (*pf)(int), int pinStatus);
    void CheckPinStatus::CheckPin(void);
private:
    uint8_t __pinNo;
    void (*__pf)(int);
    int __pinStatus;
    volatile int __lastPinStatus;
};
#endif  // __CheckPinStatus__
