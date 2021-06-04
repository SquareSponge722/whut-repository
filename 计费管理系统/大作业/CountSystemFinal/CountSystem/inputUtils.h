#pragma once

#include <string>
#include "cardModel.h"
#include "cardVector.h"

using namespace std;

bool isYear(const int year);
bool isMonth(const int month);
bool isDay(const int day);
bool isInt(const string& str,const bool mustPositive = true);
bool isNumber(const string& str,const bool mustPositive = true);
void inputYN(char& ch);
bool inputSafeInt(int& number, const bool mustPositive = true);
bool inputSafeDouble(double& number, const bool mustPositive = true);
bool inputName(string& name);
bool inputPwd(string& pwd);
bool inputBalance(double& balance);
bool confirmBalance(const double balance);
card* login(cardVector& cardV);
bool inputYear(int& year);
bool inputMonth(int& month);
bool inputYearMonth(int& sYear, int& sMonth, int& eYear, int& eMonth);
bool inputYearMonth(int& year, int& month);