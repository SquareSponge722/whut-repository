#pragma once

#include <vector>
#include <string>
#include "cardModel.h"

using namespace std;

class cardVector
{
public:
	cardVector(const string filename = CARDPATH);
	~cardVector();
	int addCard(string name, string pwd, double balance);
	card* isExisted(string name,int &index);
	bool isExisted(string name);
	void displayCard(string name = "");
	void updateCardVector(const string path = CARDPATH);
private:
	vector <card> cardV;
	void saveCard(const card* pCard, const string path = CARDPATH);
};