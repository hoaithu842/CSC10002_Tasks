#include <iostream>
using namespace std;

struct SNode{
    int data;
    SNode *next;
};
struct SList{
    SNode *head;
};

void initialize(SList &l){      //void initialize(SList *l){
    l.head = NULL;              //(*l).head = NULL;
}
bool checkEmpty(SList l){       //bool empty(SList *l){
    if (l.head==NULL) return 1; //return ((*l).head==NULL);
    else return 0;
}


SNode *findIthElement(SList l, int i){
    if (l.head==NULL) return NULL;
    int count = 0;
    for (SNode *p = l.head; p; p=p->next){
        if (count==i) return p;
        count++;
    }
    return NULL;
}
SNode *findElementEqualsX(SList l, int data){
    if (l.head==NULL) return NULL;
    for (SNode *p = l.head; p; p=p->next){
        if (p->data==data) return p;
    }
    return NULL;
}
SNode *findLastElement(SList l){
    if (l.head==NULL) return NULL;
    for (SNode *p = l.head; p; p=p->next){
        if (p->next==NULL) return p;
    }
    return NULL;
}


SNode *makeNode(int data){
    SNode *newNode = new SNode;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
void addHead(SList &l, int data){
    SNode *newNode = makeNode(data);
    newNode->next = l.head;
    l.head = newNode;
}
void addTail(SList &l, int data){
    if (l.head==NULL){
        addHead(l, data);
        return;
    }
    SNode *tail = findLastElement(l);
    tail->next = makeNode(data);    //(*tail).next = makeNode(data);   
}
void addMiddleIth(SList &l, int data, int i){
    if (l.head==NULL) return;
    SNode *tmp = findIthElement(l, i);
        if (tmp==NULL) return;
    SNode *newNode = makeNode(data);
        newNode->next = tmp->next;
        tmp->next = newNode;
}
void addOrder(SList &l, int data){
    if (l.head==NULL || l.head->data>data){
        addHead(l, data);
        return;
    }
    SNode *newNode = makeNode(data);
    for (SNode *p=l.head; p->next; p=p->next){
        if (p->data<=data && (*p->next).data>=data){
            newNode->next = p->next;
            p->next = newNode;
            return;
        }
    }
    addTail(l, data);
}


void removeHead(SList &l){
    if (l.head==NULL) return;
    SNode *tmp = l.head;
    l.head = tmp->next;
    delete tmp;
}
void removeTail(SList &l){
    if (l.head==NULL) return;
    if (l.head->next==NULL){
        removeHead(l);
        return;
    }
    SNode *p = l.head;
    for (p = l.head; p; p = p->next){
        if (p->next->next==NULL) break;
    }
    SNode *tmp = p->next->next;
    p->next = NULL;
    delete tmp;
}
void removeIthElement(SList &l, int i){
    if (i==0){
        removeHead(l);
        return;
    }
    SNode *p = findIthElement(l, i-1);
    SNode *tmp = p->next;
    p->next = (p->next)->next;
    delete tmp;
}
void removeElementEqualsX(SList &l, int data){
    if (l.head==NULL) return;
    SNode *prev = NULL;
    for (SNode *p = l.head; p; p=p->next){
        if (p->data==data){
            if (p==l.head) removeHead(l);
            else{
                SNode *tmp = p;
                prev->next = p->next;
                delete tmp;
            }
        } else prev = p;
    }
}
void removeAll(SList &l){
    if (l.head==NULL) return;
    for (SNode *p = l.head; p; p=p->next) removeHead(l);
}


int main(){
    SList l;
    initialize(l);
    SNode a, b, c, d, e;
    
    l.head = &a;
    a.next = &b;    a.data = 1;
    b.next = &c;    b.data = 2;
    c.next = &d;    c.data = 3;
    d.next = &e;    d.data = 4;
    e.next = NULL;  e.data = 5;

    removeAll(l);
    return 0;
}
