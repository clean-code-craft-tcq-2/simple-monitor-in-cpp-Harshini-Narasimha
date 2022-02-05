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

bool isDataBelowLowerLimit(float data, float lower_limit,string dataType)
{
  bool isDataBelowLowerLimit=false;
  if(data<lower_limit)
  {
  printOnConsole(dataType+" is lower than "+to_string(lower_limit)+"\n");
  isDataBelowLowerLimit=true;
  }
  return isDataBelowLowerLimit;
}

bool isDataAboveUpperLimit(float data, float lower_limit,string dataType)
{
  bool isDataBelowLowerLimit=false;
  if(data>lower_limit)
  {
  printOnConsole(dataType+" is higher than "+to_string(lower_limit)+"\n");
  isDataBelowLowerLimit=true;
  }
  return isDataBelowLowerLimit;
}

bool isDataOutOfLimit (float data,float limit,string dataType,bool (*dataOutOfLimitCheckFunction)(float,float,string)) {
    return dataOutOfLimitCheckFunction(data,limit,dataType);
}

bool isTemperatureOutOfRange(float temperature) {
    printOnConsole("Temperature out of range!\n");
    return (isDataOutOfLimit(temperature,LOWER_TEMPERATURE_LIMIT,"Temperature",&isDataBelowLowerLimit) || isDataOutOfLimit(temperature,UPPER_TEMPERATURE_LIMIT,"Temperature",&isDataAboveUpperLimit));
}

bool isStateOfChargeOutOfRange(float soc) {
    printOnConsole("State of Charge out of range!\n");
    return (isDataOutOfLimit(soc,LOWER_CHARGE_LIMIT,"State Of charge",&isDataBelowLowerLimit) || isDataOutOfLimit(soc,UPPER_CHARGE_LIMIT,"State Of charge",&isDataAboveUpperLimit));
}

bool isChargeRateOutOfRange(float chargeRate) {
    printOnConsole("Charge Rate out of range!\n");
    return (isDataOutOfLimit(chargeRate,CHARGE_RATE,"Charge",&isDataAboveUpperLimit));
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
