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
bool isDay(const int day) { //临时处理
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
高容错输入Y/N
返回false标志用户取消操作
*/
void inputYN(char& ch)
{
	ch = 0;
	while (ch != 'Y' && ch != 'N')
	{
		cin >> ch;
		cinClear();
		ch = toupper(ch);
		if (ch != 'Y' && ch != 'N') cout << "请输入 y 或 n：";
	}
	return;
}
/*
高容错输入整型
返回false标志用户取消操作
默认非负
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
			cout << "非法输入！" << endl;
			cout << HINT_REINPUT;

			char ch = 0;
			inputYN(ch);

			if (ch == 'N')
			{
				cout << HINT_CANCEL << endl;
				return false;
			}

			cout << "请输入：";
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
高容错输入浮点数
返回false标志用户取消操作
默认非负
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
			cout << "非法输入！" << endl;
			cout << HINT_REINPUT;

			char ch = 0;
			inputYN(ch);

			if (ch == 'N')
			{
				cout << HINT_CANCEL << endl;
				return false;
			}

			cout << "请输入：";
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
高容错输入卡号
返回false标志用户取消操作
*/
bool inputName(string& name)
{
	while (true)
	{
		cout << "请输入卡号(长度为1~17)：";
		cin >> name;
		cinClear();

		if (name.length() >= 17)
		{
			cout << "卡号长度溢出！" << endl;
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
高容错输入密码
返回false标志用户取消操作
*/
bool inputPwd(string& pwd)
{
	while (true)
	{
		cout << "请输入密码(长度为1~8)：";
		cin >> pwd;
		cinClear();

		if (pwd.length() >= 8)
		{
			cout << "密码长度溢出！" << endl;
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
高容错输入金额
返回false标志用户取消操作
*/
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
bool confirmBalance(const double balance)  //此函数源于我买饭时工作人员多刷我11块，大家付钱时一定要看清楚！
{
	double confirmBalance;
	while (true)
	{
		cout << "请再次输入金额：";
		if (!inputSafeDouble(confirmBalance)) return false;

		if (fabs(confirmBalance - balance) > 0.1)
		{
			cout << "金额不匹配！" << endl;
			cout << HINT_REINPUT;

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
/*
账号登录函数
返回nullptr表示用户取消操作
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
			cout << "卡号不存在！" << endl;
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
					cout << "密码错误！" << endl;
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
高容错输入年份
返回false标志用户取消操作
*/
bool inputYear(int& year)
{
	while (true)
	{
		cout << "请输入年份：";
		if (!inputSafeInt(year)) return false;
		if (!isYear(year))
		{
			cout << "非法年份！" << endl;
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
高容错输入月份
返回false标志用户取消操作
*/
bool inputMonth(int& month)
{
	while (true)
	{
		cout << "请输入月份：";
		if (!inputSafeInt(month)) return false;
		if (!isMonth(month))
		{
			cout << "非法月份！" << endl;
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
高容错输入年份&月份
返回false标志用户取消操作
*/
bool inputYearMonth(int& sYear, int& sMonth, int& eYear, int& eMonth)
{
	cout << "请输入查询起始日期(左闭右开)" << endl;
	if (!inputYear(sYear) || !inputMonth(sMonth)) return false;
	cout << "请输入查询终止日期" << endl;
	if (!inputYear(eYear) || !inputMonth(eMonth)) return false;
	return true;
}

bool inputYearMonth(int& year, int& month)
{
	cout << "请输入查询日期" << endl;
	if (!inputYear(year) || !inputMonth(month)) return false;
	return true;
}

