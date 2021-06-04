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
        cout << endl << SPLITELINE << "��ӿ�" << SPLITELINE << endl << endl;
        addCard(cardvector_, infovector_, setting_);
        break;
    case '2':
        cout << endl << SPLITELINE << "��ѯ��" << SPLITELINE << endl << endl;
        displayCard(cardvector_, setting_);
        break;
    case '3':
        cout << endl << SPLITELINE << "�ϻ�" << SPLITELINE << endl << endl;
        cardSetUse(cardvector_, setting_);
        break;
    case '4':
        cout << endl << SPLITELINE << "�»�" << SPLITELINE << endl << endl;
        cardSetUnuse(cardvector_, infovector_, setting_);
        break;
    case '5':
        cout << endl << SPLITELINE << "��ֵ" << SPLITELINE << endl << endl;
        chargeCard(cardvector_, infovector_, setting_);
        break;
    case '6':
        cout << endl << SPLITELINE << "�˷�" << SPLITELINE << endl << endl;
        feeBack(cardvector_, infovector_, setting_);
        break;
    case '7':
        cout << endl << SPLITELINE << "��ѯͳ��" << SPLITELINE << endl << endl;
        searchInfo(infovector_, setting_);
        break;
    case '8':
        cout << endl << SPLITELINE << "ע����" << SPLITELINE << endl << endl;
        pauseCard(cardvector_, infovector_, setting_);
        break;
    case '9':
        cout << endl << SPLITELINE << "����" << SPLITELINE << endl << endl;
        settingInfo(setting_);
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
void menuInfo()
{
    cout << SPLITELINE << "�Ʒ�ϵͳ�˵�" << SPLITELINE << endl << endl;
    cout << "1.��ӿ�" << endl;
    cout << "2.��ѯ��" << endl;
    cout << "3.�ϻ�" << endl;
    cout << "4.�»�" << endl;
    cout << "5.��ֵ" << endl;
    cout << "6.�˷�" << endl;
    cout << "7.��ѯͳ��" << endl;
    cout << "8.ע����" << endl;
    cout << "9.����" << endl;
    cout << "0.�˳�" << endl << endl;
    cout << "��ѡ��˵����ţ�0~8����";
}
void searchInfo(infoVector& infovector_, setting& setting_)
{
    while (true)
    {
        cout << "1.���Ѽ�¼��ѯ" << endl;
        cout << "2.ͳ����Ӫҵ��" << endl;
        cout << "3.ͳ����Ӫҵ��" << endl;
        cout << "0.����" << endl << endl;
        cout << "��ѡ��˵����ţ�0~3����";

        char selection;
        cin >> selection;
        cinClear();
        cout << endl;

        if (selection == '0') return;

        searchCount(infovector_, selection, setting_);

        cout << SPLITELINE << "��ѯͳ��" << SPLITELINE << endl << endl;
    }
}
    
void settingInfo(setting& setting_)
{
    while (true) 
    {
        cout << "1.��·��" << endl;
        cout << "2.������¼·��" << endl;
        cout << "3.��־·��" << endl;
        cout << "4.�Ʒѵ�Ԫ" << endl;
        cout << "5.�շѱ�׼" << endl;
        cout << "6.�������" << endl;
        cout << "7.������־" << endl;
        cout << "0.����" << endl << endl;
        cout << "��ѡ��˵����ţ�0~7����";

        char selection;
        cin >> selection;
        cinClear();
        cout << endl;

        if (selection == '0') return;

        settings(setting_, selection);

        cout << SPLITELINE << "����" << SPLITELINE << endl << endl;
    }
}