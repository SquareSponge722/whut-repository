#pragma once

#include <time.h>
#include <string>

void cinClear();
void timeToString(time_t t,char* pStr);
time_t stringToTime(char* pStr);
bool isNumber(std::string str,bool mustPositive = false);
void inputYN(char& ch);
bool inputSafeDouble(double& number);