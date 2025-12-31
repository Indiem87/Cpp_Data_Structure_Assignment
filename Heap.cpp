#include <iostream>
#include <iomanip>
using namespace std;

/* UPLOAD START */

template <class T>
class AMinHeap{ // class T better has its comparison operators correctly overloaded
    private:
        T *heapArr; 
        int capacity;
        int numData;
        void doubleHeapSize(){
            T* oldArr = heapArr;
            capacity = 2 * capacity;
            heapArr = new T[capacity];
            for(int i=1;i<=numData;i++){
                heapArr[i] = oldArr[i];
            }
            delete [] oldArr;
        }
        void siftUp(int index){
            int j = 2*index;
            while(j <= numData){
                if(j < numData && heapArr[j+1] < heapArr[j])
                    j = j + 1;
                if(heapArr[index] <= heapArr[j])
                    break;
                T tmp = heapArr[index];
                heapArr[index] = heapArr[j];
                heapArr[j] = tmp;
                index = j;
                j = 2*index;
            }
        }
        void siftDown(int index){
            int parent = index / 2;
            while(parent >= 1){
                if(heapArr[parent] <= heapArr[index])
                    break;
                T tmp = heapArr[parent];
                heapArr[parent] = heapArr[index];
                heapArr[index] = tmp;
                index = parent;
                parent = index / 2;
            }
        }
    public:
        AMinHeap(){
            heapArr = new T[101]; //index 0 not used
            capacity = 100;
            numData = 0;
        }
        AMinHeap(T* arr, int n){
            capacity = n + 100;
            heapArr = new T[capacity];
            numData = n;
            for(int i=1;i<=n;i++){
                heapArr[i] = arr[i-1];
            }
            for(int i=n/2;i>=1;i--){
                siftUp(i);
            }
        }
        ~AMinHeap(){
            delete [] heapArr;
        }
        bool isEmpty(){
            return numData==0;
        }
        T getMin(){
            if(numData==0)
                throw "Heap Empty";
            return heapArr[1];
        }
        void push(T x){
            if(numData==capacity-1)
                doubleHeapSize();
            numData++;
            heapArr[numData] = x;
            siftDown(numData);
        }
        T delMin(){
            if(numData==0)
                throw "Heap Empty";
            T tmp;
            tmp = heapArr[1];
            heapArr[1] = heapArr[numData];
            numData--;
            siftUp(1);
            return tmp;
        }
        T* getLevelOrderArray(){
            return heapArr;
        }
        int getNumData(){
            return numData;
        }
};

/* UPLOAD END */

template <class T>
void printLevelOrder(T* data, int numItems){ //assumes class T has an overloaded ostream << operator.
    for(int i=1;i<=numItems;i++){
        cout << data[i] << " ";
    }
}

int test1(){ // normal test
    AMinHeap<int> amh;
    cout << (amh.isEmpty() ? "Empty" : "Non-Empty") << " Heap" << endl;
    amh.push(10);
    amh.push(8);
    amh.push(6);
    printLevelOrder(amh.getLevelOrderArray(),amh.getNumData());
    cout << endl;
    amh.push(4);
    printLevelOrder(amh.getLevelOrderArray(),amh.getNumData());
    cout << endl;
    cout << (amh.isEmpty() ? "Empty" : "Non-Empty") << " Heap" << endl;
    
    cout << "Top: " << amh.getMin() << endl;
    printLevelOrder(amh.getLevelOrderArray(),amh.getNumData());
    cout << endl;
    
    cout << "Popping:" << endl;
    while(!amh.isEmpty()){
        cout << "Current Min: " << amh.delMin() << endl;
        cout << endl;
    }
    return 0;
}

int main(){
    //unit test for Heap.
    test1();
    return 0;
}