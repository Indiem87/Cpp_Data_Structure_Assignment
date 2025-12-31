#include<iostream>
using namespace std;

void integer_divide(int n,int max,int* result,int p)
{
    int i = 0;
    if(n == 0)
    {
        for(i = 0;i < p;i++)
        {
            if(i == 0)
            {
                cout<<result[i];
            }
            else
            {
                printf("+%d",result[i]);
            }
        }
        cout<<endl;
        return;                          
    }
    else
    {
        for(i = min(n,max);i > 0;i--)
        {
            result[p] = i;
            integer_divide(n-i,i,result,p+1);
        }
    }
}

int main()
{
    int i = 0,n;
    cin>>n;
    int* result = new int[n];
    for(i = 0;i < n;i++)
    {
        result[i] = 0;
    }
    integer_divide(n,n,result,0);
    return 0;
}
