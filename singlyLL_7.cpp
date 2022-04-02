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
void readFromFile(SList &flist){
    ifstream fi("input.txt");
    int tmp;
    SNode *p= nullptr;
    while (1){
        fi >> tmp;
        if (tmp==0) break;
        if (p==nullptr){
            flist.head = makeNode(tmp);
            p = flist.head;
        }
        else{
            p->next = makeNode(tmp);
            p = p->next; 
        }
    }
    fi.close();
}
void seperateIntoTwoLists(SList flist, SList &list1, SList &list2){
    bool mark = 0;
    SNode *p1 = list1.head;
    SNode *p2 = list2.head;
    for (SNode *p=flist.head; p; p=p->next){
        if (mark==0){
            if (list1.head==nullptr) list1.head = p;
            else p1->next = p;
            p1 = p;
            mark = 1;
        }else{
            if (list2.head==nullptr) list2.head = p;
            else p2->next = p;
            p2 = p;
            mark = 0;
        }
    }
    if (list1.head!=nullptr) p1->next = nullptr;
    if (list2.head!=nullptr) p2->next = nullptr;
}
void writeToFile(SList list1, SList list2){
    ofstream fo("output.txt");
    if (list1.head!=nullptr){
        for (SNode *p=list1.head; p; p=p->next) fo << p->data << " ";
    }
    fo << "0\n";
    if (list2.head!=nullptr){
        for (SNode *p=list2.head; p; p=p->next) fo << p->data << " ";
    }
    fo << "0";
    fo.close();
}
int main(){
    SList flist, list1, list2;
    initialize(flist);
    initialize(list1);
    initialize(list2);
    readFromFile(flist);
    seperateIntoTwoLists(flist, list1, list2);
    writeToFile(list1, list2);
    return 0;
}