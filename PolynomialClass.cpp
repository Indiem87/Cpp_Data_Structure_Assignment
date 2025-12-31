#include <iostream>
using namespace std;

/* UPLOAD START */
// You can use VecList, LinkList or none of these structures in writing the IntPolynomial class
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

class IntPolynomial{
    private:
        VecList<int>* C;
        VecList<int>* D;
        int N;
    public:
        IntPolynomial(){
            N = 0;
            int c[0] = {};
            int d[0] = {};
            C = new VecList<int>(c,N);
            D = new VecList<int>(d,N);
        }
        IntPolynomial(int * c, int * d, int n){
            N = n;
            C = new VecList<int>(c,N);
            D = new VecList<int>(d,N);
            int temp = 0;
            for(int i = 0;i < n;i++)
            {
                for(int j = 0;j < n-i-1;j++)
                {
                    if(D->getEleAtPos(j)>D->getEleAtPos(j+1))
                    {
                        temp = D->getEleAtPos(j+1);
                        D->setEleAtPos(j+1,D->getEleAtPos(j));
                        D->setEleAtPos(j,temp);
                        temp = C->getEleAtPos(j+1);
                        C->setEleAtPos(j+1,C->getEleAtPos(j));
                        C->setEleAtPos(j,temp);
                    }                    
                }
            }
        }
        ~IntPolynomial(){
            delete C;
            delete D;
        }
        int getDegree(){
            if(N == 0)
            {
                return -1;
            }
            if(N == 1)
            {
                if(D->getEleAtPos(N-1)==0 && C->getEleAtPos(N-1)==0)
                {
                    return -1;
                }
                else
                return D->getEleAtPos(N-1);
            }
            else if(N > 1)
            {
                return D->getEleAtPos(N-1);
            }
        }
        IntPolynomial* Add(IntPolynomial* b){
            int n1 = N,n2 = b->N;
            int i = 0,j = 0,p = 0,length = n1+n2;
            int* c = new int[length];
            int* d = new int[length];
            while(i<n1 && j<n2)
            {
                if(D->getEleAtPos(i) < b->D->getEleAtPos(j))
                {
                    if(C->getEleAtPos(i) != 0)
                    {
                        c[p] = C->getEleAtPos(i);
                        d[p] = D->getEleAtPos(i);
                        p++;
                    }
                    i++;
                }
                else if(D->getEleAtPos(i) > b->D->getEleAtPos(j))
                {
                    if(b->C->getEleAtPos(j) != 0)
                    {
                        c[p] = b->C->getEleAtPos(j);
                        d[p] = b->D->getEleAtPos(j);
                        p++;
                    }
                    j++;
                }
                else 
                {
                    int sum = C->getEleAtPos(i)+b->C->getEleAtPos(j);
                    if(sum != 0)
                    {
                        c[p] = C->getEleAtPos(i)+b->C->getEleAtPos(j);
                        d[p] = D->getEleAtPos(i);
                        p++;
                    }
                    i++;
                    j++;
                }
            }
            while (i<n1)
            {
                if(C->getEleAtPos(i) != 0)
                    {
                        c[p] = C->getEleAtPos(i);
                        d[p] = D->getEleAtPos(i);
                        p++;
                    }
                i++;
            }
            while(j<n2)
            {
                if(b->C->getEleAtPos(j) != 0)
                {
                    c[p] = b->C->getEleAtPos(j);
                    d[p] = b->D->getEleAtPos(j);
                    p++;
                }
                j++;
            }
            if(p == 0)
            {
                IntPolynomial* result = new IntPolynomial();
                return result;
            }
            else
            {
                IntPolynomial* result = new IntPolynomial(c,d,p+1);
                return result;
            }
        }
        IntPolynomial* Subtract(IntPolynomial* b){
            int n1 = N,n2 = b->N;
            int i = 0,j = 0,p = 0,length = n1+n2;
            int* c = new int[length];
            int* d = new int[length];
            while(i<n1 && j<n2)
            {
                if(D->getEleAtPos(i) < b->D->getEleAtPos(j))
                {
                    if(C->getEleAtPos(i) != 0)
                    {
                        c[p] = C->getEleAtPos(i);
                        d[p] = D->getEleAtPos(i);
                        p++;
                    }
                    i++;
                }
                else if(D->getEleAtPos(i) > b->D->getEleAtPos(j))
                {
                    if(b->C->getEleAtPos(j) != 0)
                    {
                        c[p] = -b->C->getEleAtPos(j);
                        d[p] = b->D->getEleAtPos(j);
                        p++;
                    }
                    j++;
                }
                else 
                {
                    int diff = C->getEleAtPos(i)-b->C->getEleAtPos(j);
                    if(diff != 0)
                    {
                        c[p] = C->getEleAtPos(i)-b->C->getEleAtPos(j);
                        d[p] = D->getEleAtPos(i);
                        p++;
                    }
                    i++;
                    j++;
                }
            }
            while (i<n1)
            {
                if(C->getEleAtPos(i) != 0)
                    {
                        c[p] = C->getEleAtPos(i);
                        d[p] = D->getEleAtPos(i);
                        p++;
                    }
                i++;
            }
            while(j<n2)
            {
                if(b->C->getEleAtPos(j) != 0)
                {
                    c[p] = -b->C->getEleAtPos(j);
                    d[p] = b->D->getEleAtPos(j);
                    p++;
                }
                j++;
            }
            if(p == 0)
            {
                IntPolynomial* result = new IntPolynomial();
                return result;
            }
            else
            {
                IntPolynomial* result = new IntPolynomial(c,d,p+1);
                return result;
            }
        }
        IntPolynomial* Multiply(IntPolynomial* b){
            int i = 0,j = 0;
            int x1 = 0,x2 = 0;
            int n1 = N,n2 = b->N;
            IntPolynomial* result = new IntPolynomial();
            for(i = 0;i < n2;i++)
            {
                x1 = b->C->getEleAtPos(i);
                x2 = b->D->getEleAtPos(i);
                IntPolynomial* temp = new IntPolynomial(C->getArr(),D->getArr(),N);
                for(j = 0;j < n1;j++)
                {
                    temp->C->setEleAtPos(j,C->getEleAtPos(j)*x1);
                    temp->D->setEleAtPos(j,D->getEleAtPos(j)+x2);
                }
                IntPolynomial* newResult = result->Add(temp);
                delete result;
                delete temp;
                result = newResult;
            }
            return result;           
        }
        void printPolynomial(){
            bool first_val = false;
            for(int i=0;i < N;i++)
            {
                if(C->getEleAtPos(i) == 0)
                {
                    continue;
                }
                else
                {
                    if(first_val == false)
                    {
                        if(C->getEleAtPos(i) > 1)
                        {
                            printf("%d",C->getEleAtPos(i));
                        }
                        else if(C->getEleAtPos(i) == 1)
                        {
                            if(D->getEleAtPos(i) == 0)
                            printf("1");
                        }
                        else if(C->getEleAtPos(i) == -1)
                        {
                            if(D->getEleAtPos(i) == 0)
                            printf("-1");
                            else
                            printf("-");
                        }
                        else if(C->getEleAtPos(i) < -1)
                        {
                            printf("%d",C->getEleAtPos(i));
                        }
                        first_val = true;    
                    }
                    else
                    {
                        if(C->getEleAtPos(i) > 1)
                        {
                            printf("+%d",C->getEleAtPos(i));
                        }
                        else if(C->getEleAtPos(i) == 1)
                        {
                            printf("+");
                        }
                        else if(C->getEleAtPos(i) == -1)
                        {
                            printf("-");
                        }
                        else if(C->getEleAtPos(i) < -1)
                        {
                            printf("%d",C->getEleAtPos(i));
                        }
                    }
                    if(D->getEleAtPos(i) == 0)
                    {
                        continue;
                    }
                    else if(D->getEleAtPos(i) == 1)
                    {
                        printf("x");
                    }
                    else 
                    {
                        printf("x^%d",D->getEleAtPos(i));
                    }
                }
            }
            if(first_val == true)
            {
                cout<<endl;
            }
            else
            {
                cout<<"0"<<endl;
            }
        }
};  

