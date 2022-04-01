#include <iostream>
using namespace std;
struct SNode{
    int data;
    SNode *next;
};
struct SList{
    SNode *head;
};
/*struct DNode{
    int data;
    DNode *next;
    DNode *prev;
};
struct DList{
    DNode *head;
    DNode *tail;
};
*/
void initialize(SList &l){
    l.head = NULL;
}
bool checkEmpty(SList l){
    if (l.head==NULL) return 1;
    else return 0;
}
/*          C
void init(SList *l){
    (*l).head = NULL;
}
bool empty(SList l){
    return ((*l).head==NULL);
}
*/
int findIthElement(SList l, int i){
    SNode *temp = l.head;
    int count = 0;
    while (count!=i){
        count++;
        temp = (*temp).next;
        if ((*temp).next==NULL && i!=count) return -1;
    }
    return (*temp).data;
}
int findElementHasDataX(SList l, int element/*, */){
    SNode *temp = l.head;
    int count = 0;
    bool stop;
    while (!stop){
        if ((*temp).data==element) return count;
        if ((*temp).next==NULL) return -1;
            count++;
            temp = (*temp).next;
    }
    return -1;
}
SNode *findEX(SList l, int element){
    SNode *temp = l.head;
    if (temp==NULL) return temp;
    while ((*temp).data!=element){
        temp = (*temp).next;
        if (temp==NULL) return temp;
    }
    return temp;
    
}
int findLastElement(SList l){
    SNode *temp = l.head;
    while ((*temp).next!=NULL){
        temp = (*temp).next;
    }
    return (*temp).data;    
}
/*void addHead(SList &l, int element){
    SNode temp;
    temp.data = element;
    temp.next = l.head;

    l.head = &temp;
}*/
SNode *makeNode(int data){
    SNode *newNode = new SNode;
    newNode->data = data;
    newNode->next = NULL;
}
void addHead(SList &l, int data){
    SNode *p = makeNode(data);
    p->next = l.head;
    l.head = p;
}
/*void addHead(SList &l, int data){
    SNode temp;
    temp.data = data;
    temp.next = l.head;

    l.head = &temp;
    //element.next = l.head;
    //l.head = &element;
}*/
/*void addTail(SList &l, SNode element){
    SNode *temp = lastElement(l);
    element.next = NULL;
    (*temp).next = &element;    
}*/
SNode *lastElement(SList l){
    for (SNode *p = l.head; p; p = p->next){
        if (p->next==NULL) return p;
    }
    return NULL;
}
void addTail(SList &l, int data){
    if (l.head==NULL){
        addHead(l, data);
        return;
    }
    
    SNode *temp = lastElement(l);
    SNode *p = makeNode(data);

    (*temp).next = p;
    // ~(*temp).next = makeNode(data);


    //SNode tmp;
    
    //tmp.next = NULL;
    //(*temp).next = &tmp;    
}
void addMiddleIth(SList &l, int data, int i){

    //~addTail w findI;
    SNode *newNode = makeNode(data);
    int count = 0;
    for (SNode *p = l.head; p; p=p->next){
        count++;
        if (count==i){
            newNode->next = p->next;
            p->next = newNode;
            return;
        }
    }
}
// gcc -x c
// g++ (gcc -x c++)
void addOrder(SList &l, int data){
    SNode *newNode = makeNode(data);
    for (SNode *p=l.head; p; p=p->next){
        if (p->data<=data && (*p->next).data>=data){
            newNode->next = p->next;
            p->next = newNode;
            return;
        }
    }
}
void removeHead(SList &l){
    //sc: empty list
    
    if (l.head==NULL) return;
    SNode *tmp = l.head;
    l.head = tmp->next;
    delete tmp;
    //l.head = l.head->next;
    //delete l.head;
}
void removeTail(SList &l){
    if (l.head==NULL) return;

    SNode *p = l.head;
    for (p = l.head; p; p = p->next){
        if (p->next->next==NULL) break;
        //if (p->next==NULL);// return p;
    }

    SNode *tmp = p->next->next;
    p->next = NULL;
    delete tmp;
}
void removeMiddleI(SList &l, int i){
    SNode *p = l.head;
    int count = 0;
    for (p = l.head; p; p=p->next){
        if (count==i-1){
            break;
        }
        count++;
    }
    SNode *tmp = p->next->next;
    p->next = p->next->next;
    delete tmp;
}
void getPrev(SList l){ //removeTail
    SNode *prev = NULL;
    if (l.head==NULL) return;
    if (l.head->next==NULL) removeHead(l);
    else
        for (SNode *p= l.head; p; p=p->next){
            if (p->next==NULL){             //==x
                prev->next = p->next;       //neu ptu la head => removeHead
                delete p;                   //i==0 => removeHead
                return;                     //la ptu duy nhat => ...
            }
            prev = p;
        }
}
int main(){
    SList l;
    initialize(l);
    SNode a, b, c, d;
    
    l.head = &a;
    a.next = &b;    a.data = 1;
    b.next = &c;    b.data = 2;
    c.next = &d;    c.data = 3;
    d.next = NULL;  d.data = 4;

    cout << findElementHasDataX(l, 3) << "\n";
    cout << findIthElement(l, 0) << "\n";
    cout << findLastElement(l);

    int count = 0;
    for (SNode *p = l.head; p/*!=NULL*/; p=p->next){
        //if (count == /*i=*/8) return p;
        count++;
    }

    return 0;
}