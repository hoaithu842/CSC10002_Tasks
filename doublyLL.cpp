
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
    l.head = nullptr;
    l.tail = nullptr;
}
bool checkEmpty(DList l){
    if (l.head==nullptr) return 1;
    return 0;
}

DNode *findIthElement(DList l, int i){
    if (l.head==nullptr) return nullptr;
    int count=0;
    for (DNode *p = l.head; p; p=p->next){
        if (count==i) return p;
        count++;
    }
    return nullptr;
}
DNode *findElementX(DList l, int data){
    if (l.head==nullptr) return nullptr;
    for (DNode *p = l.head; p; p=p->next){
        if (p->data==data) return p;
    }
    return nullptr;
}
DNode *findLastElement(DList l){
    if (l.head==nullptr && l.tail==nullptr) return nullptr;
    return l.tail;
}

DNode *makeNode(int data){
    DNode *newNode = new DNode;
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return newNode;
}
void addHead(DList &l, int data){
    DNode *newNode = makeNode(data);
    if (l.head==nullptr || l.head==nullptr){
        l.head = newNode;
        l.tail = newNode;
        return;
    }
    newNode->next = l.head;
    (l.head)->prev = newNode;
    l.head = newNode;
}
void addTail(DList &l, int data){
    if (l.tail==nullptr){
        addHead(l, data);
        return;
    }
    DNode *p = makeNode(data);
    p->prev = l.tail;
    (l.tail)->next = p;
    l.tail = p;
}
void addMiddleIth(DList &l, int data, int i){
    if (l.head==nullptr || l.tail==nullptr) return;
    DNode *tmp = findIthElement(l, i);
        if (tmp==nullptr) return;
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
    if (l.head==nullptr || l.head->data>data){
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
    if (l.head==nullptr) return;
    DNode *tmp = l.head;
    if (l.head->next==nullptr) {
        l.head = nullptr;
        l.tail = nullptr;
        delete tmp;
        return;
    }
    (l.head->next)->prev = nullptr;
    l.head = l.head->next;
    delete tmp;
}
void removeTail(DList &l){
    if (l.head==nullptr || l.tail==nullptr) return;
    if (l.tail->prev==nullptr){
        removeHead(l);
        return;
    }
    DNode *tmp = l.tail;
    (l.tail->prev)->next = nullptr;
    l.tail = (l.tail)->prev;
    delete tmp;
}
void removeIthElement(DList &l, int i){
    if (l.head==nullptr || l.tail==nullptr) return;
    DNode *p = findIthElement(l, i);
    if (p==nullptr) return;
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
    if (l.head==nullptr || l.tail==nullptr) return;
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
    DNode *p = l.head;
    while (p!=nullptr){
        DNode *tmp = p;
        p = p->next;
        if (p!=nullptr) p->prev = nullptr;
        l.head = p;
        delete tmp;
    }
}
int main(){
    DList l;
    initialize(l);
    DNode a, b, c, d, e;
    
    l.head = &a;    l.tail = &e;
    a.next = &b;    a.prev = nullptr;  a.data = 1;
    b.next = &c;    b.prev = &a;    b.data = 2;
    c.next = &d;    c.prev = &b;    c.data = 3;
    d.next = &e;    d.prev = &c;    d.data = 4;
    e.next = nullptr;  e.prev = &d;    e.data = 5;
    
    removeAll(l);
    if (l.head==nullptr) cout << "removed";
    return 0;
}
