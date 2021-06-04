#include "menu.h"
#include "utils.h"
#include "service.h"
#include "global.h"

using namespace std;

void menuInfo()
{
    cout << endl << SPLITELINE << "计费系统菜单" << SPLITELINE << endl << endl;
    cout << "1.添加卡" << endl;
    cout << "2.查询卡" << endl;
    cout << "3.上机" << endl;
    cout << "4.下机" << endl;
    cout << "5.充值" << endl;
    cout << "6.退费" << endl;
    cout << "7.查询统计" << endl;
    cout << "8.注销卡" << endl;
    cout << "0.退出" << endl << endl;
    cout << "请选择菜单项编号（0~8）：";
}
bool menu(cardVector& cardvector_)
{
    menuInfo();

    char selection;
    cin >> selection;
    //cin.clear();
    cinClear();

    switch (selection)
    {
    case '1':
        cout << endl << SPLITELINE << "添加卡" << SPLITELINE << endl << endl;
        addCard(cardvector_);
        break;
    case '2':
        cout << endl << SPLITELINE << "查询卡" << SPLITELINE << endl << endl;
        displayCard(cardvector_);
        break;
    case '3':
        cout << endl << SPLITELINE << "上机" << SPLITELINE << endl << endl;
        break;
    case '4':
        cout << endl << SPLITELINE << "下机" << SPLITELINE << endl << endl;
        break;
    case '5':
        cout << endl << SPLITELINE << "充值" << SPLITELINE << endl << endl;
        break;
    case '6':
        cout << endl << SPLITELINE << "退费" << SPLITELINE << endl << endl;
        break;
    case '7':
        cout << endl << SPLITELINE << "查询统计" << SPLITELINE << endl << endl;
        break;
    case '8':
        cout << endl << SPLITELINE << "注销卡" << SPLITELINE << endl << endl;
        pauseCard(cardvector_);
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