#include <cstdio>
#include <cstdlib>

using namespace std;
const int N = 1e5 + 10;

struct List{
    int arr[N];
    int n;
    void init(){
        for(int i = 0;i < n;i++){
            arr[i] = i + 1;
        }
    }
    void del(int pos){
        if(pos >= n || pos < 0) return;
        for(;pos + 1 < n;pos++){
            arr[pos] = arr[pos + 1];
        }
        n--;
    }
}list;

int m;

int main(){
    scanf("%d %d",&list.n,&m);
    list.init();
    int t = 0;
    while(list.n){
        t = (t + m - 1) % list.n;
        printf("%d ",list.arr[t]);
        list.del(t);
    }
    return 0;
}