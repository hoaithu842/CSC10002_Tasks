#include <fstream>
#include <iostream>
using namespace std;

struct SNode{
    int data;
    SNode *next;
};
struct SList{
    SNode *head;
};
void initialize(SList &l){
    l.head = nullptr;
}
SNode *makeNode(int data){
    SNode *newNode = new SNode;
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}
/*void removeAll(SList &l){
    if (l.head==NULL) return;
    for (SNode *p = l.head; p; p=p->next) removeHead(l);
}
*/
void readFromFile(SList &l){
    ifstream fi("input.txt");
    int tmp;
    SNode *p = nullptr;
    while (1){
        fi >> tmp;
        if (tmp==0) break;
        if (p==nullptr){
            l.head = makeNode(tmp);
            p = l.head;
        }
        else{
            p->next = makeNode(tmp);
            p = p->next; 
        }
    }
    fi.close();
}
void insertEvenNum(SList &l){
    if (l.head==nullptr) return;
    int evenNum = 2;
    SNode *p = l.head, *realp = nullptr;
    while (p!=nullptr){
        SNode *tmp = makeNode(evenNum);
        if (p==l.head){
            tmp->next = l.head;
            l.head = tmp;
        } else{
            tmp->next = realp->next;
            realp->next = tmp;
        }
        realp = p;
        p = p->next;
        evenNum = evenNum + 2;
    }
}
void writeToFile(SList l){
    ofstream fo("output.txt");
    if (l.head!=nullptr){
        for (SNode *p=l.head; p; p=p->next) fo << p->data << " ";
    }
    fo << "0";
    fo.close();
}
int main(){
    SList l;
    initialize(l);
    readFromFile(l);
    insertEvenNum(l);
    writeToFile(l);
    return 0;
}