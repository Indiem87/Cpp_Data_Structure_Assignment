#include <iostream>
#include <iomanip>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

/* UPLOAD START */
template <class T>
struct DNode{
    T data;
    DNode<T>* next;
};

template <class T>
class ASet{ // for now we assume datatype T can be sorted
    private:
        int length;
        DNode<T>* head;
    public:
        ASet(){
            head = new DNode<T>;
            head->next = NULL;
            length = 0;
        }
        ASet(T* arr, int n){ //incoming array is guaranteed not to have duplicates.
            head = new DNode<T>;
            head->next = NULL;
            for(int i=n-1;i>=0;i--){
                DNode<T> *tmpNode = new DNode<T>;
                tmpNode->next = head->next;
                tmpNode->data = arr[i];
                head->next = tmpNode;
            }
            length = n;
        }
        ~ASet(){
            while(head!=NULL){
                DNode<T>* tmpNode = head;
                head = head->next;
                delete tmpNode;
            }
        }
        void addEle(T x){
            DNode<T>* tmpNode = head->next;
            int count = 0;
            while(tmpNode!=NULL){
                if(tmpNode->data == x) return;
                tmpNode = tmpNode->next;
                count++;
            } 
            DNode<T>* newNode = new DNode<T>;
            newNode->data = x;
            newNode->next = head->next;
            head->next = newNode;
            length++;
        }
        bool isEmpty(){
            return length==0;
        }
        bool removeEle(T x){
            // returns true if removed.
            // returns false if it is not in the set
            DNode<T>* tmpNode = head;
            while(tmpNode->next!=NULL){
                if(tmpNode->next->data == x)
                {
                    DNode<T>* delNode = tmpNode->next;
                    tmpNode->next = delNode->next;
                    delete delNode;
                    length--;
                    return true;
                }
                tmpNode = tmpNode->next;
            }
            return false;
        }
        bool hasEle(T x){
            DNode<T>* tmpNode = head->next;
            int count = 0;
            while(tmpNode!=NULL){
                if(tmpNode->data == x) return true;
                tmpNode = tmpNode->next;
                count++;
            }
            return false;
        }
        bool isSubsetOf(ASet<T>* S){
            DNode<T>* tmpNode = head->next;
            while(tmpNode!=NULL){
                if(!S->hasEle(tmpNode->data)) return false;
                tmpNode = tmpNode->next;
            }
            return true;
        }
        bool containsSet(ASet<T>* S){
            return S->isSubsetOf(this);
        }
        bool isDisjointFrom(ASet<T>* S){
            DNode<T>* tmpNode = head->next;
            while(tmpNode!=NULL){
                if(S->hasEle(tmpNode->data)) return false;
                tmpNode = tmpNode->next;
            }
            return true;
        }
        int cardinality(){
            return length;
        }
        ASet<T>* setUnion(ASet<T>* S){
            DNode<T>* tmpNode = head->next;
            ASet<T>* newSet = new ASet<T>();
            while(tmpNode!=NULL){
                newSet->addEle(tmpNode->data);
                tmpNode = tmpNode->next;
            }
            tmpNode = S->head->next;
            while(tmpNode!=NULL){
                newSet->addEle(tmpNode->data);
                tmpNode = tmpNode->next;
            }
            return newSet;
        }
        ASet<T>* intersect(ASet<T>* S){
            DNode<T>* tmpNode = head->next;
            ASet<T>* newSet = new ASet<T>();
            while(tmpNode!=NULL){
                if(S->hasEle(tmpNode->data))
                    newSet->addEle(tmpNode->data);
                tmpNode = tmpNode->next;
            }
            return newSet;
        }
        ASet<T>* subtract(ASet<T>* S){
            DNode<T>* tmpNode = head->next;
            ASet<T>* newSet = new ASet<T>();
            while(tmpNode!=NULL){
                if(!S->hasEle(tmpNode->data))
                    newSet->addEle(tmpNode->data);
                tmpNode = tmpNode->next;
            }
            return newSet;
        }
        ASet<T>* symDiff(ASet<T>* S){
            ASet<T>* part1 = subtract(S);
            ASet<T>* part2 = S->subtract(this);
            ASet<T>* result = part1->setUnion(part2);
            delete part1;
            delete part2;
            return result;
        }
        void printSet(){ //print the elements of S in ascending order
            if (length == 0) {
                cout << "{}" << endl;
                return;
            }
            
            T* arr = new T[length];     
            DNode<T>* tmpNode = head->next;
            for(int i=0;i<length;i++){
                arr[i] = tmpNode->data;
                tmpNode = tmpNode->next;
            }
            for(int i=0;i<length-1;i++){
                for(int j=0;j<length-1-i;j++){
                    if(arr[j]>arr[j+1]){
                        T tmp = arr[j];
                        arr[j] = arr[j+1];
                        arr[j+1] = tmp;
                    }
                }
            }
            cout<<"{";
            for(int i=0;i<length-1;i++)
                cout<<arr[i]<<",";
            cout<<arr[length-1];
            cout<<"}"<<endl;
            delete[] arr;
        }
};

/* UPLOAD END */

void simpleTest(){
    ASet<int> A;
    for(int i=1;i<=4;i++){
        A.addEle(i);
    }
    cout << "Set A: ";
    A.printSet();
    cout << "Cardinality of A: " << A.cardinality() << endl << endl;
    
    int tmpB[4] = {3,6,5,4};
    ASet<int> B(tmpB,4);
    cout << "Set B: ";
    B.printSet();
    cout << "Cardinality of B: " << B.cardinality() << endl << endl;
    
    ASet<int>* C = A.intersect(&B);
    ASet<int>* D = A.subtract(&B);
    
    cout << "Intersecting A and B gets set C, ";
    C->printSet();
    cout << "Union of A and B is ";
    (A.setUnion(&B))->printSet();
    cout << "Let set D be the set of elements in A but not B. Then set D is ";
    D->printSet();
    cout << "Symmetric difference of A and B is ";
    (A.symDiff(&B))->printSet();
    
    cout << endl << "Checking subset relations:" << endl;
    cout << "A " << (A.containsSet(C) ? "contains" : "does not contain") << " set C" << endl;
    cout << "B " << (B.containsSet(D) ? "contains" : "does not contain") << " set D" << endl;
    cout << "C is " << (C->isSubsetOf(&A) ? "" : "not ") << "a subset of A" << endl;
    cout << "D is " << (D->isSubsetOf(&B) ? "" : "not ") << "a subset of B" << endl;
}

int main(){
    simpleTest();
    return 0;
}