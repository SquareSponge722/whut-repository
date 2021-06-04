#include "cardVector.h"
#include "global.h"
#include "utils.h"
#include <iostream>
#include <fstream>

using namespace std;

cardVector::cardVector(const string filename)
{
	ifstream ifile(filename);
	card bufCard;
	
	if (!ifile.is_open()) return;

	while (true)
	{
		ifile.read((char*)&bufCard, sizeof(card));
		if (ifile.eof()) break;
		cardV.push_back(bufCard);
	}
}
cardVector::~cardVector(){}

int cardVector::addCard(string name, string pwd, double balance)
{
	if (isExisted(name)) return EXISTED;

	card card(name,pwd,balance);

	cardV.push_back(card);
	saveCard(&card);

	return SUCCESS;
}
card* cardVector::isExisted(string name,int &index)
{
	index = 0;

	vector<card>::iterator it;
	for (it = cardV.begin(); it != cardV.end(); it++)
	{	
		if (!strcmp(it->name, name.c_str()))
		{
			return &(*it);
		}
		index++;
	}

	return NULL;
}
bool cardVector::isExisted(string name)
{
	vector<card>::iterator it;
	for (it = cardV.begin(); it != cardV.end(); it++)
		if (!strcmp(it->name, name.c_str())) return true;
	return false;
}
void cardVector::displayCard(string name)
{
	if (cardV.empty())
	{
		cout << ERRORLINE << "无卡存在" << ERRORLINE << endl << endl;
		return;
	}

	cout << endl << SPLITELINE << SPLITELINE << SPLITELINE << endl;
	cout << "卡号\t状态\t余额\t累计充值\t使用次数\t上次使用时间\n";

	vector<card>::iterator it;
	for (it = cardV.begin(); it != cardV.end(); it++)
	{
		if (!name.empty()) 
		{
			string cardName = it->name;
			if (cardName.find(name) == string::npos) continue;
		}

		char lastTime[TIMELENGTH] = { 0 };
		timeToString(it->lastTime, lastTime);
		
		cout << it->name << '\t';
		
		switch (it->status)
		{
		case USING:
			cout << "上机\t";
			break;
		case UNUSE:
			cout << "未上机\t";
			break;
		case PAUSED:
			cout << "注销\t";
			break;
		default:
			cout << "异常状态\t";
			break;
		}

		cout << it->balance << '\t';

		cout << it->totalUse << "\t\t";

		cout << it->useCount << "\t\t";
		
		cout << lastTime << endl;
	}

	cout << SPLITELINE << SPLITELINE << SPLITELINE << endl << endl;
}
void cardVector::saveCard(const card* pCard, const string path)
{
	ofstream ofile(path, ios::binary | ios::app);
	ofile.write((char*)pCard, sizeof(card));
	ofile.close();
}
void cardVector::updateCardVector(const string path)
{
	ofstream ofile(path, ios::binary | ios::ate);
	vector<card>::iterator it;
	for (it = cardV.begin(); it != cardV.end(); it++)
		ofile.write((char*)&(*it), sizeof(card));
	ofile.close();
}