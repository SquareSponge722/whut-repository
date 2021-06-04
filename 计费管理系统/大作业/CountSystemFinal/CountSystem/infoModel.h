#pragma once
#include <time.h>
#include <string>
#include "global.h"

using namespace std;

struct info
{
	char name[18]; //����
	double charge; //���
	time_t sDate; //�ϻ�ʱ��
	time_t eDate; //�»�ʱ��
	int flag; //info����

	info(const string name_, const double charge_, const int flag_, const time_t sDate_, const time_t eDate_ = 0)
	{
		strcpy_s(name, name_.c_str());
		charge = charge_;
		sDate = sDate_;
		eDate = eDate_;
		flag = flag_;
	}
};