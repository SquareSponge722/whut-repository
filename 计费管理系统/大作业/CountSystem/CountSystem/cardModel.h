#pragma once
#include <time.h>
#include <string>
#include "global.h"

struct card
{
	char name[18]; // 卡号
	char pwd[8]; // 密码
	int status; // 卡状态
	int useCount; // 使用次数
	time_t startTime; // 开卡时间
	//time_t endTime; // 卡截止时间
	time_t lastTime; // 最后使用时间
	double totalUse; // 累计充值金额
	double balance; // 余额

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