
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
			cout << "卡号：" << name << endl;
			cout << "密码：" << pwd << endl;
			cout << "金额：" << balance;
			cout << endl << endl;
			break;
		case FAILURE:
			cout << "信息录入失败..." << endl;
			break;
		case EXISTED:
			cout << "卡号已存在！" << endl;
			break;
		default:
			cout << "未知错误，去买彩票吧！" << endl;
			break;
		}
	}

	return;
}
bool inputName(string &name)
{
	while (true) 
	{
		cout << "请输入卡号(长度为1~17)：";
		cin >> name;
		cinClear();

		if (name.length() >= 17)
		{
			cout << "卡号长度溢出！" << endl;
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
		cout << "请输入密码(长度为1~8)：";
		cin >> pwd;
		cinClear();

		if (pwd.length() >= 8)
		{
			cout << "密码长度溢出！" << endl;
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
		cout << "请输入金额：";
		if (!inputSafeDouble(balance)) return false;
		if (confirmBalance(balance)) break;
	}
	return true;
}
bool confirmBalance(double balance)  //此函数源于我买饭时工作人员多刷我11块，大家付钱时一定要看清楚！
{
	double confirmBalance;
	while (true)
	{
		cout << "请再次输入金额：";
		if (!inputSafeDouble(confirmBalance)) return false;

		if (fabs(confirmBalance - balance) > 0.1)
		{
			cout << "金额不匹配！" << endl;
			cout << REINPUTHINT;

			char ch = 'N';
			inputYN(ch);

			if (ch == 'N')
			{
				cout << "请重设金额..." << endl;
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
		cout << "是否进行模式匹配？(y/n) ";
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
			cout << "卡号不存在！" << endl;
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
					cout << "密码错误！" << endl;
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