#include <iostream>
#include"menu.h"
using namespace std;
int main()
{
    cardVector cardvector_;
    cout << "★欢迎进入计费管理系统★" << endl << endl; //进入系统提示
    while (true) //主程序死循环保护
    {
        if (!menu(cardvector_)) break;
    }
    return 0;
}