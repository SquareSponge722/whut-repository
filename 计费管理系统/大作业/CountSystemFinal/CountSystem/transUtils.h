#pragma once

#include <time.h>
#include <string>

void cinClear();
void outputDouble(const double number);
void timeToString(const time_t& t,char* pStr);
time_t stringToTime(const char* pStr);
time_t intToTime(const int year, const int month = 1, const int day = 1);
int getMonth(const time_t& t);