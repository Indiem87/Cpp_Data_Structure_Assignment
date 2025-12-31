#include <iostream>
#include <string>
using namespace std;

/* UPLOAD START */

void makePalindrome(string s){
    int i=0,j=0;
    int loopspot=0;
    bool judge;
    for(i = 0;i < s.length();i++)
    {
        if(s.length()-i <= 1)
        {
            judge = true;
        }
        else
        {
            judge = true;
            for(j = 0;j < (s.length()-i)/2;j++)
            {
                if(s[i+j] != s[s.length()-j-1])
                {
                    judge = false;
                    break;
                }
            }
        }
        if(judge == true)
        {
            loopspot = i;
            break;
        }
        
    }
    for(j = 0;j < s.length();j++)
    {
        cout<<s[j];
    }
    for(j = loopspot-1;j >= 0;j--)
    {
        cout<<s[j];
    }
    cout<<endl;
}

/* UPLOAD END */

int main(){
    int x;
    cin >> x;
    switch(x){
        case 1:
            makePalindrome("A");
            makePalindrome("ABA");
             break;
        case 2:
            makePalindrome("AB");
            makePalindrome("ABC");
             break;
        case 3:
            makePalindrome("ABCB");
            makePalindrome("ABCC");
        default: ;
    }
    return 0;
}