#include<iostream>
#include<string>
using namespace std;

void findstr(string s)
{
    int minlength = s.length(),i=0,j=0,k=0;
    bool judge;
    for(i = 0;i < s.length();i++)
    {
        if(s.length()%(i+1) == 0)
        {
            judge = true;
            for(j = 0;j <= i;j++)
            {
                for(k = 1;k < s.length()/(i+1);k++)
                {
                    if(s[j] != s[j+(i+1)*k])
                    {
                        judge = false;
                        break;
                    }
                }
            }
            if(judge == true)
            {
                minlength = i+1;
                break;
            }
        }
        else continue;
    }
    cout<<minlength<<endl;
    for(i = 0;i < minlength;i++)
    {
        cout<<s[i];
    }
}
int main(void)
{
    string s;
    cin>>s;
    findstr(s);
    return 0;
}