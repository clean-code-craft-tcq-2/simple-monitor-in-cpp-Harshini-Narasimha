#include <iostream>
using namespace std;

#define LOWER_TEMPERATURE_LIMIT 0
#define UPPER_TEMPERATURE_LIMIT 45
#define LOWER_CHARGE_LIMIT 20
#define UPPER_CHARGE_LIMIT 80
#define CHARGE_RATE 0.8

void printOnConsole(string stringToPrint){
    cout << stringToPrint;
}

bool isTemperatureOutOfRange(float temperature) {
    printOnConsole("Temperature out of range!\n");
    return (temperature < LOWER_TEMPERATURE_LIMIT || temperature > UPPER_TEMPERATURE_LIMIT);
}

bool isStateOfChargeOutOfRange(float soc) {
    printOnConsole("State of Charge out of range!\n");
    return (soc < LOWER_CHARGE_LIMIT || soc > UPPER_CHARGE_LIMIT);
}

bool isChargeRateOutOfRange(float chargeRate) {
    printOnConsole("Charge Rate out of range!\n");
    return (chargeRate > CHARGE_RATE);
}

bool isOutOfRange (float data,bool (*OutOfRangeCheckFunction)(float)) {
    return OutOfRangeCheckFunction(data);
}

bool checkAnyDataOutOfRange(float temperature, float soc, float chargeRate)
{
    bool isDataOutOfRange=false;
    isDataOutOfRange=isOutOfRange(temperature,&isTemperatureOutOfRange)?true:(isOutOfRange(soc,&isStateOfChargeOutOfRange)?true:isOutOfRange(chargeRate,&isChargeRateOutOfRange));
    return isDataOutOfRange;
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {
  bool isBatteryOK=true;
  if(checkAnyDataOutOfRange(temperature,soc,chargeRate)) {
    isBatteryOK= false;
  }
  return isBatteryOK;
}
