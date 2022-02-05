#include <assert.h>
#include "checker.h"

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

void testAnyDataOutOfRange(float testTemperature, float testsoc, float testChargeRate, bool expectedResult) {
    assert(checkAnyDataOutOfRange(testTemperature,testsoc,testChargeRate)==expectedResult);
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
  testAnyDataOutOfRange(25, 70, 0.7, false); //all the date are within limit
  testAnyDataOutOfRange(40, 70, 2.0, true); //charge rate greater than 0.8, so battery not ok
  testBatteryCheck(25, 70, 0.7, true); //all the date are within limit
  testBatteryCheck(50, 80, 0, false); //temperature greater than 45, so battery not ok
  testBatteryCheck(30, 90, 0, false); //soc greater than 80, so battery not ok
  testBatteryCheck(30, 90, 1.0, false); //charge rate greater than 0.8, so battery not ok
}