/* UPLOAD END */

void test1(){    
    // int p4c[5] = {1,-1,1,-1,0};
    // int p4d[5] = {0,1,2,11,3};
    int p4c[5] = {0,1,1,0,0};
    int p4d[5] = {0,0,2,11,3};
    IntPolynomial p4(p4c,p4d,5);
    p4.printPolynomial();
}

void test2(){
    int p1c[3] = {3,5,-6};
    int p1d[3] = {0,1,4};
    IntPolynomial p1(p1c,p1d,3);
    
    int p4c[5] = {-3,-5,6,1,-1};
    int p4d[5] = {1,3,7,9,11};
    IntPolynomial p4(p4c,p4d,5);
    // IntPolynomial p1;
    // IntPolynomial p4;
    
    p1.Add(&p4)->printPolynomial();
    p4.Subtract(&p1)->printPolynomial();
    
    p4.Add(&p4)->printPolynomial();
    p4.Subtract(&p4)->printPolynomial();
}

void test3(){
    // int p1c[3] = {1,-1,2};
    // int p1d[3] = {0,3,6};
    // IntPolynomial p1(p1c,p1d,3);
    
    // int p2c[4] = {1,1,2,4};
    // int p2d[4] = {0,3,6,12};
    // IntPolynomial p2(p2c,p2d,4);
    IntPolynomial p1;
    IntPolynomial p2;
    
    p1.Multiply(&p2)->printPolynomial();
}

int main(){
    int x;
    cin >> x;
    switch(x){
        case 1: test1(); break;
        case 2: test2(); break;
        case 3: test3(); 
        default:
        ;
    }
    return 0;
}
