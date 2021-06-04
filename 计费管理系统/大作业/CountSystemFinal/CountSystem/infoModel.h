#pragma once
#include <time.h>
#include <string>
#include "global.h"

using namespace std;

struct info
{
	char name[18]; //卡号
	double charge; //金额
	time_t sDate; //上机时间
	time_t eDate; //下机时间
	int flag; //info类型

	info(const string name_, const double charge_, const int flag_, const time_t sDate_, const time_t eDate_ = 0)
	{
		strcpy_s(name, name_.c_str());
		charge = charge_;
		sDate = sDate_;
		eDate = eDate_;
		flag = flag_;
	}
};