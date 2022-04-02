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
void joinTwoLists(SList &list1, SList list2){
    for (SNode *p = list1.head; p; p=p->next){
        if (p->next==nullptr){
            p->next = list2.head;
            return;
        }
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
    SList list1, list2;
    initialize(list1);
    initialize(list2);
    readFromFile(list1, list2);
    joinTwoLists(list1, list2);
    writeToFile(list1);
    return 0;
}