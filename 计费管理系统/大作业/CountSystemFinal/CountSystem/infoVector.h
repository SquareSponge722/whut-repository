#pragma once
#include <string>
#include <vector>
#include <time.h>
#include "global.h"
#include "infoModel.h"
#include "setting.h"

using namespace std;
//单例类
class infoVector
{
public:
	static infoVector& getInstance()
	{
		static infoVector instance;
		return instance;
	}
	void addInfo(const string& name,const double charge,const int flag,const time_t& sDate,const time_t& eDate = 0);
	vector<info>& searchInfo(const string& name,const time_t& sDate,const time_t& eDate); //日期左闭右开
	vector<info>& searchInfo(const time_t& sDate, const time_t& eDate);
	void resetPath(const string& path = setting::getInstance().getInfoPath());
private:
	vector <info> infoV;
	vector <info> infoSearch;
	infoVector(const string& filename = setting::getInstance().getInfoPath());
	~infoVector();
	void saveInfo(const info* pInfo, const string& path = setting::getInstance().getInfoPath());
};