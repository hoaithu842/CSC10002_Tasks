#include <iostream>
using namespace std;

struct DNode{
    int data;
    DNode *next;
    DNode *prev;
};
struct DList{
    DNode *head;
    DNode *tail;
};

void initialize(DList &l){
    l.head = NULL;
    l.tail = NULL;
}
bool checkEmpty(DList l){
    if (l.head==NULL) return 1;
    return 0;
}


DNode *findIthElement(DList l, int i){
    if (l.head==NULL) return NULL;
    int count=0;
    for (DNode *p = l.head; p; p=p->next){
        if (count==i) return p;
        count++;
    }
    return NULL;
}
DNode *findElementX(DList l, int data){
    if (l.head==NULL) return NULL;
    for (DNode *p = l.head; p; p=p->next){
        if (p->data==data) return p;
    }
    return NULL;
}
DNode *findLastElement(DList l){
    if (l.head==NULL && l.tail==NULL) return NULL;
    return l.tail;
}


DNode *makeNode(int data){
    DNode *newNode = new DNode;
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}
void addHead(DList &l, int data){
    DNode *newNode = makeNode(data);
    if (l.head==NULL || l.head==NULL){
        l.head = newNode;
        l.tail = newNode;
        return;
    }
    newNode->next = l.head;
    (l.head)->prev = newNode;
    l.head = newNode;
}
void addTail(DList &l, int data){
    if (l.tail==NULL){
        addHead(l, data);
        return;
    }
    DNode *p = makeNode(data);
    p->prev = l.tail;
    (l.tail)->next = p;
    l.tail = p;
}
void addMiddleIth(DList &l, int data, int i){
    if (l.head==NULL || l.tail==NULL) return;
    DNode *tmp = findIthElement(l, i);
        if (tmp==NULL) return;
        if (tmp==l.tail){
            addTail(l, data);
            return;
        }
    DNode *newNode = makeNode(data);
        newNode->next = tmp->next;
        (tmp->next)->prev = newNode;
        tmp->next = newNode;
        newNode->prev = tmp;
}
void addOrder(DList &l, int data){
    if (l.head==NULL || l.head->data>data){
        addHead(l, data);
        return;
    }
    for (DNode *p = l.head; p; p=p->next){
        if (p!=l.tail && p->data<=data && p->next->data>=data){
            DNode *newNode = makeNode(data);
            newNode->next = p->next;
            p->next->prev = newNode;
            newNode->prev = p;
            p->next = newNode;
            return;
        }
    }
    addTail(l, data);
}


void removeHead(DList &l){
    if (l.head==NULL) return;
    DNode *tmp = l.head;
    if (l.head->next==NULL) {
        l.head = NULL;
        l.tail = NULL;
        delete tmp;
        return;
    }
    (l.head->next)->prev = NULL;
    l.head = l.head->next;
    delete tmp;
}
void removeTail(DList &l){
    if (l.head==NULL || l.tail==NULL) return;
    if (l.tail->prev==NULL){
        removeHead(l);
        return;
    }
    DNode *tmp = l.tail;
    (l.tail->prev)->next = NULL;
    l.tail = (l.tail)->prev;
    delete tmp;
}
void removeIthElement(DList &l, int i){
    if (l.head==NULL || l.tail==NULL) return;
    DNode *p = findIthElement(l, i);
    if (p==NULL) return;
    if (p==l.head){
        removeHead(l);
        return;
    }
    if (p==l.tail){
        removeTail(l);
        return;
    }
    (p->prev)->next = p->next;
    (p->next)->prev = p->prev;
    delete p;
}
void removeElementX(DList &l, int data){
    if (l.head==NULL || l.tail==NULL) return;
    for (DNode *p = l.head; p; p=p->next){
        if (p->data==data){
            if (p==l.head) removeHead(l);
            else if (p==l.tail) removeTail(l);
            else{
                DNode *tmp = p;
                (p->prev)->next = p->next;
                (p->next)->prev = p->prev;
                delete tmp;
            }
        }
    }
}
void removeAll(DList &l){
    if (l.head==NULL || l.tail==NULL) return;
    for (DNode *p = l.head; p; p=p->next) removeHead(l);
}



int main(){
    DList l;
    initialize(l);
    DNode a, b, c, d, e;
    
    l.head = &a;    l.tail = &e;
    a.next = &b;    a.prev = NULL;  a.data = 1;
    b.next = &c;    b.prev = &a;    b.data = 2;
    c.next = &d;    c.prev = &b;    c.data = 3;
    d.next = &e;    d.prev = &c;    d.data = 4;
    e.next = NULL;  e.prev = &d;    e.data = 5;
    
    removeAll(l);
    return 0;
}
