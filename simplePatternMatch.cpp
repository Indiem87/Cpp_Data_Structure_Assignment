#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

/* UPLOAD START */

int* getNext(string T){
    int tLen = T.length();
    int* next = new int[tLen];
    if(tLen==0) return next;
    next[0] = -1;
    if(tLen==1) return next;
    next[1] = 0;
    for(int j=2;j<tLen;j++){
        // calculate next[i]
        int k = next[j-1];
        while(k!=-1 && T[k]!=T[j-1]){
            k = next[k];
        }
        next[j] = k+1;

        /*if(T[k]==T[j-1]){
            next[j] = k+1;
        }
        else{
            while(k!=-1 && T[k]!=T[j-1]){
                k = next[k];
            }
            next[j] = k+1;
        }*/
    }
    return next;
}

int KMP(string S, string T){
    int i=0, j=0; // i points to S, j points to T
    int sLen = S.length();
    int tLen = T.length();
    int* next = getNext(T);
    if(tLen==0) return 0;
    if(sLen==0) return -1;
    while(i < sLen && j < tLen){
        if(j==-1||S[i]==T[j]){
            // cout << "Matched " << i << " and " << j << endl;
            i++;
            j++;
        }
        else{
            // cout << "Mismatched " << i << " and " << j << endl;
            j = next[j];
        }
    }
    if(j==tLen){
        return i-j;
    }
    else
        return -1;
}

int simplePatternMatch(string s, string p){
    string matchstr[10];
    int pos1=0,pos2=0,i=0,k=0,matchspot[10] = {0};
    string searchstr = s;
    while(pos1 < p.length())
    {
        while(p[pos2] != '*' && pos2 < p.length())
        {
            pos2++;
        }
        matchstr[k] = p.substr(pos1,pos2-pos1);
        pos1=pos2+1;
        pos2=pos1;
        k++;
    }
    for(i = 0;i < k;i++)
    {
        matchspot[i] = KMP(searchstr,matchstr[i]);
        if(matchspot[i] == -1)
        {
            return -1;
        }
        if(matchspot[i]+matchstr[i].length() <= searchstr.length())
        {
            searchstr = searchstr.substr(matchspot[i] + matchstr[i].length());
        }
        else return -1;
    }
    return matchspot[0];
}

/* UPLOAD END */

int main(){
    int x;
    cin >> x;
    string s1 = "aaccdabbca";
    switch(x){
        case 1:
            cout << simplePatternMatch(s1,"abb") << endl;
            cout << simplePatternMatch(s1,"cda") << endl;
            cout << simplePatternMatch(s1,"ccdb") << endl;
            break;
        case 2:
            cout << simplePatternMatch(s1,"aa*ab") << endl;
            cout << simplePatternMatch(s1,"ad*ab") << endl;
            cout << simplePatternMatch(s1,"aa*d") << endl;
            break;
        case 3:
            cout << simplePatternMatch(s1,"e*ac*da") << endl;
            cout << simplePatternMatch(s1,"ac*cb*a") << endl;
            cout << simplePatternMatch(s1,"ac*cd*ca") << endl;
        default: ;
    }
    return 0;
}