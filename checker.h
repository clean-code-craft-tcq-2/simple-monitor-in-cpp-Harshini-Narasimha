#include <iostream>
#include <vector>
#include <map>
using namespace std;

#define LOWER_TEMPERATURE_LIMIT 0
#define UPPER_TEMPERATURE_LIMIT 45
#define LOWER_CHARGE_LIMIT 20
#define UPPER_CHARGE_LIMIT 80
#define LOWER_CHARGE_RATE 0.0
#define UPPER_CHARGE_RATE 0.8
#define WARNING_TOLERANCE_VALUE 0.05

enum supportedLanguage
{
  ENGLISH,
  GERMAN
};

supportedLanguage outputLanguage=ENGLISH;
enum warningLevel
{
   LOW_BREACH_LEVEL,
   LOW_WARNING_LEVEL,
   NORMAL_LEVEL,
   HIGH_WARNING_LEVEL,
   HIGH_BREACH_LEVEL
};

std::vector<std::string> warningMessageInEnglish={"Warning: Below lower limit","Warning: Approaching low breach level","Normal","Warning: Approaching high breach level","Warning: Above high level"};
std::vector<std::string> warningMessageInGerman={"Warnung: Untere Grenze unterschritten","Warnung: Annäherung an niedrige Verletzungsstufe","Normal","Warnung: Annäherung an hohe Verletzungsstufe","Warnung: Über dem hohen Niveau"};
std::vector<std::string> dataTypeInEnglish={"Temperature ","SOC ","Charge Rate "};
std::vector<std::string> dataTypeInGerman={"Temperatur ","SOC ","Ladestrom "};

std::map<supportedLanguage,std::vector<std::string>> warningMessageList ={{ENGLISH,warningMessageInEnglish},{GERMAN,warningMessageInGerman}};
std::map<supportedLanguage,std::vector<std::string>> dataTypeList={{ENGLISH,dataTypeInEnglish},{GERMAN,dataTypeInGerman}};

float getToleranceValue(float upper_limit)
{
    return WARNING_TOLERANCE_VALUE*upper_limit;
}

enum warningLevel getLowerLevelWarningLevelStatus(float data, float lower_limit,float upper_limit)
{
    warningLevel lowerLevelWarningStatus=NORMAL_LEVEL;
    lowerLevelWarningStatus=(data<=lower_limit+getToleranceValue(upper_limit))?((data<=lower_limit)?LOW_BREACH_LEVEL:LOW_WARNING_LEVEL):lowerLevelWarningStatus;
    return lowerLevelWarningStatus;
}

enum warningLevel getHigherLevelWarningLevelStatus(float data, float lower_limit,float upper_limit,warningLevel lowerWarningStatus)
{
    warningLevel higherLevelWarningStatus=NORMAL_LEVEL;
    higherLevelWarningStatus=(data>=upper_limit-getToleranceValue(upper_limit))?((data>upper_limit)?HIGH_BREACH_LEVEL:HIGH_WARNING_LEVEL):lowerWarningStatus;
    return higherLevelWarningStatus;
}

enum warningLevel getWarningLevelStatus(float data, float lower_limit,float upper_limit){
   warningLevel warningLevelStatus=getLowerLevelWarningLevelStatus(data,lower_limit,upper_limit);
   warningLevelStatus=getHigherLevelWarningLevelStatus(data,lower_limit,upper_limit,warningLevelStatus);
   return warningLevelStatus;
}

void printWarningMessage(string stringToPrint){
    cout << stringToPrint;
}

bool isDataOutOfLimit (float data,float limit,string dataType,bool (*dataOutOfLimitCheckFunction)(float,float,string)) {
    return dataOutOfLimitCheckFunction(data,limit,dataType);
}

bool isTemperatureOutOfRange(float temperature) {
    warningLevel temperatureWarningStatus=getWarningLevelStatus(temperature,LOWER_TEMPERATURE_LIMIT,UPPER_TEMPERATURE_LIMIT);
    printWarningMessage(dataTypeList[outputLanguage][0]+warningMessageList[outputLanguage][temperatureWarningStatus]+"\n");
    if(temperatureWarningStatus==LOW_BREACH_LEVEL || temperatureWarningStatus==HIGH_BREACH_LEVEL)
    {
	  return true;
    }
    return false;
}

bool isStateOfChargeOutOfRange(float soc) {
    warningLevel socWarningStatus=getWarningLevelStatus(soc,LOWER_CHARGE_LIMIT,UPPER_CHARGE_LIMIT);
    printWarningMessage(dataTypeList[outputLanguage][1]+warningMessageList[outputLanguage][socWarningStatus]+"\n");
    if(socWarningStatus==LOW_BREACH_LEVEL || socWarningStatus==HIGH_BREACH_LEVEL)
    {
	  return true;
    }
    return false;
}

bool isChargeRateOutOfRange(float chargeRate) {
    warningLevel chargeRateWarningStatus=getWarningLevelStatus(chargeRate,LOWER_CHARGE_RATE,UPPER_CHARGE_RATE);
    printWarningMessage(dataTypeList[outputLanguage][2]+warningMessageList[outputLanguage][chargeRateWarningStatus]+"\n");
    if(chargeRateWarningStatus==LOW_BREACH_LEVEL || chargeRateWarningStatus==HIGH_BREACH_LEVEL)
    {
	  return true;
    }
    return false;
}

bool isOutOfRange (float data,bool (*OutOfRangeCheckFunction)(float)) {
    return OutOfRangeCheckFunction(data);
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {
  bool isBatteryOK = isOutOfRange(temperature,&isTemperatureOutOfRange)? false: (isOutOfRange(soc,&isStateOfChargeOutOfRange)? false: (!isOutOfRange(chargeRate,&isChargeRateOutOfRange)));
  return isBatteryOK;
}
