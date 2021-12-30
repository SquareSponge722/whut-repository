#include <cstdio>
#include <cstdlib>

using namespace std;

struct node{
    int expn;
    double coef;
    node* next;
    node() {
        expn = coef = 0;
        next = NULL;
    }
    node(int expn,double coef) :
        expn(expn),coef(coef) {
            next = NULL;
        }
};

struct poly{
    node* head;
    poly(){
        head = new node();
    }
    void insert(node* nod){
        node* cur = head;
        while(cur->next != NULL){
            if(cur->next->expn == nod->expn){
                cur->next->coef += nod->coef;
                return ;
            }else if(cur->next->expn > nod->expn){
                break;
            }
            cur = cur->next;
        }
        nod->next = cur->next;
        cur->next = nod;
    }
    void add(poly* pol){
        node* last = head;
        node* pos1 = head->next;
        node* pos2 = pol->head->next;
        while(pos1 != NULL && pos2 != NULL){
            if(pos1->expn == pos2->expn){
                pos1->coef += pos2->coef;
                last = pos1;
                pos1 = pos1->next;
                pos2 = pos2->next;
            }else if(pos1->expn < pos2->expn){
                last = pos1;
                pos1 = pos1->next;
            }else{
                node* tmp = new node(pos2->expn,pos2->coef);
                tmp->next = last->next;
                last->next = tmp;
                pos2 = pos2->next;
            }
        }
        while(pos2 != NULL){
            node* tmp = new node(pos2->expn,pos2->coef);
            last->next = tmp;
            pos2 = pos2->next;
        }
    }
    void sub(poly* pol){
        node* last = head;
        node* pos1 = head->next;
        node* pos2 = pol->head->next;
        while(pos1 != NULL && pos2 != NULL){
            if(pos1->expn == pos2->expn){
                pos1->coef -= pos2->coef;
                last = pos1;
                pos1 = pos1->next;
                pos2 = pos2->next;
            }else if(pos1->expn < pos2->expn){
                last = pos1;
                pos1 = pos1->next;
            }else{
                node* tmp = new node(pos2->expn,-pos2->coef);
                tmp->next = last->next;
                last->next = tmp;
                pos2 = pos2->next;
            }
        }
        while(pos2 != NULL){
            node* tmp = new node(pos2->expn,-pos2->coef);
            last->next = tmp;
            pos2 = pos2->next;
        }
    }
    void print(){
        node* cur = head->next;
        while(cur != NULL){
            printf("%.2lfX^%d ",cur->coef,cur->expn);
            cur = cur->next;
        }
        printf("\n");
    }
    void del(){
        node* cur = head->next;
        while(cur != NULL){
            node* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
        free(head);
    }
}p1,p2;

int n,m;

int main(){
    int ex;
    double co;
    scanf("%d %d",&n,&m);
    for(int i = 0;i < n;i++){
        scanf("%lf %d",&co,&ex);
        node* tmp = new node(ex,co);
        p1.insert(tmp);
    }
    for(int i = 0;i < m;i++){
        scanf("%lf %d",&co,&ex);
        node* tmp = new node(ex,co);
        p2.insert(tmp);
    }
    p1.add(&p2);
    p1.print();
    p2.print();
    p1.del();
    p2.del();
    return 0;
}