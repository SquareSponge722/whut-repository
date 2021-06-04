#include "cardVector.h"
#include "global.h"
#include "transUtils.h"
#include <iostream>
#include <fstream>

using namespace std;

cardVector::cardVector(const string& filename)
{
	ifstream ifile(filename);
	card bufCard;
	
	if (!ifile.is_open()) return;

	while (true)
	{
		ifile.read((char*)&bufCard, sizeof(card));
		if (ifile.eof()) break;
		cardList_.pushback(&bufCard);
	}
}
cardVector::~cardVector(){}

int cardVector::addCard(const string& name, const string& pwd, const double balance, infoVector& infoV)
{
	if (isExisted(name)) return EXISTED;

	card card(name,pwd,balance);

	cardList_.pushback(&card);
	saveCard(&card);

	infoV.addInfo(card.name, card.balance, INFO_NEW, card.startTime); //加入info

	return SUCCESS;
}
card* cardVector::isExisted(const string& name, int &index)
{
	index = 0;
	if (cardList_.empty()) return nullptr;

	cardCursor cursor(cardList_.begin());
	do
	{
		if (!strcmp(cursor.getItem()->name, name.c_str()))
		{
			return cursor.getItem();
		}
	} while (cursor.moveNext());

	return nullptr;
}
bool cardVector::isExisted(const string& name)
{
	if (cardList_.empty()) return false;

	cardCursor cursor(cardList_.begin());
	do
	{
		if (!strcmp(cursor.getItem()->name, name.c_str())) return true;
	} while (cursor.moveNext());

	return false;
}
void cardVector::displayCard(setting& settings,const string& name)
{

	if (cardList_.empty())
	{
		cout << HINT_NULL_RESAULT << endl;
		return;
	}

	cout << endl << SPLITELINE << SPLITELINE << SPLITELINE << endl;
	cout << "卡号\t状态\t余额\t累计充值\t使用次数\t上次使用时间\n";

	settings.displayHeadLog();

	cardCursor cursor(cardList_.begin());
	do
	{
		card* pItem = cursor.getItem();

		if (!name.empty())
		{
			string cardName = pItem->name;
			if (cardName.find(name) == string::npos) continue;
		}

		char lastTime[TIMELENGTH] = { 0 };
		timeToString(pItem->lastTime, lastTime);

		cout << pItem->name << '\t';

		switch (pItem->status)
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

		outputDouble(pItem->balance);
		cout << '\t';

		outputDouble(pItem->totalUse);
		cout << "\t\t";

		cout << pItem->useCount << "\t\t";

		cout << lastTime << endl;

		settings.displayBodyLog(pItem->name, pItem->status, pItem->balance, pItem->totalUse, pItem->useCount, lastTime);

	} while (cursor.moveNext());

	cout << SPLITELINE << SPLITELINE << SPLITELINE << endl << endl;

	settings.timeLog();
}
void cardVector::saveCard(const card* pCard, const string& path)
{
	ofstream ofile(path, ios::binary | ios::app);
	ofile.write((char*)pCard, sizeof(card));
	ofile.close();
}
void cardVector::updateCardVector(const string& path)
{
	if (cardList_.empty()) return;
	ofstream ofile(path, ios::binary | ios::ate);
	cardCursor cursor(cardList_.begin());
	do
	{
		ofile.write((char*)cursor.getItem(), sizeof(card));
	} while (cursor.moveNext());
	ofile.close();
}
void cardVector::resetPath(const string& path)
{
	cardList_.clear();

	ifstream ifile(path);
	card bufCard;

	if (!ifile.is_open()) return;

	while (true)
	{
		ifile.read((char*)&bufCard, sizeof(card));
		if (ifile.eof()) break;
		cardList_.pushback(&bufCard);
	}
}
