#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <string>
#include <map>
#include <cmath>

using namespace std;
const int N = 50;

struct cours{
    string id;
    int sco;
}cou[N];

struct node{
    int idx,sco;
    node(int idx,int sco) :
        idx(idx),sco(sco) {}
    bool operator < (const node& ot) const{
        return sco > ot.sco;
    }
};

int term,scoLim,n;
int inc[N],ans[N];
vector <int> path[N];
map <string,int> simap;

int main(){
    //freopen("out.txt","w",stdout);
    string str;
    cin >> term >> scoLim >> n;
    for(int i = 0;i < n;i++){
        cin >> cou[i].id >> cou[i].sco >> str;
        simap[cou[i].id] = i;
        int pre = -1;
        if(str != "-1"){
            pre = simap[str];
            path[pre].push_back(i);
            inc[i]++;
        }
    }
    
    int cnt = 0;
    priority_queue <node> q;
    for(int i = 0;i < n;i++){
        if(inc[i] == 0) q.push(node(i,cou[i].sco));
    }
    while(!q.empty()){
        node cur = q.top();
        q.pop();

        ans[cnt++] = cur.idx;
        for(auto to : path[cur.idx]){
            inc[to]--;
            if(!inc[to]) q.push(node(to,cou[to].sco));
        }
    }
    bool isLegal = true;
    for(int i = 0;i < n && isLegal;i++){
        if(inc[i]) isLegal = false;
    }
    if(!isLegal){
        cout << "course conflict!\n";
        exit(0);
    }

    int mode = 0;
    cin >> mode;

    int curTerm = 2,sum = 0,tot = 0;
    cout << "term 1:\n";
    for(int i = 0;i < n;i++){
        sum += cou[ans[i]].sco;
        tot += 1;
        if(sum > scoLim || (mode && tot > ceil(n * 1.0 / term))){
            sum = cou[ans[i]].sco;
            tot = 1;
            cout << "term " << curTerm++ << ":\n";
        }
        cout << cou[ans[i]].id << endl;
    }
    while(curTerm <= term){
        cout << "term " << curTerm++ << ":\n"; 
    }
    //fclose(stdout);
    return 0;
}

/*
4 20 10
a1 2 -1
b2 1 -1
c3 5 a1
d4 7 b2
e5 3 b2
f6 5 d4
g7 6 e5
h8 1 a1
i9 2 -1
j10 3 i9
0
*/

/*
4 20 10
a1 2 -1
b2 1 -1
c3 5 a1
d4 7 b2
e5 3 b2
f6 5 d4
g7 6 e5
h8 1 a1
i9 2 -1
j10 3 i9
1
*/