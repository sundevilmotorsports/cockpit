#include "max31855.h"

float getThermocoupleTemperature(int data) {
    int thermocoupleData = (data >> 18);
    int number = thermocoupleData >> 2;
    float decimal = 0.25 * (thermocoupleData & 0x3);
    return ((float) number) + decimal;
}