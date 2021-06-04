#include <iostream>
#include <cstdio>
#include <iomanip>
#include "transUtils.h"
#include "global.h"

using namespace std;
/*
��ռ��̻�����
*/
void cinClear()
{
	cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
}
void outputDouble(const double number)
{
	cout << fixed << setprecision(1) << number;
}
void timeToString(const time_t& t, char* pStr)
{
	struct tm timeInfo;
	localtime_s(&timeInfo,&t); //ʹ��localtime_s(nowTime,timeSeconds)
	strftime(pStr, 20, "%Y-%m-%d %H:%M", &timeInfo);
}
time_t stringToTime(const char* pStr)
{
	struct tm timeTemp;

	sscanf_s(pStr, "%d-%d-%d %d:%d", &timeTemp.tm_year, &timeTemp.tm_mon,&timeTemp.tm_mday, &timeTemp.tm_hour, &timeTemp.tm_min);//��ʽ������ʱ��
	timeTemp.tm_year -= 1900; // ���Ϊ��1900�꿪ʼ
	timeTemp.tm_mon -= 1; // �·�Ϊ0~11
	timeTemp.tm_sec = 0;
	timeTemp.tm_isdst = -1;

	return mktime(&timeTemp);
}
time_t intToTime(const int year, const int month, const int day)
{
	struct tm timeTemp;

	timeTemp.tm_year = year - 1900;
	timeTemp.tm_mon = month - 1;
	timeTemp.tm_mday = day;
	timeTemp.tm_hour = 0;
	timeTemp.tm_min = 0;
	timeTemp.tm_sec = 0;
	timeTemp.tm_isdst = -1;

	return mktime(&timeTemp);
}
/*
�����·�(0-11)
*/
int getMonth(const time_t& t)
{
	struct tm timeInfo;
	localtime_s(&timeInfo, &t);
	return timeInfo.tm_mon;
}
