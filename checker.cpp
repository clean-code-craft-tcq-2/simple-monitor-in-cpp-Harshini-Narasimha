#include <assert.h>
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
    if(isOutOfRange(temperature,&isTemperatureOutOfRange) || isOutOfRange(soc,&isStateOfChargeOutOfRange) || isOutOfRange(chargeRate,&isChargeRateOutOfRange)) {
    isDataOutOfRange=true;
    }
    return isDataOutOfRange;
}
bool batteryIsOk(float temperature, float soc, float chargeRate) {
  bool isBatteryOK=true;
  if(checkAnyDataOutOfRange(temperature,soc,chargeRate)) {
    isBatteryOK= false;
  }
  return isBatteryOK;
}

void testOutOfRange(float testData, bool (*OutOfRangeCheckFunction)(float), bool expectedResult) {
  assert(isOutOfRange(testData,*OutOfRangeCheckFunction)==expectedResult);
}
   
void testTemperatureOutOfRange(float testTemperature, bool expectedResult) {
   assert(isTemperatureOutOfRange(testTemperature)==expectedResult);
}

void testStateOfChargeOutOfRange(float testChargeData, bool expectedResult) {
   assert(isStateOfChargeOutOfRange(testChargeData)==expectedResult);
}

void testChargeRateOutOfRange(float testChargeRate, bool expectedResult) {
   assert(isChargeRateOutOfRange(testChargeRate)==expectedResult);
}

void testBatteryCheck(float testTemperature, float testsoc, float testChargeRate, bool expectedResult) {
    assert(batteryIsOk(testTemperature,testsoc,testChargeRate)==expectedResult);
}
int main() {
  testTemperatureOutOfRange(-10, true); //temperature lower than 0, so temperature out of range
  testTemperatureOutOfRange(50, true);  //temperature greater than 45, so temperature out of range
  testTemperatureOutOfRange(30, false);  //temperature is not out of range
  testStateOfChargeOutOfRange(10, true); //soc lower than 20, so soc out of range
  testStateOfChargeOutOfRange(90, true);  //soc greater than 80, so soc out of range
  testStateOfChargeOutOfRange(40, false);  //soc is not out of range
  testChargeRateOutOfRange(1.5, true); //charge rate greater than 0.8, so out of range
  testChargeRateOutOfRange(0.5, false); //charge rate less than 0.8
  testOutOfRange(70,&isTemperatureOutOfRange,true); //temperature greater than 45, so temperature out of range
  testOutOfRange(100,&isStateOfChargeOutOfRange,true); //soc greater than 80, so soc out of range
  testOutOfRange(1.0,&isChargeRateOutOfRange,true); //charge rate greater than 0.8, so out of range
  testBatteryCheck(25, 70, 0.7, true); //all the date are within limit
  testBatteryCheck(50, 80, 0, false); //temperature greater than 45, so battery not ok
  testBatteryCheck(30, 90, 0, false); //soc greater than 80, so battery not ok
  testBatteryCheck(30, 90, 1.0, false); //charge rate greater than 0.8, so battery not ok
}
