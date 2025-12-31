#include <iostream>
using namespace std;

/* Question 2 UPLOAD START */
int numOfBinaryTreesiter(int n,int* Bintree)
{
    if(n<=1)       
        return 1;
    if(Bintree[n]!=0)
        return Bintree[n];
    Bintree[n] = 0;
    for(int i=0;i<n;i++)
    {
        Bintree[n] += (numOfBinaryTreesiter(i,Bintree)%30011) * (numOfBinaryTreesiter(n-i-1,Bintree)%30011);
        Bintree[n] %= 30011;
    }
    return Bintree[n];
}
int numOfBinaryTrees(int n){
    // return the number of binary trees with n nodes mod 30011
    // max of n will be 150 in this problem
    int Bintree[151] = {0};
    return numOfBinaryTreesiter(n,Bintree);  
}
/* Question 2 UPLOAD END */

void test(){
    for(int i=0;i<20;i++){
        cout << (2*i) << ": " << numOfBinaryTrees(2*i) << endl;
    }
}

int main(){
    test();
    return 0;
}