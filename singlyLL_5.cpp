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
void readFromFile(SList &l, int &data){
    ifstream fi("input.txt");
    fi >> data;
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
void updateSortedList(SList &l, int x){
    SNode *newNode = makeNode(x);

    if (l.head==nullptr || l.head->data>x){ //Head
        newNode->next = l.head;
        l.head = newNode;
        return;
    }

    SNode *p = l.head;
    for (p = l.head; p->next; p=p->next){   //Mid
        if (p->data<=x && (*p->next).data>=x){
            newNode->next = p->next;
            p->next = newNode;
            return;
        }
    }

    p->next = newNode;  //Tail
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
    int data;
    initialize(l);
    readFromFile(l, data);
    updateSortedList(l, data);
    writeToFile(l);
    return 0;
}