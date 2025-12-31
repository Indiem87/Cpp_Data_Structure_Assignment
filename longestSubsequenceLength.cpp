#include <iostream>
using namespace std;

/* UPLOAD START */
template <class T>
class VecList{
    private:
        int capacity;
        int length;
        T* arr;
        void doubleListSize(){
            T * oldArr = arr;
            arr = new T[2*capacity];
            capacity = 2 * capacity;
            for(int i=0;i<length;i++){
                arr[i] = oldArr[i];
            }
            delete [] oldArr;
        }
    public:
        VecList(){
            length = 0;
            capacity = 100;
            arr = new T[capacity];
        }
        VecList(T* a, int n){
            length = n;
            capacity = 100 + 2*n;
            arr = new T[capacity];
            for(int i=0;i<n;i++){
                arr[i] = a[i];
            }
        }
        ~VecList(){
            delete [] arr;
        }
        int getLength(){
            return length;
        }
        int* getArr(){
            return arr;
        }
        bool isEmpty(){
            return length==0;
        }
        void insertEleAtPos(int i, T x){
            if(length==capacity)
                doubleListSize();
            if(i > length || i < 0)
                throw "Illegal position";
            for(int j=length;j>i;j--)
                arr[j] = arr[j-1];
            arr[i] = x;
            length++;
        }
        T deleteEleAtPos(int i){
            if(i >= length || i < 0)
                throw "Illegal position";
            T tmp = arr[i];
            for(int j=i;j<length-1;j++)
                arr[j] = arr[j+1];
            length--;
            return tmp;
        }
        void setEleAtPos(int i, T x){
            if(i >= length || i < 0)
                throw "Illegal position";
            arr[i] = x;
        }
        T getEleAtPos(int i){
            if(i >= length || i < 0)
                throw "Illegal position";
            return arr[i];
        }
        int locateEle(T x){
            for(int i=0;i<length;i++){
                if(arr[i]==x)
                    return i;
            }
            return -1;
        }
        void printList(){
            for(int i=0;i<length;i++)
                cout << arr[i] << " ";
        }
};

int longestSubsequenceLength(int* a, int n) {
    if (n == 0) return 0;
    VecList<int> dp;
    for (int i=0;i<n;i++) 
    {
        dp.insertEleAtPos(i, 1);
    }
    int maxLen = 1;
    for (int i=1;i<n;i++) 
    {
        for (int j=0;j<i;j++) 
        {
            if (a[i] > a[j]) 
            {
                dp.setEleAtPos(i, dp.getEleAtPos(j)+1>dp.getEleAtPos(i) ? dp.getEleAtPos(j)+1:dp.getEleAtPos(i));
            }
        }
        maxLen = dp.getEleAtPos(i)>maxLen ? dp.getEleAtPos(i):maxLen;
    }
    return maxLen;
}
/* UPLOAD END */

void test1(){
    int a[8] = {10,9,2,5,3,7,101,18};
    cout << longestSubsequenceLength(a,8) << endl; //4
}            

void test2(){
    int a[7] = {1,2,3,5,3,7,8};
    cout << longestSubsequenceLength(a,7) << endl; //6
}

int main(){
    test1();
    test2();
    return 0;
}