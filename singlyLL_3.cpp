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
/*void removeAll(SList &l){
    if (l.head==NULL) return;
    for (SNode *p = l.head; p; p=p->next) removeHead(l);
}
*/
void readFromFile(SList &l){
    ifstream fi("textfile.txt");
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
void reverseList(ofstream &fo, SNode *p){
    if (p==nullptr) return;
    reverseList(fo, p->next);
    fo << p->data << " ";
}
void writeToFile(SList l){
    ofstream fo("textfile.txt");
    if (l.head!=nullptr) reverseList(fo, l.head);
    fo << "0";
    fo.close();
}
int main(){
    SList l;
    initialize(l);
    readFromFile(l);
    writeToFile(l);
    return 0;
}