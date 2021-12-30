#include <bits/stdc++.h>
using namespace std;

#define lson(k) (k << 1)
#define rson(k) (k << 1 | 1)

const int N = 1024;
const int MOCK_N = 10;

int mock[MOCK_N] = {45,33,59,28,128,256,9,3,234,1024};

int quickArr[N],quickN;

int heapTree[N],heapN;
bool heapUsed[N];

int mergeArr[N],mergeN;

inline void printArr(int arr[],int len){
    for(int i = 0;i < len;i++) printf("%d ",arr[i]);
    printf("\n");
}

void insertSort(int arr[],int len);
void shellSort(int arr[],int len);
void bubbleSort(int arr[],int len);
void quickSort(int arr[],int len);
void quickDfs(int l,int r);
void selectSort(int arr[],int len);
void heapSort(int arr[],int len);
void heapInsert(int val);
int heapPop();
void mergeSort(int arr[],int len);
void mergeDfs(int l,int r);
void radixSort(int arr[],int len);
int qpow(int x,int y);

void show(int arr[],int len);

int main(){
    show(mock,MOCK_N);
    return 0;
}

void show(int arr[],int len){
    printf("insertSort:\n");
    insertSort(arr,len);
    printf("shellSort:\n");
    shellSort(arr,len);
    printf("bubbleSort:\n");
    bubbleSort(arr,len);
    printf("quickSort:\n");
    quickSort(arr,len);
    printf("selectSort:\n");
    selectSort(arr,len);
    printf("heapSort:\n");
    heapSort(arr,len);
    printf("mergeSort:\n");
    mergeSort(arr,len);
    printf("radixSort:\n");
    radixSort(arr,len);
}

void insertSort(int arr[],int len){
    int n = 0;
    int list[N];
    for(int i = 0;i < len;i++){
        int pos = n;
        while(pos && list[pos - 1] > arr[i]){
            list[pos] = list[pos - 1];
            pos--;
        }
        list[pos] = arr[i];
        n++;

        printArr(list,n);
    }
}

void shellSort(int arr[],int len){
    int step = len >> 1;
    while(step){
        for(int i = step;i < len;i++){
            int pos = i;
            while(pos - step >= 0 && arr[pos - step] > arr[pos]){
                swap(arr[pos - step],arr[pos]);
                pos -= step;
            }
        }
        step >>= 1;

        printArr(arr,len);
    }
}

void bubbleSort(int arr[],int len){
    for(int i = len;i > 0;i--){
        for(int j = 0;j < i;j++)
            if(arr[j] < arr[j - 1]) swap(arr[j],arr[j - 1]);
        
        printArr(arr,len);
    }
}

void quickSort(int arr[],int len){
    quickN = len;
    for(int i = 0;i < len;i++) quickArr[i] = arr[i];
    quickDfs(0,len - 1);
}
void quickDfs(int l,int r){
    if(l >= r) return;
    int divider = quickArr[l];
    int s = l,t = r;
    while(s < t){
        while(s < t && quickArr[t] > divider) t--;
        quickArr[s] = quickArr[t];
        while(s < t && quickArr[s] < divider) s++;
        quickArr[t] = quickArr[s];
    }
    quickArr[s] = divider;

    printArr(quickArr,quickN);

    quickDfs(l,s);
    quickDfs(s + 1,r);
}

void selectSort(int arr[],int len){
    for(int i = 0;i < len;i++){
        int pos = i;
        for(int j = i + 1;j < len;j++)
            if(arr[j] < arr[pos]) pos = j;
        swap(arr[i],arr[pos]);

        printArr(arr,len);
    }
}

void heapSort(int arr[],int len){
    memset(heapUsed,0,sizeof(heapUsed));
    for(int i = 0;i < len;i++) heapInsert(arr[i]);
    for(int i = 0;i < len;i++) printf("%d ",heapPop());
    printf("\n");
}
void heapInsert(int val){
    heapTree[++heapN] = val;
    heapUsed[heapN] = true;
    int cur = heapN;
    int fa = cur >> 1;
    while(fa && heapTree[fa] > heapTree[cur]){
        swap(heapTree[fa],heapTree[cur]);
        cur = fa;
        fa = cur >> 1;
    }

    printArr(heapTree,heapN);
}
int heapPop(){
    int res = heapTree[1];
    int cur = 1;
    while(heapUsed[lson(cur)] || heapUsed[rson(cur)]){
        heapUsed[cur] = true;
        if(heapUsed[lson(cur)] && heapUsed[rson(cur)]){
            if(heapTree[lson(cur)] > heapTree[rson(cur)]){
                heapTree[cur] = heapTree[rson(cur)];
                cur = rson(cur);
            } else {
                heapTree[cur] = heapTree[lson(cur)];
                cur = lson(cur);
            }
        } else if(heapUsed[lson(cur)]) {
            heapTree[cur] = heapTree[lson(cur)];
            cur = lson(cur);
        } else {
            heapTree[cur] = heapTree[rson(cur)];
            cur = rson(cur);
        }
        heapUsed[cur] = false;
    }
    return res;
}

void mergeSort(int arr[],int len){
    mergeN = len;
    for(int i = 0;i < len;i++) mergeArr[i] = arr[i];
    mergeDfs(0,mergeN - 1);
}
void mergeDfs(int l,int r){
    if(l >= r) return;
    int mid = (l + r) >> 1;
    mergeDfs(l,mid);
    mergeDfs(mid + 1,r);
    queue<int> q1,q2;
    for(int i = l;i <= r;i++){
        if(i <= mid) q1.push(mergeArr[i]);
        else q2.push(mergeArr[i]);
    }
    for(int i = l;i <= r;i++){
        if(q2.empty() || (!q1.empty() && q1.front() < q2.front())){
            mergeArr[i] = q1.front();
            q1.pop();
        } else {
            mergeArr[i] = q2.front();
            q2.pop();
        }
    }

    printArr(mergeArr,mergeN);
}

void radixSort(int arr[],int len){
    queue <int> q[10];
    int bit = 0;
    for(int i = 0;i < len;i++){
        int tmp = 1,cur = arr[i];
        while(cur / 10){
            tmp++;
            cur /= 10;
        }
        bit = max(bit,tmp);
    }
    for(int i = 0;i < bit;i++){
        for(int j = 0;j < len;j++){
            int tt = (arr[j] % qpow(10,i + 1)) / qpow(10,i);
            q[(arr[j] % qpow(10,i + 1)) / qpow(10,i)].push(arr[j]);
        }
        int pos = 0;
        for(int j = 0;j < 10;j++){
            while(!q[j].empty()){
                arr[pos++] = q[j].front();
                q[j].pop();
            }
        }

        printArr(arr,len);
    }
}
int qpow(int x,int y){
    int res = 1;
    while(y){
        if(y & 1) res = res * x;
        x = x * x;
        y >>= 1;
    }
    return res;
}