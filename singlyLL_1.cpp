#include <iostream>
#include <fstream>
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
/*
void removeAll(SList &l){
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
void readFromUser(int &x){
    cin >> x;
}

void writeToFile(SList &l){
    ofstream fo("output.txt");
    if (l.head!=nullptr){
        for (SNode *p=l.head; p; p=p->next) fo << p->data << " ";
    }
    fo << "0";
    fo.close();
}

void removeX(SList &l, int x){
    if (l.head==nullptr) return;
    SNode *p=l.head, *prev=nullptr; //prev can * kh??
    while (p!=nullptr){
        if (p->data==x){
            if (prev==nullptr){
                SNode *tmp = l.head;
                l.head = l.head->next;
                p = l.head;
                delete tmp;
            }else{
                SNode *tmp = p;
                prev->next = p->next;
                p = p->next;
                delete tmp;
            }
        }else{
            prev = p;
            p = p->next;
        }
    }
}
int main(){
    SList l;
    int x;
    initialize(l);
    readFromFile(l);
    readFromUser(x);
    removeX(l, x);
    writeToFile(l);
    return 0;
}