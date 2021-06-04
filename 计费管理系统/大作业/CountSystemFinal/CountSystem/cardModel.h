#pragma once
#include <time.h>
#include <string>
#include "global.h"

using std::string;

struct card
{
	char name[18]; // ����
	char pwd[8]; // ����
	int status; // ��״̬
	int useCount; // ʹ�ô���
	time_t startTime; // ����ʱ��
	time_t lastTime; // ���ʹ��ʱ��
	double totalUse; // �ۼƳ�ֵ���
	double balance; // ���

	card(const string& name_ = "",const string& pwd_ = "",const double balance_ = 0,const int status_ = UNUSE,const int useCount_ = 0)
	{
		strcpy_s(name, name_.c_str());
		strcpy_s(pwd, pwd_.c_str());
		totalUse = balance = balance_;
		useCount = useCount_;
		status = status_;
		startTime = lastTime = time(NULL);
	}
	void clone(const card* pCard)
	{
		strcpy_s(name, pCard->name);
		strcpy_s(pwd, pCard->pwd);
		balance = pCard->balance;
		totalUse = pCard->totalUse;
		useCount = pCard->useCount;
		status = pCard->status;
		startTime = pCard->startTime;
		lastTime = pCard->lastTime;
	}
};