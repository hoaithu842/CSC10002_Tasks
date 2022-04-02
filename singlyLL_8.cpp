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
void readFromFile(SList &list1, SList &list2){
    ifstream fi("input.txt");
    int tmp;
    SNode *p;
    
    //list1
    p = nullptr;
    while (1){
        fi >> tmp;
        if (tmp==0) break;
        if (p==nullptr){
            list1.head = makeNode(tmp);
            p = list1.head;
        }
        else{
            p->next = makeNode(tmp);
            p = p->next; 
        }
    }
    //list2
    p = nullptr;
    while (1){
        fi >> tmp;
        if (tmp==0) break;
        if (p==nullptr){
            list2.head = makeNode(tmp);
            p = list2.head;
        }
        else{
            p->next = makeNode(tmp);
            p = p->next; 
        }
    }

    fi.close();
}
void joinTwoLists(SList &flist, SList &list1, SList list2){
    SNode *p1 = list1.head;
    SNode *p2 = list2.head;
    SNode *p3 = flist.head;
    while (1){
        if (p1!=nullptr){
            if (p3==flist.head) flist.head = p1;
            else p3->next = p1;
            p3 = p1;
            p1 = p1->next;
        }
        if (p2!=nullptr){
            if (p3==nullptr) flist.head = p2;
            else p3->next = p2;
            p3 = p2;
            p2 = p2->next;
        }
        if (p1==nullptr && p2==nullptr) break;
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
    SList flist, list1, list2;
    initialize(flist);
    initialize(list1);
    initialize(list2);
    readFromFile(list1, list2);
    joinTwoLists(flist, list1, list2);
    writeToFile(flist);
    return 0;
}