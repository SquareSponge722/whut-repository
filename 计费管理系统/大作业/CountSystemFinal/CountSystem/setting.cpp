#include "setting.h"
#include "transUtils.h"
#include <iomanip>

using namespace std;
setting::setting(const string& cardPath_, const string& infoPath_, const string& logPath_, const string& settingPath_, const int unit_, const double fee_, const double limit_, const bool writeFile_)
{
	strcpy_s(content.cardPath, cardPath_.c_str());
	strcpy_s(content.infoPath, infoPath_.c_str());
	strcpy_s(content.logPath, logPath_.c_str());
	strcpy_s(content.settingPath, settingPath_.c_str());
	content.unit = unit_;
	content.fee = fee_;
	content.limit = limit_;
	content.writeFile = writeFile_;

	ifstream ifile(content.settingPath);
	Content bufContent;

	if (!ifile.is_open()) return;

	ifile.read((char*)&bufContent, sizeof(Content));
	content = bufContent;

	if (content.writeFile) logFile.open(content.logPath, ios::app);
}
setting::~setting() {}
/*
使用此函数判断是否写日志
*/
bool setting::fileAvailable()
{
	static bool open = logFile.is_open();
	if (content.writeFile && !open) 
	{
		logFile.open(content.logPath,ios::ate);
		open = logFile.is_open();
	}
	return content.writeFile && open;
}
/*
日志头 仅限内部调用！
*/
void setting::headLog(const string& head)
{
	logFile << endl << SPLITELINE << head << endl;
}
/*
日志时间戳
一般用作日志尾
*/
void setting::timeLog()
{
	if (!fileAvailable()) return;

	char date[TIMELENGTH] = { 0 };
	timeToString(time(NULL), date);

	logFile << DOWNLINE << date << endl;
}
void setting::addLog(const string& name, const string& pwd, const double balance)
{
	if (!fileAvailable()) return;

	headLog("新卡创建");

	logFile << "卡号：" << name << endl;
	logFile << "密码：" << pwd << endl;
	logFile << "金额：" << balance << endl;
	
	timeLog();
}
void setting::displayHeadLog()
{
	if (!fileAvailable()) return;

	headLog("查询");

	logFile << "卡号" << "\t" << "状态" << "\t" << "余额" << "\t" << "累计充值" << "\t\t" << "使用次数" << "\t\t" << "上次使用时间" << endl;
}
void setting::displayBodyLog(const string& name, const int status, const double balance, const double totalUse, const int useCount, const string& lastTime)
{
	if (!fileAvailable()) return;

	logFile << name << '\t';

	switch (status)
	{
	case USING:
		logFile << "上机\t";
		break;
	case UNUSE:
		logFile << "未上机\t";
		break;
	case PAUSED:
		logFile << "注销\t";
		break;
	default:
		logFile << "异常状态\t";
		break;
	}

	streamDouble(balance);
	logFile << '\t';

	streamDouble(totalUse);
	logFile << "\t\t";

	logFile << useCount << "\t\t";

	logFile << lastTime << endl;
}
void setting::pauseLog(const string& name, const double chargeBack)
{
	if (!fileAvailable()) return;

	headLog("销卡");

	logFile << "卡号：" << name << " 已注销" << endl;
	logFile << "余额：";
	streamDouble(chargeBack);
	logFile << " 已清空" << endl;
	
	timeLog();
}
void setting::setUseLog(const string& name)
{
	if (!fileAvailable()) return;

	headLog("上机");

	logFile << "卡号：" << name << " 已上机" << endl;

	timeLog();
}
void setting::setUnuseLog(const string& name, const double charge)
{
	if (!fileAvailable()) return;

	headLog("下机");

	logFile << "卡号：" << name << " 已下机" << endl;
	logFile << "此次收费：";
	streamDouble(charge);
	logFile << " 元" << endl;

	timeLog();
}
void setting::chargeLog(const string& name, const double charge)
{
	if (!fileAvailable()) return;

	headLog("充值");

	logFile << "卡号：" << name << endl;
	logFile << "充值：";
	streamDouble(charge);
	logFile << " 元" << endl;

	timeLog();
}
void setting::feeBackLog(const string& name, const double feeBack)
{
	if (!fileAvailable()) return;

	headLog("退费");

	logFile << "卡号：" << name << endl;
	logFile << "退费：";
	streamDouble(feeBack);
	logFile << " 元" << endl;

	timeLog();
}
void setting::search1HeadLog(const string& name)
{
	if (!fileAvailable()) return;

	headLog("消费记录查询");

	logFile << "查询卡号：" << name << endl;

	logFile << SPLITELINE << SPLITELINE << endl;
	logFile << "收入" << "\t\t" << "开始时间" << "\t\t\t" << "结束时间" << "\t\t\t" << "操作类型" << endl;
}
void setting::search1BodyLog(const double value, const string& sDate, const string& eDate, const int flag)
{
	if (!fileAvailable()) return;

	switch (flag)
	{
	case INFO_NEW:
		streamDouble(value);
		logFile << "\t\t" << sDate << '\t' << sDate << '\t' << "新卡" << endl;
		break;
	case INFO_PAUSE:
		streamDouble(value);
		logFile << "\t\t" << sDate << '\t' << sDate << '\t' << "销卡" << endl;
		break;
	case INFO_CHARGE:
		streamDouble(value);
		logFile << "\t\t" << sDate << '\t' << sDate << '\t' << "充值" << endl;
		break;
	case INFO_CUNSUME:
		streamDouble(value);
		logFile << "\t\t" << sDate << '\t' << eDate << '\t' << "消费" << endl;
		break;
	case INFO_FEEBACK:
		streamDouble(value);
		logFile << "\t\t" << sDate << '\t' << sDate << '\t' << "退款" << endl;
		break;
	default:
		break;
	}
}
void setting::search2Log(const int sYear, const int sMonth, const int eYear, const int eMonth, const double income, const double expend)
{
	if (!fileAvailable()) return;

	headLog("统计总营业额");

	logFile << "开始时间：" << sYear << "年 " << sMonth << "月" << endl;
	logFile << "结束时间：" << eYear << "年 " << eMonth << "月" << endl;

	logFile << "净收入：";
	streamDouble(income);
	logFile << " 元" << endl;

	logFile << "净支出：";
	streamDouble(-expend);
	logFile << " 元" << endl;

	logFile << "总收入：";
	streamDouble(income + expend);
	logFile << " 元" << endl;

	timeLog();
}
void setting::search3HeadLog(const int year)
{
	if (!fileAvailable()) return;

	headLog("统计月营业额");

	logFile << "统计年份：" << year << "年" << endl;
	logFile << SPLITELINE << SPLITELINE << endl;
	logFile << "月份" << "\t" << "净收入" << "\t\t" << "净支出" << "\t\t" << "总收入" << endl;
}
void setting::search3BodyLog(const int month, const double income, const double expend)
{
	if (!fileAvailable()) return;

	logFile << month << "\t";

	streamDouble(income);
	logFile << "\t\t";

	streamDouble(-expend);
	logFile << "\t\t";

	streamDouble(income + expend);
	logFile << endl;
}
void setting::search3EndLog(const string& tag, const double income, const double expend)
{
	if (!fileAvailable()) return;

	logFile << tag << "\t";

	streamDouble(income);
	logFile << "\t\t";

	streamDouble(-expend);
	logFile << "\t\t";

	streamDouble(income + expend);
	logFile << endl;

	timeLog();
}
/*
是否开启日志
若开启则打开file io流
*/
void setting::setWriteFile(const bool writeFile_)
{
	content.writeFile = writeFile_;
	if (writeFile_) logFile.open(content.logPath, ios::app);
	else if (logFile.is_open()) logFile.close();
	saveSetting();
}
void setting::saveSetting()
{
	ofstream ofile(content.settingPath, ios::binary | ios::ate);
	ofile.write((char*)&content, sizeof(content));
	ofile.close();
}
/*
向文件输出保留小数点后n位的小数
*/
void setting::streamDouble(const double number)
{
	logFile << fixed << setprecision(1) << number;
}
