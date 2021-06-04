#pragma once
#include <string>
#include <time.h>
#include <fstream>
#include "global.h"

using namespace std;

//µ¥ÀýÀà
class setting
{
public:
	static setting& getInstance()
	{
		static setting instance;
		return instance;
	}
	bool fileAvailable();
	void timeLog();
	void addLog(const string& name, const string& pwd, const double balance);
	void displayHeadLog();
	void displayBodyLog(const string& name, const int status, const double balance, const double totalUse, const int useCount, const string& lastTime);
	void pauseLog(const string& name, const double chargeBack);
	void setUseLog(const string& name);
	void setUnuseLog(const string& name, const double charge);
	void chargeLog(const string& name, const double charge);
	void feeBackLog(const string& name, const double feeBack);
	void search1HeadLog(const string& name);
	void search1BodyLog(const double value, const string& sDate, const string& eDate, const int flag);
	void search2Log(const int sYear, const int sMonth, const int eYear, const int eMonth, const double income, const double expend);
	void search3HeadLog(const int year);
	void search3BodyLog(const int month, const double income, const double expend);
	void search3EndLog(const string& tag, const double income, const double expend);
public:
	void setCardPath(const string& cardPath_) {
		strcpy_s(content.cardPath, cardPath_.c_str());
		saveSetting();
	}
	void setInfoPath(const string& infoPath_) {
		strcpy_s(content.infoPath, infoPath_.c_str());
		saveSetting();
	}
	void setLogPath(const string& logPath_) {
		strcpy_s(content.logPath, logPath_.c_str());
		saveSetting();
	}
	void setUnit(const int unit_) {
		content.unit = unit_;
		saveSetting();
	}
	void setFee(const double fee_) {
		content.fee = fee_;
		saveSetting();
	}
	void setLimit(const double limit_) {
		content.limit = limit_;
		saveSetting();
	}
	void setWriteFile(const bool writeFile_);
	const string getCardPath() {
		return string(content.cardPath);
	}
	const string getInfoPath() {
		return string(content.infoPath);
	}
	const string getLogPath() {
		return string(content.logPath);
	}
	const string getSettingPath() {
		return string(content.settingPath);
	}
	const int getUnit() {
		return content.unit;
	}
	const double getFee() {
		return content.fee;
	}
	const double getLimit() {
		return content.limit;
	}
	const bool getWriteFile() {
		return content.writeFile;
	}
private:
	struct Content
	{
		char cardPath[128];
		char infoPath[128];
		char logPath[128];
		char settingPath[128];
		int unit;
		double fee;
		double limit;
		bool writeFile;
	}content;
	ofstream logFile;
private:
	setting(const string& cardPath_ = CARDPATH, const string& infoPath_ = INFOPATH, const string& logPath_ = LOGPATH
		, const string& settingPath_ = SETTINGPATH, const int unit_ = UNIT, const double fee_ = FEE
		, const double limit_ = LIMIT, const bool writeFile_ = WRITEFILE);
	~setting();
	void saveSetting();
	void streamDouble(const double number);
	void headLog(const string& head);
};