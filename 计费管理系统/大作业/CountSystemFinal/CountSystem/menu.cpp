#include "menu.h"
#include "transUtils.h"
#include "service.h"
#include "global.h"

using namespace std;

bool menu(cardVector& cardvector_, infoVector& infovector_, setting& setting_)
{
    menuInfo();

    char selection;
    cin >> selection;
    cinClear();

    switch (selection)
    {
    case '1':
        cout << endl << SPLITELINE << "添加卡" << SPLITELINE << endl << endl;
        addCard(cardvector_, infovector_, setting_);
        break;
    case '2':
        cout << endl << SPLITELINE << "查询卡" << SPLITELINE << endl << endl;
        displayCard(cardvector_, setting_);
        break;
    case '3':
        cout << endl << SPLITELINE << "上机" << SPLITELINE << endl << endl;
        cardSetUse(cardvector_, setting_);
        break;
    case '4':
        cout << endl << SPLITELINE << "下机" << SPLITELINE << endl << endl;
        cardSetUnuse(cardvector_, infovector_, setting_);
        break;
    case '5':
        cout << endl << SPLITELINE << "充值" << SPLITELINE << endl << endl;
        chargeCard(cardvector_, infovector_, setting_);
        break;
    case '6':
        cout << endl << SPLITELINE << "退费" << SPLITELINE << endl << endl;
        feeBack(cardvector_, infovector_, setting_);
        break;
    case '7':
        cout << endl << SPLITELINE << "查询统计" << SPLITELINE << endl << endl;
        searchInfo(infovector_, setting_);
        break;
    case '8':
        cout << endl << SPLITELINE << "注销卡" << SPLITELINE << endl << endl;
        pauseCard(cardvector_, infovector_, setting_);
        break;
    case '9':
        cout << endl << SPLITELINE << "设置" << SPLITELINE << endl << endl;
        settingInfo(setting_);
        break;
    case '0':
        cout << endl << SPLITELINE << "欢迎下次使用" << SPLITELINE << endl << endl;
        return false;
        break;
    default:
        cout << endl << "非法输入" << endl << endl;
        break;
    }
    return true;
}
void menuInfo()
{
    cout << SPLITELINE << "计费系统菜单" << SPLITELINE << endl << endl;
    cout << "1.添加卡" << endl;
    cout << "2.查询卡" << endl;
    cout << "3.上机" << endl;
    cout << "4.下机" << endl;
    cout << "5.充值" << endl;
    cout << "6.退费" << endl;
    cout << "7.查询统计" << endl;
    cout << "8.注销卡" << endl;
    cout << "9.设置" << endl;
    cout << "0.退出" << endl << endl;
    cout << "请选择菜单项编号（0~8）：";
}
void searchInfo(infoVector& infovector_, setting& setting_)
{
    while (true)
    {
        cout << "1.消费记录查询" << endl;
        cout << "2.统计总营业额" << endl;
        cout << "3.统计月营业额" << endl;
        cout << "0.返回" << endl << endl;
        cout << "请选择菜单项编号（0~3）：";

        char selection;
        cin >> selection;
        cinClear();
        cout << endl;

        if (selection == '0') return;

        searchCount(infovector_, selection, setting_);

        cout << SPLITELINE << "查询统计" << SPLITELINE << endl << endl;
    }
}
    
void settingInfo(setting& setting_)
{
    while (true) 
    {
        cout << "1.卡路径" << endl;
        cout << "2.操作记录路径" << endl;
        cout << "3.日志路径" << endl;
        cout << "4.计费单元" << endl;
        cout << "5.收费标准" << endl;
        cout << "6.余额限制" << endl;
        cout << "7.开启日志" << endl;
        cout << "0.返回" << endl << endl;
        cout << "请选择菜单项编号（0~7）：";

        char selection;
        cin >> selection;
        cinClear();
        cout << endl;

        if (selection == '0') return;

        settings(setting_, selection);

        cout << SPLITELINE << "设置" << SPLITELINE << endl << endl;
    }
}