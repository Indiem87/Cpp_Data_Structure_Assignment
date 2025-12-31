#include <iostream>
using namespace std;

/* Question 1 UPLOAD START */
int numStepsToN_v2(int N, int mod_num){
    // calculate the number of ways to get to N
    // allowed step on each move: +1, +2, +3
    // However, no two consecutive steps are the same.
    if(N==0) return 1;
    int** x = new int*[N+1];
    for(int i=0;i<=N;i++)
        x[i] = new int[3];
    if(N>=1)
    {
        x[1][0] = 1;
        x[1][1] = 0;
        x[1][2] = 0; 
    } 
    if(N>=2)
    {
        x[2][1] = 1;  
        x[2][0] = 0;
        x[2][2] = 0;
    }
    if(N>=3)
    {
        x[3][2] = 1;
        x[3][0] = 1;
        x[3][1] = 1;
    }
    for(int i=4;i<=N;i++){
        x[i][0] = (x[i-1][1] + x[i-1][2])%mod_num;
        x[i][1] = (x[i-2][0] + x[i-2][2])%mod_num;
        x[i][2] = (x[i-3][0] + x[i-3][1])%mod_num;
    }
    return (x[N][0] + x[N][1] + x[N][2])%mod_num;    
}

/* Question 1 UPLOAD END */

int main(){
    for(int i=0;i<=100;i++)
        cout << i << ": " << numStepsToN_v2(i,9999999) << endl;
    return 0;
}

/*
0: 1
1: 1
2: 1
3: 3
4: 3
5: 4
6: 8
7: 9
8: 12
9: 21
10: 27
*/