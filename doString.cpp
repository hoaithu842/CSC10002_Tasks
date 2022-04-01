#include <iostream>
#include <cstring>
#include <fstream>
#define MAX 10000
using namespace std;
void trim(char *s){
    while (s[0]==' ') for (int i=0; i<strlen(s); i++) s[i] = s[i+1];
    while (s[strlen(s)-1]==' ') s[strlen(s)-1] = '\0';
    
    int i=0;
    while (i<strlen(s)){
        if ((s[i]==' ' && s[i+1]==' ') || (s[i]==' ' && ((s[i+1]==',') || (s[i+1]=='.')))){
            for (int j=i; j<strlen(s)-1; j++){
                s[j] = s[j+1];
            }
            s[strlen(s)-1] = '\0';
        } else i++;
    }
}
int wordCount(char *str){
    int count = 0;
    for (int i=0; i<strlen(str)-1; i++){
        if ((*(str+i)!=',' && *(str+i)!=' ' && *(str+i)!='.')
            && (*(str+i+1)==',' || *(str+i+1)==' ' || *(str+i+1)=='.' || *(str+i+1)=='\n'))
                count++;
    }
    return count;
}
void capitalize(char *str){
    if (*(str)>='a'&&*(str)<='z') *(str) = *(str) - 32;
    for (int i=1; i<strlen(str); i++){
        if ((*(str+i)>='a' && *(str+i)<='z')
            && ((*(str+i-1)==' ') || (*(str+i-1)=='\n'))) *(str+i) = *(str+i) - 32;
    }
}
void input(char *&str){
    ifstream ifs("sample.txt");
    int count = 0, kt = 0;
    char tmp[MAX];
    string tmpp;
    while (!ifs.eof()){
        getline(ifs, tmpp);
        for (int i=0; i<tmpp.length(); i++){
            tmp[count] = tmpp[i];
            count++;
        }
        if (tmpp[tmpp.length()-1]=='.'){
            tmp[count] = '\0';
            str = new char[count];
            str = strdup(tmp);
            ifs.close();
            return ;
        }
        tmp[count] = '\n';
        count++;
    }
    tmp[count] = '\0';
    str = new char[count];
    str = strdup(tmp);
    ifs.close();
}
void addSpace(char *&str){
    char tmp[MAX];
    int count = 0;
    for (int i=0; i<strlen(str); i++){
        if ((*(str+i)==',' || *(str+i)=='.') && *(str+i+1)!=' ' && i!=strlen(str)-1){
            tmp[count] = *(str+i);
            count++;
            tmp[count] = ' ';
            count++;
        } else{
            tmp[count] = *(str+i);
            count++;
        }
    }
    delete []str;
    str = new char[count];
    str = strdup(tmp);
}
int main(){
    char *str;
    input(str);
    trim(str);
    cout << "a) There is/are " << wordCount(str) << " word(s) in the paragraph." << endl;
    cout << "b) Normalized paragraph: \n";
    addSpace(str);
    capitalize(str);
    cout << str << endl;
    free(str);
}