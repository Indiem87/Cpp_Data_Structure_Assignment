#include <iostream>
#include <string>
using namespace std;

/* UPLOAD START */
void SortArr(int** arr, int n)
{
    for(int i=1;i<n;i++){
        for(int j=i-1;j>=0;j--){
            if(arr[j][0]>arr[j+1][0]){
                int tmp[2];
                tmp[0] = arr[j][0];
                tmp[1] = arr[j][1];
                arr[j][0] = arr[j+1][0];
                arr[j][1] = arr[j+1][1];
                arr[j+1][0] = tmp[0];
                arr[j+1][1] = tmp[1];
            }
            else
                break;
        }
    }
}
void mergeIntervals(int** arr, int n){
    /* The first interval is arr[0][0] to arr[0][1]
       The 2nd interval is arr[1][0] to arr[1][1]
       ...
       The last interval is arr[n-1][0] to arr[n-1][1]
       Print the results of merging these intervals. Assume endpoints are always included.
    */
    if(n==0)
    {
        cout<<endl;
        return;
    }
    SortArr(arr, n);
    int Intervalnum = 0;
    int **mergeArr = new int*[n];
    for(int i=0;i<n;i++)
    {
        mergeArr[i] = new int[2];
    }
    int currentStart = arr[0][0];
    int currentEnd = arr[0][1];
    for(int i=1;i<n;i++)
    {
        if(arr[i][0] <= currentEnd)
        {
            currentEnd = currentEnd>arr[i][1]?currentEnd:arr[i][1];
        }
        else
        {
            mergeArr[Intervalnum][0] = currentStart;
            mergeArr[Intervalnum][1] = currentEnd;
            Intervalnum++;
            currentStart = arr[i][0];
            currentEnd = arr[i][1];
        }
    }
    mergeArr[Intervalnum][0] = currentStart;
    mergeArr[Intervalnum][1] = currentEnd;
    Intervalnum++;
    bool first = true;
    for(int i=0;i<Intervalnum;i++)
    {
        if(first)
        {
            printf("[%d,%d]",mergeArr[i][0],mergeArr[i][1]);
            first = false;
        }
        else
        {
            printf(",[%d,%d]",mergeArr[i][0],mergeArr[i][1]);
        }
    }
    cout<<endl;
}

/* UPLOAD END */

void test1(){
    int** a = new int*[2];
    a[0] = new int[2];
    a[1] = new int[2];
    a[0][0] = 1;
    a[0][1] = 4;
    a[1][0] = 4;
    a[1][1] = 5;
    mergeIntervals(a,2);
    
    int** b = new int*[4];
    b[0] = new int[2]{1,3};
    b[1] = new int[2]{2,6};
    b[2] = new int[2]{8,10};
    b[3] = new int[2]{15,18};
    mergeIntervals(b,4);
}

int main()
{
    test1();
    return 0;
}