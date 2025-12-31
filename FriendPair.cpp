#include <iostream>
using namespace std;

/* Question 3 UPLOAD START */
int numOfFriendPairsiter(int n,int* Fpair)
{
    if(n==0) return 0;
    if(Fpair[n]!=0) return Fpair[n];
    Fpair[n] = ((n-1)*numOfFriendPairsiter(n-2,Fpair))%10000019 + numOfFriendPairsiter(n-1,Fpair);
    Fpair[n] %= 10000019;
    return Fpair[n];
}
int numOfFriendPairs(int n){
    // return the number of pairings with n people mod 10000019
    // max of n will be 150 in this problem
    int Fpair[151] = {0};
    Fpair[1] = 1;
    Fpair[2] = 2;
    return numOfFriendPairsiter(n,Fpair);       
}
/* Question 3 UPLOAD END */

void test(){
    for(int i=0;i<20;i++){
        cout << (3*i) << ": " << numOfFriendPairs(3*i) << endl;
    }
}

int main(){
    test();
    return 0;
}