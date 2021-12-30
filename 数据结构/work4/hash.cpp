#include <bits/stdc++.h>
using namespace std;

const int MOD = 23;
const int N = 128;

string name[10] = {"XiaoMing","ZhangSan","LiSi","ErGou","WangWu",
                "Yanzi","LuYiSi","LiuJiangJun","SiShen","XiaoChou"};

string store[N];

int strHash(const string& str){
    int res = 1;
    for(auto ch: str){
        res = (res + (ch - 'A')) % MOD;
    }
    return res;
}

void pushStr(const string& str){
    int pos = strHash(str),cnt = 0;
    while(!store[pos].empty()){
        pos++;
        cnt++;
        if(cnt > N) return;
        pos %= N;
    }
    store[pos] = str;
}

int findStr(const string& str){
    int pos = strHash(str),cnt = 0;
    while(store[pos] != str){
        pos++;
        cnt++;
        if(cnt > N) return -1;
        pos %= N;
    }
    return pos;
}

int main(){
    for(auto s: name) pushStr(s);
    for(auto s: name){
        cout << strHash(s) << "  " << findStr(s) << endl;
    }
    return 0;
}