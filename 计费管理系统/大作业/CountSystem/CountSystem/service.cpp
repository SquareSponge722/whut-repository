
#include <iostream>
#include <string>
#include <sstream>
#include "service.h"
#include "utils.h"
#include "global.h"

using namespace std;

void addCard(cardVector &cardV)
{
	string name, pwd;
	double balance;

	if ((inputName(name) && inputPwd(pwd) && inputBalance(balance))) 
	{
		int flag = cardV.addCard(name, pwd, balance);
		switch (flag)
		{
		case SUCCESS:
			cout << endl << endl;
			cout << "���ţ�" << name << endl;
			cout << "���룺" << pwd << endl;
			cout << "��" << balance;
			cout << endl << endl;
			break;
		case FAILURE:
			cout << "��Ϣ¼��ʧ��..." << endl;
			break;
		case EXISTED:
			cout << "�����Ѵ��ڣ�" << endl;
			break;
		default:
			cout << "δ֪����ȥ���Ʊ�ɣ�" << endl;
			break;
		}
	}

	return;
}
bool inputName(string &name)
{
	while (true) 
	{
		cout << "�����뿨��(����Ϊ1~17)��";
		cin >> name;
		cinClear();

		if (name.length() >= 17)
		{
			cout << "���ų��������" << endl;
			cout << REINPUTHINT;

			char ch = 'N';
			inputYN(ch);

			if (ch == 'N')
			{
				cout << CANCELHINT << endl;
				return false;
			}
			else continue;
		}
		else break;
	}
	return true;
}
bool inputPwd(string &pwd)
{
	while (true)
	{
		cout << "����������(����Ϊ1~8)��";
		cin >> pwd;
		cinClear();

		if (pwd.length() >= 8)
		{
			cout << "���볤�������" << endl;
			cout << REINPUTHINT;

			char ch = 'N';
			inputYN(ch);

			if (ch == 'N')
			{
				cout << CANCELHINT << endl;
				return false;
			}
		}
		else break;
	}
	return true;
}
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
bool confirmBalance(double balance)  //�˺���Դ������ʱ������Ա��ˢ��11�飬��Ҹ�Ǯʱһ��Ҫ�������
{
	double confirmBalance;
	while (true)
	{
		cout << "���ٴ������";
		if (!inputSafeDouble(confirmBalance)) return false;

		if (fabs(confirmBalance - balance) > 0.1)
		{
			cout << "��ƥ�䣡" << endl;
			cout << REINPUTHINT;

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
void displayCard(cardVector& cardV)
{
	string name;
	while (true)
	{
		name = "";
		cout << "�Ƿ����ģʽƥ�䣿(y/n) ";
		char ch = 'N';
		inputYN(ch);

		if (ch == 'Y' && !inputName(name)) continue;
		cardV.displayCard(name);
		break;
	}
}
void pauseCard(cardVector& cardV)
{
	string name, pwd;
	int index;
	card* bufCard;

	while (true)
	{
		if (!inputName(name))
		{
			cout << CANCELHINT << endl;
			return;
		}
		bufCard = cardV.isExisted(name, index);
		if (bufCard == NULL)
		{
			cout << "���Ų����ڣ�" << endl;
			cout << REINPUTHINT;

			char ch = 'N';
			inputYN(ch);

			if (ch == 'N')
			{
				cout << CANCELHINT << endl;
				return;
			}
			else continue;
		}
		else
		{
			while (true) 
			{
				if (!inputPwd(pwd)) return;
				
				if (strcmp(pwd.c_str(), bufCard->pwd) != 0)
				{
					cout << "�������" << endl;
					cout << REINPUTHINT;

					char ch = 'N';
					inputYN(ch);

					if (ch == 'N')
					{
						cout << CANCELHINT << endl;
						return;
					}
					else continue;
				}
				else break;
			}
		}

		bufCard->status = PAUSED;
		cardV.updateCardVector();
		return;
	}
}