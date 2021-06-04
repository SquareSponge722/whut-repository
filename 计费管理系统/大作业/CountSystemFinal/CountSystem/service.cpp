
#include <iostream>
#include <string>
#include <sstream>
#include "service.h"
#include "transUtils.h"
#include "global.h"
#include "inputUtils.h"

using namespace std;

void addCard(cardVector& cardV, infoVector& infoV, setting& settings)
{
	string name, pwd;
	double balance;

	if (inputName(name) && inputPwd(pwd) && inputBalance(balance))
	{
		int flag = cardV.addCard(name, pwd, balance, infoV); //ע�� info �ڴ˼���
		switch (flag)
		{
		case SUCCESS:
			cout << endl << endl;
			cout << "���ţ�" << name << endl;
			cout << "���룺" << pwd << endl;
			cout << "��" << balance;
			cout << endl << endl;

			settings.addLog(name, pwd, balance);

			break;
		case FAILURE:
			cout << "��Ϣ¼��ʧ��..." << endl;
			break;
		case EXISTED:
			cout << "�����Ѵ��ڣ�" << endl << endl;
			break;
		default:
			cout << "δ֪����ȥ���Ʊ�ɣ�" << endl;
			break;
		}
	}
}
void displayCard(cardVector& cardV, setting& settings)
{
	string name;
	while (true)
	{
		name = "";
		cout << "�Ƿ����ģʽƥ�䣿(y/n) ";
		char ch = 'N';
		inputYN(ch);

		if (ch == 'Y' && !inputName(name)) continue;
		cardV.displayCard(settings, name); //ע�� log �ڴ˵���
		break;
	}
}
/*
ע�����Ὣ������
�����Ѷ��Ҳ����Ӧ����
*/
void pauseCard(cardVector& cardV, infoVector& infoV, setting& settings)
{
	card* bufCard = login(cardV);
	if (bufCard == nullptr) return;

	switch (bufCard->status)
	{
	case USING:
		cout << HINT_USING << HINT_ASK_UNUSE << endl;
		return;
	case PAUSED:
		cout << HINT_PAUSED << HINT_CANCEL << endl;
		return;
	default:
		break;
	}

	double chargeBack = bufCard->balance;
	bufCard->totalUse -= bufCard->balance;
	bufCard->balance = 0;
	bufCard->status = PAUSED;
	cardV.updateCardVector();

	infoV.addInfo(bufCard->name, -chargeBack, INFO_PAUSE, time(NULL));

	cout << "������";
	outputDouble(chargeBack);
	cout << " �����" << endl;
	cout << HINT_SUCCESS << endl;

	settings.pauseLog(bufCard->name, chargeBack);
}
void cardSetUse(cardVector& cardV, setting& settings)
{
	card* bufCard = login(cardV);
	if (bufCard == nullptr) return;

	switch (bufCard->status)
	{
	case USING:
		cout << HINT_USING << HINT_ASK_UNUSE << endl;
		return;
	case PAUSED:
		cout << HINT_PAUSED << HINT_CANCEL << endl;
		return;
	default:
		break;
	}

	if (bufCard->balance < settings.getLimit())
	{
		cout << HINT_BALANCE_SHORTAGE << HINT_CANCEL << endl;
		return;
	}

	bufCard->lastTime = time(NULL);
	bufCard->status = USING;
	cardV.updateCardVector();

	cout << HINT_SUCCESS << endl;

	settings.setUseLog(bufCard->name);
}
void cardSetUnuse(cardVector& cardV, infoVector& infoV, setting& settings)
{
	card* bufCard = login(cardV);
	if (bufCard == nullptr) return;

	switch (bufCard->status)
	{
	case PAUSED:
		cout << HINT_PAUSED << HINT_CANCEL << endl;
		return;
	case UNUSE:
		cout << HINT_UNUSED << HINT_ASK_USING << endl;
		return;
	default:
		break;
	}

	time_t currentTime = time(NULL);
	double fee = ((double)currentTime - bufCard->lastTime) / 60 / settings.getUnit() * settings.getFee();

	if (bufCard->balance - fee < settings.getLimit())
	{
		cout << HINT_BALANCE_SHORTAGE;
		cout << "�����ٳ�ֵ��";
		outputDouble(fee + settings.getLimit() - bufCard->balance + 1);
		cout << " Ԫ";

		cout << HINT_CANCEL << endl;
		return;
	}

	bufCard->useCount++;
	bufCard->balance -= fee;
	bufCard->status = UNUSE;
	cardV.updateCardVector();

	infoV.addInfo(bufCard->name, fee, INFO_CUNSUME, bufCard->lastTime, currentTime);

	cout << HINT_SUCCESS << endl;

	settings.setUnuseLog(bufCard->name, fee);
}
void chargeCard(cardVector& cardV, infoVector& infoV, setting& settings)
{
	card* bufCard = login(cardV);
	if (bufCard == nullptr) return;

	if (bufCard->status == PAUSED) 
	{
		cout << HINT_PAUSED << HINT_CANCEL << endl;
		return;
	}

	double charge = 0;
	if (!inputBalance(charge)) return;
	bufCard->balance += charge;
	bufCard->totalUse += charge;
	cardV.updateCardVector();

	infoV.addInfo(bufCard->name, charge, INFO_CHARGE, time(NULL));

	cout << HINT_SUCCESS << endl;

	settings.chargeLog(bufCard->name, charge);
}
/*
�˿�ᵼ�������Ѷ�ȼ���(��ֹ���˲�ͣ������ˢ���)
*/
void feeBack(cardVector& cardV, infoVector& infoV, setting& settings)
{
	card* bufCard = login(cardV);
	if (bufCard == nullptr) return;

	switch (bufCard->status)
	{
	case USING:
		cout << HINT_USING << HINT_ASK_UNUSE << endl;
		return;
	case PAUSED:
		cout << HINT_PAUSED << HINT_CANCEL << endl;
		return;
	default:
		break;
	}

	double chargeBack = 0;
	while (true)
	{
		if (!inputBalance(chargeBack)) return;
		if (bufCard->balance - chargeBack < 0)
		{
			cout << HINT_BALANCE_SHORTAGE;
			cout << "������";
			outputDouble(bufCard->balance);
			cout << " Ԫ" << endl;

			cout << HINT_REINPUT;
			char ch;
			inputYN(ch);

			if (ch == 'N')
			{
				cout << HINT_CANCEL << endl;
				return;
			}
		}
		else break;
	}
	
	bufCard->balance -= chargeBack;
	bufCard->totalUse -= chargeBack;
	cardV.updateCardVector();

	infoV.addInfo(bufCard->name, -chargeBack, INFO_FEEBACK, time(NULL));

	cout << HINT_SUCCESS << endl;

	settings.feeBackLog(bufCard->name, chargeBack);
}
void searchCount(infoVector& infoV, const char id, setting& settings)
{
	switch (id)
	{
	case '1':
		searchCount1(infoV, settings);
		break;
	case '2':
		searchCount2(infoV, settings);
		break;
	case '3':
		searchCount3(infoV, settings);
		break;
	default:
		break;
	}
}
void searchCount1(infoVector& infoV, setting& settings)
{
	string name;
	int sYear, sMonth;
	int eYear, eMonth;
	cout << SPLITELINE << "���Ѽ�¼��ѯ" << SPLITELINE << endl << endl;
	
	if (!inputName(name)) return;
	if (!inputYearMonth(sYear, sMonth, eYear, eMonth)) return;

	time_t sDate = intToTime(sYear, sMonth);
	time_t eDate = intToTime(eYear, eMonth);
	vector<info>result = infoV.searchInfo(name, sDate, eDate);

	
	if (result.empty())
	{
		cout << HINT_NULL_RESAULT << endl;
		return;
	}

	cout << endl << SPLITELINE << SPLITELINE << endl;
	cout << "����" << "\t\t" << "��ʼʱ��" << "\t\t" << "����ʱ��" << "\t\t" << "��������" << endl;
	
	settings.search1HeadLog(name);

	vector<info>::iterator it;
	for (it = result.begin(); it != result.end(); it++)
	{
		char sDate[TIMELENGTH] = { 0 };
		timeToString(it->sDate, sDate);
		char eDate[TIMELENGTH] = { 0 };
		timeToString(it->eDate, eDate);

		switch (it->flag)
		{
		case INFO_NEW:
			outputDouble(it->charge);
			cout << "\t\t" << sDate << '\t' << sDate << '\t' << "�¿�" << endl;
			break;
		case INFO_PAUSE:
			outputDouble(it->charge);
			cout << "\t\t" << sDate << '\t' << sDate << '\t' << "����" << endl;
			break;
		case INFO_CHARGE:
			outputDouble(it->charge);
			cout << "\t\t" << sDate << '\t' << sDate << '\t' << "��ֵ" << endl;
			break;
		case INFO_CUNSUME:
			outputDouble(it->charge);
			cout << "\t\t" << sDate << '\t' << eDate << '\t' << "����" << endl;
			break;
		case INFO_FEEBACK:
			outputDouble(it->charge);
			cout << "\t\t" << sDate << '\t' << sDate << '\t' << "�˿�" << endl;
			break;
		default:
			break;
		}

		settings.search1BodyLog(it->charge, sDate, eDate, it->flag);
	}

	cout << SPLITELINE << SPLITELINE << endl << endl;
	
	settings.timeLog();
}
void searchCount2(infoVector& infoV, setting& settings)
{
	int sYear, sMonth;
	int eYear, eMonth;
	cout << SPLITELINE << "ͳ����Ӫҵ��" << SPLITELINE << endl << endl;

	if (!inputYearMonth(sYear, sMonth, eYear, eMonth)) return;

	time_t sDate = intToTime(sYear, sMonth);
	time_t eDate = intToTime(eYear, eMonth);
	vector<info>result = infoV.searchInfo(sDate, eDate);


	double income = 0, expend = 0;
	vector<info>::iterator it;
	for (it = result.begin(); it != result.end(); it++)
	{
		if (it->flag == INFO_NEW || it->flag == INFO_CHARGE) income += it->charge;
		if (it->flag == INFO_FEEBACK || it->flag == INFO_PAUSE) expend += it->charge;
	}

	cout << endl << SPLITELINE << SPLITELINE << endl;

	cout << "�����룺";
	outputDouble(income);
	cout << " Ԫ" << endl;
	
	cout << "��֧����";
	outputDouble(-expend);
	cout << " Ԫ" << endl;

	cout << "�����룺";
	outputDouble(income + expend);
	cout << " Ԫ" << endl;

	cout << SPLITELINE << SPLITELINE << endl << endl;

	settings.search2Log(sYear, sMonth, eYear, eMonth, income, expend);
}
void searchCount3(infoVector& infoV, setting& settings)
{
	int year;
	cout << SPLITELINE << "ͳ����Ӫҵ��" << SPLITELINE << endl << endl;

	if (!inputYear(year)) return;

	time_t sDate = intToTime(year);
	time_t eDate = intToTime(year + 1);
	vector<info>result = infoV.searchInfo(sDate, eDate);


	double income[16] = { 0 }, expend[16] = { 0 };
	double sum_income = 0, sum_expend = 0;
	vector<info>::iterator it;
	for (it = result.begin(); it != result.end(); it++)
	{
		if (it->flag == INFO_NEW || it->flag == INFO_CHARGE) income[getMonth(it->sDate)] += it->charge;
		if (it->flag == INFO_FEEBACK || it->flag == INFO_PAUSE) expend[getMonth(it->sDate)] += it->charge;
	}

	cout << endl << SPLITELINE << SPLITELINE << endl;
	cout << "�·�" << "\t" << "������" << "\t\t" << "��֧��" << "\t\t" << "������" << endl;

	settings.search3HeadLog(year);

	for (int i = 0; i < 12; i++)
	{
		cout << i + 1 << "\t";
		
		outputDouble(income[i]);
		cout << "\t\t";

		outputDouble(-expend[i]);
		cout << "\t\t";

		outputDouble(income[i] + expend[i]);
		cout << endl;

		sum_income += income[i];
		sum_expend += expend[i];

		settings.search3BodyLog(i + 1, income[i], expend[i]);
	}

	cout << "�ϼ�" << "\t";

	outputDouble(sum_income);
	cout << "\t\t";

	outputDouble(-sum_expend);
	cout << "\t\t";

	outputDouble(sum_income + sum_expend);
	cout << endl;

	cout << SPLITELINE << SPLITELINE << endl << endl;

	settings.search3EndLog("�ϼ�", sum_income, sum_expend);
}
void settings(setting& settings, const char id)
{
	string path = "";
	int iValue = 0;
	double dValue = 0;
	char ch = 'N';
	switch (id)
	{
	case '1':
		cout << "��ǰ�Ŀ�·��Ϊ��" << settings.getCardPath() << endl;
		cout << HINT_REWRITE;

		inputYN(ch);

		if (ch == 'Y')
		{
			cout << HINT_ASK_PATH;

			cin >> path;
			cinClear();

			settings.setCardPath(path);
			cardVector::getInstance().resetPath();

			//cout << HINT_SUCCESS << HINT_ASK_QUIT << endl;
			cout << HINT_SUCCESS << endl;
		}
		else cout << endl;
		break;
	case '2':
		cout << "��ǰ�Ĳ�����¼·��Ϊ��" << settings.getInfoPath() << endl;
		cout << HINT_REWRITE;

		inputYN(ch);

		if (ch == 'Y')
		{
			cout << HINT_ASK_PATH;

			cin >> path;
			cinClear();

			settings.setInfoPath(path);
			infoVector::getInstance().resetPath();

			//cout << HINT_SUCCESS << HINT_ASK_QUIT << endl;
			cout << HINT_SUCCESS << endl;
		}
		else cout << endl;
		break;
	case '3':
		cout << "��ǰ����־·��Ϊ��" << settings.getLogPath() << endl;
		cout << HINT_REWRITE;

		inputYN(ch);

		if (ch == 'Y')
		{
			cout << HINT_ASK_PATH;

			cin >> path;
			cinClear();

			settings.setLogPath(path);

			cout << HINT_SUCCESS << endl;
		}
		else cout << endl;
		break;
	case '4':
		cout << "��ǰ�ļƷѵ�ԪΪ��" << settings.getUnit() << " ����" << endl;
		cout << HINT_REWRITE;

		inputYN(ch);

		if (ch == 'Y')
		{
			cout << HINT_ASK_VALUE;

			if (!inputSafeInt(iValue)) return;

			settings.setUnit(iValue);

			cout << HINT_SUCCESS << endl;
		}
		else cout << endl;
		break;
	case '5':
		cout << "��ǰ���շѱ�׼Ϊ��" << settings.getFee() << " Ԫ/��Ԫ" << endl;
		cout << HINT_REWRITE;

		inputYN(ch);

		if (ch == 'Y')
		{
			cout << HINT_ASK_VALUE;

			if (!inputSafeDouble(dValue)) return;

			settings.setFee(dValue);

			cout << HINT_SUCCESS << endl;
		}
		else cout << endl;
		break;
	case '6':
		cout << "��ǰ���������Ϊ��" << settings.getLimit() << " Ԫ" << endl;
		cout << HINT_REWRITE;

		inputYN(ch);

		if (ch == 'Y')
		{
			cout << HINT_ASK_VALUE;

			if (!inputSafeDouble(dValue)) return;

			settings.setLimit(dValue);

			cout << HINT_SUCCESS << endl;
		}
		else cout << endl;
		break;
	case '7':
		cout << "��ǰ����־״̬Ϊ��" << (settings.getWriteFile() ? "����" : "�ر�") << endl;
		cout << HINT_REWRITE;

		inputYN(ch);

		if (ch == 'Y')
		{
			settings.setWriteFile(!settings.getWriteFile());

			cout << HINT_SUCCESS << endl;
		}
		else cout << endl;
		break;
	default:
		break;
	}
}