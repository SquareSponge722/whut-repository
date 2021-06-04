#include <iostream>
#include <cstdio>
#include <sstream>
#include "utils.h"
#include "global.h"

using namespace std;

void cinClear()
{
	cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
}
void timeToString(time_t t, char* pStr)
{
	struct tm timeInfo;
	localtime_s(&timeInfo,&t); //使用localtime_s(nowTime,timeSeconds)
	strftime(pStr, 20, "%Y-%m-%d %H:%M", &timeInfo);
}
time_t stringToTime(char* pStr)
{
	struct tm timeTemp;
	time_t timeResult;

	sscanf_s(pStr, "%d-%d-%d %d:%d", &timeTemp.tm_year, &timeTemp.tm_mon,&timeTemp.tm_mday, &timeTemp.tm_hour, &timeTemp.tm_min);//格式化读入时间
	timeTemp.tm_year -= 1900; // 年份为从1900年开始
	timeTemp.tm_mon -= 1; // 月份为0~11
	timeTemp.tm_sec = 0;
	timeTemp.tm_isdst = -1;

	timeResult = mktime(&timeTemp);
	return timeResult;
}
bool isNumber(string str,bool mustPositive)
{
	bool hasDot = false;
	int length = str.size();
	for (int i = 0; i < length; i++)
	{
		if (!i && str[i] == '+') continue;
		if (!i && str[i] == '-' && !mustPositive) continue;
		if ((str[i] < '0') || (str[i] > '9'))
		{
			if (str[i] == '.' && !hasDot && i != length - 1 && i)
			{
				hasDot = true;
				continue;
			}
			return false;
		}
	}
	return true;
}
void inputYN(char& ch)
{
	ch = 0;
	while (ch != 'Y' && ch != 'N')
	{
		cin >> ch;
		cinClear();
		ch = toupper(ch);
		if (ch != 'Y' && ch != 'N') cout << "请输入 y 或 n：";
	}
	return;
}
bool inputSafeDouble(double& number)
{
	string strSafe;
	double strToDouble;
	while (true)
	{
		cin >> strSafe;
		cinClear();

		if (!isNumber(strSafe, true))
		{
			cout << "非法输入！" << endl;
			cout << REINPUTHINT;

			char ch = 0;
			inputYN(ch);

			if (ch == 'N')
			{
				cout << CANCELHINT << endl;
				return false;
			}

			cout << "请输入：";
		}
		else
		{
			istringstream is(strSafe);
			is >> number;
			return true;
		}
	}
	
}