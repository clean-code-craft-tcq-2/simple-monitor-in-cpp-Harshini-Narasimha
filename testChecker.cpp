#include <assert.h>
#include "checker.h"

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

void testGetToleranceValue(float upper_limit,float expectedValue)
{
   assert(getToleranceValue(upper_limit)==expectedValue);
}

void testGetLowerLevelWarningLevelStatus(float testData, float lower_limit, float upper_limit,warningLevel expectedWarningLevel)
{
   assert(getLowerLevelWarningLevelStatus(testData,lower_limit, upper_limit)==expectedWarningLevel);
}

void testGetHigherLevelWarningLevelStatus(float testData, float upper_limit,warningLevel lowerWarningLevel,warningLevel expectedWarningLevel)
{
   assert(getHigherLevelWarningLevelStatus(testData, upper_limit,lowerWarningLevel)==expectedWarningLevel);
}

void testGetWarningLevelStatus(float data, float lower_limit,float upper_limit,warningLevel expectedWarningLevel)
{
   assert(getWarningLevelStatus(data,lower_limit,upper_limit)== expectedWarningLevel);
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
  testGetToleranceValue(80,4);//0.05*80
  testGetLowerLevelWarningLevelStatus(24,20,80,LOW_WARNING_LEVEL);//approaching lower limit
  testGetLowerLevelWarningLevelStatus(15,20,80,LOW_BREACH_LEVEL);//below lower limit
  testGetHigherLevelWarningLevelStatus(50,45,NORMAL_LEVEL,HIGH_BREACH_LEVEL);//above upper limit
  testGetHigherLevelWarningLevelStatus(78,80,NORMAL_LEVEL,HIGH_WARNING_LEVEL);//approaching upperlimit
  testGetWarningLevelStatus(0.5,0.0,0.8,NORMAL_LEVEL);
  testGetWarningLevelStatus(24,20,80,LOW_WARNING_LEVEL);//approaching lower limit
  testGetWarningLevelStatus(60,0,45,HIGH_BREACH_LEVEL);//above upperlimit:45
  testBatteryCheck(50, 80, 0, false); //temperature greater than 45, so battery not ok
  testBatteryCheck(30, 90, 0, false); //soc greater than 80, so battery not ok
  testBatteryCheck(30, 90, 1.0, false); //charge rate greater than 0.8, so battery not ok
}
