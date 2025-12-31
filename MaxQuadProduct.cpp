#include <iostream>
#include <stdlib.h>
using namespace std;

/* UPLOAD START */
template <class T>
void bubbleabsAscS(T* &arr, int n){
    int exchange = n-1;
    while(exchange > 0){
        int bound = exchange;
        exchange = 0;
        for(int i=0;i<bound;i++){
            if(arr[i] > arr[i+1]){
                T tmp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = tmp;
                exchange = i;
            }
        }
    }
}

int maxQuadProduct(int* arr, int n){ 
    if(n < 4) return 0;
    if(n == 4) return arr[0]*arr[1]*arr[2]*arr[3];
    
    bubbleabsAscS<int>(arr, n);
    
    int maxProduct;

    int p1 = arr[0] * arr[1] * arr[2] * arr[3];
    maxProduct = p1;
    
    int p2 = arr[n-1] * arr[n-2] * arr[n-3] * arr[n-4];
    if(p2 > maxProduct) maxProduct = p2;

    int p3 = arr[0] * arr[n-1] * arr[n-2] * arr[n-3];
    if(p3 > maxProduct) maxProduct = p3;

    int p4 = arr[0] * arr[1] * arr[2] * arr[n-1];
    if(p4 > maxProduct) maxProduct = p4;

    int p5 = arr[0] * arr[1] * arr[n-1] * arr[n-2];
    if(p5 > maxProduct) maxProduct = p5;

    return maxProduct;
}

/* UPLOAD END */

void test1(){
    int tmp1[7] = {3,-7,5,-1,-9,-8};
    int tmp4[10] = {-10,-8,-2,0,3,9,15,1,7,4};
    cout << "Case 1: Maximum product is " << maxQuadProduct(tmp1,6) << endl;
    cout << "Case 4: Maximum product is " << maxQuadProduct(tmp4,10) << endl;
    cout << endl;
}

int main()
{
    test1();
    return 0;
}