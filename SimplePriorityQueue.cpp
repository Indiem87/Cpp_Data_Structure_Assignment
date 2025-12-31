#include <iostream>
#include <string>
using namespace std;

/* UPLOAD START */

template <class T>
struct DNode{
    T data;
    DNode<T>* next;
};

template <class T>
class SimplePriorityQueue{
    private:
        DNode<T>* front[11];  
        DNode<T>* back[11];
        int length;
        int maxPriority;      
        
    public:
        SimplePriorityQueue() : SimplePriorityQueue(10) {} 
        
        SimplePriorityQueue(int numP){
            if(numP < 0 || numP > 10) throw "Invalid priority count!";
            maxPriority = numP;
            length = 0;
            
            
            for(int i = 0; i <= maxPriority; i++){
                front[i] = new DNode<T>;
                front[i]->next = NULL;
                back[i] = front[i];
            }
        }
        
        ~SimplePriorityQueue(){
            
            for(int i = 0; i <= maxPriority; i++){
                DNode<T>* current = front[i];
                while(current != NULL){
                    DNode<T>* temp = current;
                    current = current->next;
                    delete temp;
                }
            }
        }
        
        void enQueue(T x, int p){
            if(p < 0 || p > maxPriority) throw "Invalid priority!";
            
            DNode<T>* newNode = new DNode<T>;
            newNode->data = x;
            newNode->next = NULL;
            
            
            back[p]->next = newNode;
            back[p] = newNode;
            length++;
        }
        
        T deQueue(){
            if(length == 0) throw "Queue Empty!";
            
            
            for(int i = 0; i <= maxPriority; i++){
                if(front[i]->next != NULL){
                    DNode<T>* temp = front[i]->next;
                    T data = temp->data;
                    
                    front[i]->next = temp->next;
                    if(temp == back[i]){ 
                        back[i] = front[i];
                    }
                    
                    delete temp;
                    length--;
                    return data;
                }
            }
            
            throw "Queue Empty!";  
        }
        
        T peekQueue(){
            if(length == 0) throw "Queue Empty!";
            
            for(int i = 0; i <= maxPriority; i++){
                if(front[i]->next != NULL){
                    return front[i]->next->data;
                }
            }
            
            throw "Queue Empty!";
        }
        
        bool isEmpty(){
            return length == 0;
        }
        
};

/* UPLOAD END */

int main(){
    
    SimplePriorityQueue<char> spq(6);
    cout << "Before insertion, queue is " << (spq.isEmpty()?"empty":"non-empty") << endl;
    int priors[16]={0,1,2,3,4,5,0,3,2,4,0,2,1,5,1,3};
    for(int i=0;i<16;i++){
        spq.enQueue('a'+i,priors[i]);
    }
    
    cout << "Front of queue is now " << spq.peekQueue() << endl;
    // Push out first 10 items
    for(int j=0;j<10;j++){
        cout << spq.deQueue() << " has left the queue" << endl;
    }
    cout << "Right now, queue is " << (spq.isEmpty()?"empty":"non-empty") << endl;
    cout << "Inserting some digits according to squares mod 6" << endl;
    for(int i=0;i<10;i++){
        spq.enQueue('0'+i,i*i%6);
    }
    
    // Empty the queues
    while(!spq.isEmpty()){
        cout << spq.deQueue() << " has left the queue" << endl;
    }
    cout << "Right now, queue is " << (spq.isEmpty()?"empty":"non-empty") << endl;
    for(int i=0;i<10;i++){
        spq.enQueue('0'+i,i%6);
    }
    
    cout << "Right now, queue is " << (spq.isEmpty()?"empty":"non-empty") << endl;
    return 0;
}
