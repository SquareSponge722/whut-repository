#include <iostream>
#include <sstream>
#include "inputUtils.h"
#include "transUtils.h"
#include "global.h"

bool isYear(const int year) {
	return year >= 1900;
}
bool isMonth(const int month) {
	return month > 0 && month < 13;
}
bool isDay(const int day) { //��ʱ����
	return day > 0 && day < 32;
}
bool isInt(const string& str, const bool mustPositive)
{
	int length = str.size();
	for (int i = 0; i < length; i++)
	{
		if (!i && str[i] == '+') continue;
		if (!i && str[i] == '-' && !mustPositive) continue;
		if ((str[i] < '0') || (str[i] > '9')) return false;
	}
	return true;
}
bool isNumber(const string& str,const bool mustPositive)
{
	bool hasDot = false;
	int length = str.size();
	for (int i = 0; i < length; i++)
	{
		if (!i && str[i] == '+') continue;
		if (!i && str[i] == '-' && !mustPositive) continue;
		if ((str[i] < '0') || (str[i] > '9'))
		{
			if (str[i] == '.' && !hasDot && i != length - 1 && i)
			{
				hasDot = true;
				continue;
			}
			return false;
		}
	}
	return true;
}
/*
���ݴ�����Y/N
����false��־�û�ȡ������
*/
void inputYN(char& ch)
{
	ch = 0;
	while (ch != 'Y' && ch != 'N')
	{
		cin >> ch;
		cinClear();
		ch = toupper(ch);
		if (ch != 'Y' && ch != 'N') cout << "������ y �� n��";
	}
	return;
}
/*
���ݴ���������
����false��־�û�ȡ������
Ĭ�ϷǸ�
*/
bool inputSafeInt(int& number, const bool mustPositive)
{
	string strSafe;
	while (true)
	{
		cin >> strSafe;
		cinClear();

		if (!isInt(strSafe, mustPositive))
		{
			cout << "�Ƿ����룡" << endl;
			cout << HINT_REINPUT;

			char ch = 0;
			inputYN(ch);

			if (ch == 'N')
			{
				cout << HINT_CANCEL << endl;
				return false;
			}

			cout << "�����룺";
		}
		else
		{
			istringstream is(strSafe);
			is >> number;
			return true;
		}
	}
}
/*
���ݴ����븡����
����false��־�û�ȡ������
Ĭ�ϷǸ�
*/
bool inputSafeDouble(double& number, const bool mustPositive)
{
	string strSafe;
	while (true)
	{
		cin >> strSafe;
		cinClear();

		if (!isNumber(strSafe, mustPositive))
		{
			cout << "�Ƿ����룡" << endl;
			cout << HINT_REINPUT;

			char ch = 0;
			inputYN(ch);

			if (ch == 'N')
			{
				cout << HINT_CANCEL << endl;
				return false;
			}

			cout << "�����룺";
		}
		else
		{
			istringstream is(strSafe);
			is >> number;
			return true;
		}
	}
}
/*
���ݴ����뿨��
����false��־�û�ȡ������
*/
bool inputName(string& name)
{
	while (true)
	{
		cout << "�����뿨��(����Ϊ1~17)��";
		cin >> name;
		cinClear();

		if (name.length() >= 17)
		{
			cout << "���ų��������" << endl;
			cout << HINT_REINPUT;

			char ch = 'N';
			inputYN(ch);

			if (ch == 'N')
			{
				cout << HINT_CANCEL << endl;
				return false;
			}
			else continue;
		}
		else break;
	}
	return true;
}
/*
���ݴ���������
����false��־�û�ȡ������
*/
bool inputPwd(string& pwd)
{
	while (true)
	{
		cout << "����������(����Ϊ1~8)��";
		cin >> pwd;
		cinClear();

		if (pwd.length() >= 8)
		{
			cout << "���볤�������" << endl;
			cout << HINT_REINPUT;

			char ch = 'N';
			inputYN(ch);

			if (ch == 'N')
			{
				cout << HINT_CANCEL << endl;
				return false;
			}
		}
		else break;
	}
	return true;
}
/*
���ݴ�������
����false��־�û�ȡ������
*/
bool inputBalance(double& balance)
{
	while (true)
	{
		cout << "�������";
		if (!inputSafeDouble(balance)) return false;
		if (confirmBalance(balance)) break;
	}
	return true;
}
bool confirmBalance(const double balance)  //�˺���Դ������ʱ������Ա��ˢ��11�飬��Ҹ�Ǯʱһ��Ҫ�������
{
	double confirmBalance;
	while (true)
	{
		cout << "���ٴ������";
		if (!inputSafeDouble(confirmBalance)) return false;

		if (fabs(confirmBalance - balance) > 0.1)
		{
			cout << "��ƥ�䣡" << endl;
			cout << HINT_REINPUT;

			char ch = 'N';
			inputYN(ch);

			if (ch == 'N')
			{
				cout << "��������..." << endl;
				return false;
			}
		}
		else break;
	}
	return true;
}
/*
�˺ŵ�¼����
����nullptr��ʾ�û�ȡ������
*/
card* login(cardVector& cardV)
{
	string name, pwd;
	int index;
	card* pCard;

	while (true)
	{
		if (!inputName(name)) return nullptr;

		pCard = cardV.isExisted(name, index);
		if (pCard == nullptr)
		{
			cout << "���Ų����ڣ�" << endl;
			cout << HINT_REINPUT;

			char ch = 'N';
			inputYN(ch);

			if (ch == 'N')
			{
				cout << HINT_CANCEL << endl;
				return nullptr;
			}
			else continue;
		}
		else
		{
			while (true)
			{
				if (!inputPwd(pwd)) return nullptr;

				if (strcmp(pwd.c_str(), pCard->pwd) != 0)
				{
					cout << "�������" << endl;
					cout << HINT_REINPUT;

					char ch = 'N';
					inputYN(ch);

					if (ch == 'N')
					{
						cout << HINT_CANCEL << endl;
						return nullptr;
					}
					else continue;
				}
				else return pCard;
			}
		}
	}

}
/*
���ݴ��������
����false��־�û�ȡ������
*/
bool inputYear(int& year)
{
	while (true)
	{
		cout << "��������ݣ�";
		if (!inputSafeInt(year)) return false;
		if (!isYear(year))
		{
			cout << "�Ƿ���ݣ�" << endl;
			cout << HINT_REINPUT;

			char ch = 'N';
			inputYN(ch);

			if (ch == 'N')
			{
				cout << HINT_CANCEL << endl;
				return false;
			}
		}
		else return true;
	}
}
/*
���ݴ������·�
����false��־�û�ȡ������
*/
bool inputMonth(int& month)
{
	while (true)
	{
		cout << "�������·ݣ�";
		if (!inputSafeInt(month)) return false;
		if (!isMonth(month))
		{
			cout << "�Ƿ��·ݣ�" << endl;
			cout << HINT_REINPUT;

			char ch = 'N';
			inputYN(ch);

			if (ch == 'N')
			{
				cout << HINT_CANCEL << endl;
				return false;
			}
		}
		else return true;
	}
}
/*
���ݴ��������&�·�
����false��־�û�ȡ������
*/
bool inputYearMonth(int& sYear, int& sMonth, int& eYear, int& eMonth)
{
	cout << "�������ѯ��ʼ����(����ҿ�)" << endl;
	if (!inputYear(sYear) || !inputMonth(sMonth)) return false;
	cout << "�������ѯ��ֹ����" << endl;
	if (!inputYear(eYear) || !inputMonth(eMonth)) return false;
	return true;
}

bool inputYearMonth(int& year, int& month)
{
	cout << "�������ѯ����" << endl;
	if (!inputYear(year) || !inputMonth(month)) return false;
	return true;
}

