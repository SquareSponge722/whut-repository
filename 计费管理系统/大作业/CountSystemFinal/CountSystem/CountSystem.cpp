#include <iostream>
#include "menu.h"
#include "cardList.h"
#include "setting.h"
using namespace std;
int main()
{  
    setting& setting_ = setting::getInstance();
    cardVector& cardvector_ = cardVector::getInstance();
    infoVector& infovector_ = infoVector::getInstance();
    cout << "★欢迎进入计费管理系统★" << endl << endl;
    while (true)
    {
        if (!menu(cardvector_,infovector_,setting_)) break;
    }
    return 0;
}