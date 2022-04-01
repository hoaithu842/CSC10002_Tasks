#include <iostream>

using namespace std;

void printAllPermutations(int n, bool kt[], int tmp[], int count){
    if (count!=0){
        for (int i=0; i<count; i++) cout << tmp[i] << " ";
        cout << "\n";
    }
    for (int i=1; i<=n; i++){
        if (!kt[i]){
            kt[i] = true;
            tmp[count] = i;
            printAllPermutations(n, kt, tmp, count+1);
            kt[i] = false;
        }
    }
}
void printKPermutations(int n, int k, bool kt[], int tmp[], int count){
    if (k>n){
        cout << "Cannot process...";
        return;
    }
    if (count==k){
        for (int i=0; i<count; i++) cout << tmp[i] << " ";
        cout << "\n";
        return;
    }
    for (int i=1; i<=n; i++){
        if (!kt[i]){
            kt[i] = true;
            tmp[count] = i;
            printKPermutations(n, k, kt, tmp, count+1);
            kt[i] = false;
        }
    }
}
void printKSets(int n, int k, int start, int tmp[], int count){
    if (count==k){
        for (int i=0; i<count; i++) cout << tmp[i] << " ";
        cout << "\n";
        return;
    }
    for (int i=start; i<=n; i++){
        tmp[count] = i;
        printKSets(n, k, i+1, tmp, count+1);
    }
}