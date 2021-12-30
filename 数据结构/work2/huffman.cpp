#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <string>

using namespace std;
const int N = 50;

struct tree{
    char data;
    double freq;
    int lson,rson;
    tree() : lson(-1),rson(-1) {}
    tree(double freq,int lson,int rson) :
        freq(freq),lson(lson),rson(rson) {}
}tre[N];

struct node{
    int idx;
    double freq;
    node() {}
    node(int idx,double freq) :
        idx(idx),freq(freq) {}
    bool operator < (const node& ot)const{
        return freq > ot.freq;
    }
};

int n,tot;
double arr[N];
string ans[N];

void dfs(int,int,int);

int main(){
    double t;
    priority_queue <node> q;
    cin >> n;
    for(int i = 0;i < n;i++){
        cin >> tre[tot].freq;
        tre[tot].data = i + 'a';
        q.push(node(tot,tre[tot].freq));
        tot++;
    }
    node root;
    while(!q.empty()){
        root = q.top();
        q.pop();
        if(q.empty()) break;
        node sec = q.top();
        q.pop();

        tre[tot] = tree(root.freq + sec.freq,root.idx,sec.idx);
        q.push(node(tot,tre[tot].freq));
        tot++;
    }
    dfs(root.idx,-1,-1);
    for(int i = 0;i < n;i++){
        cout << (char)('a' + i) << " : " << ans[i] << endl;
    }
    return 0;
}

void dfs(int cur,int fa,int sid){
    if(fa != -1) ans[cur] = ans[fa] + (sid == 1 ? "1" : "0");
    if(tre[cur].lson != -1) dfs(tre[cur].lson,cur,1);
    if(tre[cur].rson != -1) dfs(tre[cur].rson,cur,0);
}