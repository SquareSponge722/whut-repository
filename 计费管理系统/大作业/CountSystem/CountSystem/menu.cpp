#include "menu.h"
#include "utils.h"
#include "service.h"
#include "global.h"

using namespace std;

void menuInfo()
{
    cout << endl << SPLITELINE << "�Ʒ�ϵͳ�˵�" << SPLITELINE << endl << endl;
    cout << "1.��ӿ�" << endl;
    cout << "2.��ѯ��" << endl;
    cout << "3.�ϻ�" << endl;
    cout << "4.�»�" << endl;
    cout << "5.��ֵ" << endl;
    cout << "6.�˷�" << endl;
    cout << "7.��ѯͳ��" << endl;
    cout << "8.ע����" << endl;
    cout << "0.�˳�" << endl << endl;
    cout << "��ѡ��˵����ţ�0~8����";
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
        cout << endl << SPLITELINE << "��ӿ�" << SPLITELINE << endl << endl;
        addCard(cardvector_);
        break;
    case '2':
        cout << endl << SPLITELINE << "��ѯ��" << SPLITELINE << endl << endl;
        displayCard(cardvector_);
        break;
    case '3':
        cout << endl << SPLITELINE << "�ϻ�" << SPLITELINE << endl << endl;
        break;
    case '4':
        cout << endl << SPLITELINE << "�»�" << SPLITELINE << endl << endl;
        break;
    case '5':
        cout << endl << SPLITELINE << "��ֵ" << SPLITELINE << endl << endl;
        break;
    case '6':
        cout << endl << SPLITELINE << "�˷�" << SPLITELINE << endl << endl;
        break;
    case '7':
        cout << endl << SPLITELINE << "��ѯͳ��" << SPLITELINE << endl << endl;
        break;
    case '8':
        cout << endl << SPLITELINE << "ע����" << SPLITELINE << endl << endl;
        pauseCard(cardvector_);
        break;
    case '0':
        cout << endl << SPLITELINE << "��ӭ�´�ʹ��" << SPLITELINE << endl << endl;
        return false;
        break;
    default:
        cout << endl << "�Ƿ�����" << endl << endl;
        break;
    }
    return true;
}