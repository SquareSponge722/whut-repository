#pragma once

#include <vector>
#include <string>
#include "cardModel.h"
#include "cardList.h"
#include "infoVector.h"
#include "setting.h"

using namespace std;
//单例类
class cardVector
{
public:
	static cardVector& getInstance() { //C++0x 后线程安全
		static cardVector instance;
		return instance;
	}
	int addCard(const string& name,const string& pwd,const double balance,infoVector& infoV);
	card* isExisted(const string& name,int &index);
	bool isExisted(const string& name);
	void displayCard(setting& settings, const string& name = "");
	void updateCardVector(const string& path = setting::getInstance().getCardPath());
	void resetPath(const string& path = setting::getInstance().getCardPath());
private:
	cardList cardList_;
	void saveCard(const card* pCard, const string& path = setting::getInstance().getCardPath());
	cardVector(const string& filename = setting::getInstance().getCardPath());
	~cardVector();
};