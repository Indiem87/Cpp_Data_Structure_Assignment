#include<iostream>
using namespace std;

template <class T>
struct DNode{
    T data;
    DNode<T>* next;
};

template <class T>
class LinkQueue{
    private:
        DNode<T>* front;
        DNode<T>* back;
        int length;
    public:
        LinkQueue(){
            front = new DNode<T>;
            back = new DNode<T>;
            front->next = back;
            back->next = front->next;
            length = 0;
        }
        ~LinkQueue(){
            DNode<T>* end = back;
            front = front->next;
            while(front!=end){
                back = front;
                front = front->next;
                delete back;
            }
            delete end;
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void enQueue(T x){
            if(length == 0)
            {
                back->data = x;
                length++;
            }
            else
            {
                DNode<T>* tmpN = new DNode<T>;
                tmpN->data = x;
                tmpN->next = front->next;
                back->next = tmpN;
                back = tmpN;
                length++;
            }
        }
        T deQueue(){
            if(length==0) throw "Queue Empty!";
            else if(length==1) 
            {
                length--;
                return front->next->data;
            }
            else
            {
                DNode<T>* tmpN = front->next;
                front->next = tmpN->next;
                back->next = front->next;
                T tmpD = tmpN->data;
                delete tmpN;
                length--;
                return tmpD;
            }            
        }
        T peekQueue(){
            if(length==0) throw "Queue Empty!";
            return front->next->data;
        }
        void pass(){
            front = front->next; 
            back = back->next;
        }
        void printEle(){
            cout<<front->next->data<<' ';
        }
};

int main()
{
    int i = 0,n = 0,m = 0,p = 1;
    LinkQueue<int> Ring_solution;
    scanf("%d %d",&n,&m);
    for(i = 1;i <= n;i++)
    {
        Ring_solution.enQueue(i);
    }
    while (!Ring_solution.isEmpty())
    {
        while(p<m)   
        {
            Ring_solution.pass();
            p++;
        } 
        Ring_solution.printEle();
        Ring_solution.deQueue();
        p = 1;
    }
    return 0;
}
