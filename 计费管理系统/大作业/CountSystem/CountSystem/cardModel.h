#pragma once
#include <time.h>
#include <string>
#include "global.h"

struct card
{
	char name[18]; // ����
	char pwd[8]; // ����
	int status; // ��״̬
	int useCount; // ʹ�ô���
	time_t startTime; // ����ʱ��
	//time_t endTime; // ����ֹʱ��
	time_t lastTime; // ���ʹ��ʱ��
	double totalUse; // �ۼƳ�ֵ���
	double balance; // ���

	card(std::string name_ = "undefine", std::string pwd_ = "114514", double balance_ = 0, int status_ = UNUSE, int useCount_ = 0)
	{
		strcpy_s(name, name_.c_str());
		strcpy_s(pwd, pwd_.c_str());
		totalUse = balance = balance_;
		useCount = useCount_;
		status = status_;
		startTime = lastTime = time(NULL);
	}
};