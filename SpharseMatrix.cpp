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
        VecList(int n){
            length = n;
            capacity = 100 + 2*n;
            arr = new T[capacity];
        }
        VecList(T* a,int n){
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


// In the class below, we assume it is meaningful to put 0 as a value for the type T.
template <class T>
class SparseMatrix{
    private:
        int row;
        int col;
        int* Valv;
        int* Valr;
        int* Valc;
        int ValCapacity;
        int ValPos;
        void doubleValSize(){
            int* oldValr = Valr;
            int* oldValc = Valc;
            ValCapacity = 2*ValCapacity;
            Valr = new int[ValCapacity];
            Valc = new int[ValCapacity];
            for(int i=0;i<ValPos;i++)
            {
                Valr[i] = oldValr[i];
                Valc[i] = oldValc[i];
            }
            delete [] oldValr;
            delete [] oldValc;
        }
    public:
        SparseMatrix(){
            // default is 10 rows, 10 columns
            row = col = 10;
            ValCapacity = 1000;
            Valv = new int[ValCapacity];
            Valr = new int[ValCapacity];
            Valc = new int[ValCapacity];
            ValPos = 0;
        }
        SparseMatrix(int r, int c){
            row = r;
            col = c;
            ValCapacity = 1000;
            Valv = new int[ValCapacity];
            Valr = new int[ValCapacity];
            Valc = new int[ValCapacity];
            ValPos = 0;
        }
        ~SparseMatrix(){
            delete [] Valc;
            delete [] Valr;
            delete [] Valv;
        }
        void setEntry(int rPos, int cPos, T x){
            if(rPos >= row || rPos < 0 || cPos >= col || cPos < 0)
            {
                throw "Illegal position";
            }

            if (x != 0) 
            {
                int index = -1;
                for (int i = 0; i < ValPos; i++) 
                {
                    if (Valr[i] == rPos && Valc[i] == cPos) 
                    {
                        index = i;
                        break;
                    }
                }
                if (index != -1) 
                {
                    return;
                }
                int insertPos = ValPos; 
                for (int i = 0; i < ValPos; i++) 
                {
                    if (Valr[i] > rPos || (Valr[i] == rPos && Valc[i] > cPos)) 
                    {
                        insertPos = i;
                        break;
                    }
                }
                for (int i = ValPos; i > insertPos; i--) 
                {
                    Valr[i] = Valr[i - 1];
                    Valc[i] = Valc[i - 1];
                    Valv[i] = Valv[i - 1];
                }
                
                Valr[insertPos] = rPos;
                Valc[insertPos] = cPos;
                Valv[insertPos] = x;
                ValPos++;
            } 
        }
        int getValpos(void)
        {
            return ValPos;           
        }
        T getEntry(int rPos, int cPos){
            if(rPos >= row || rPos < 0 || cPos >= col || cPos < 0)
            {
                throw "Illegal position";
            }
            int i=0;
            for(i = 0;i < ValPos;i++)
            {
                if(Valr[i]==rPos && Valc[i]==cPos)
                {
                    return Valv[i];
                }
            }
            return 0;
        }
        SparseMatrix<T> * add(SparseMatrix<T> * B){
            if(row!=B->row || col!=B->col)
            {
                throw "Matrices have incompatible sizes";
            }
            SparseMatrix<T> * newMatrix = new SparseMatrix<T>(row,col);
            int i = 0, j = 0;
            int rA = Valr[i], cA = Valc[i], vA = Valv[i];
            int rB = B->Valr[j], cB = B->Valc[j], vB = B->Valv[j];
    
            while (i < ValPos && j < B->ValPos) 
            {
                rA = Valr[i];
                cA = Valc[i];
                vA = Valv[i];
                rB = B->Valr[j];
                cB = B->Valc[j];
                vB = B->Valv[j]; 
                
                if (rA < rB || (rA == rB && cA < cB)) 
                {
                    newMatrix->setEntry(rA, cA, vA);
                    i++;
                } 
                else if (rA > rB || (rA == rB && cA > cB)) 
                {    
                    newMatrix->setEntry(rB, cB, vB);
                    j++;
                } 
                else 
                {
                    newMatrix->setEntry(rA, cA, vA + vB);
                    i++;
                    j++;
                }
            }
            while (i < ValPos) 
            {
                newMatrix->setEntry(Valr[i], Valc[i], Valv[i]);
                i++;
            }
            while (j < B->ValPos) 
            {
                newMatrix->setEntry(B->Valr[j], B->Valc[j], B->Valv[j]);
                j++;
            }
            return newMatrix;
        }
        SparseMatrix<T> * subtract(SparseMatrix<T> * B){
            if(row!=B->row || col!=B->col)
            {
                throw "Matrices have incompatible sizes";
            }
            SparseMatrix<T> * newMatrix = new SparseMatrix<T>(row,col);
            int i = 0,j = 0;
            int rA = Valr[i], cA = Valc[i], vA = Valv[i];
            int rB = B->Valr[j], cB = B->Valc[j], vB = B->Valv[j];
    
            while (i < ValPos && j < B->ValPos) 
            {
                rA = Valr[i];
                cA = Valc[i];
                vA = Valv[i];
                rB = B->Valr[j];
                cB = B->Valc[j];
                vB = B->Valv[j]; 
                
                if (rA < rB || (rA == rB && cA < cB)) 
                {
                    newMatrix->setEntry(rA, cA, vA);
                    i++;
                } 
                else if (rA > rB || (rA == rB && cA > cB)) 
                {    
                    newMatrix->setEntry(rB, cB, -vB);
                    j++;
                } 
                else 
                {
                    newMatrix->setEntry(rA, cA, vA - vB);
                    i++;
                    j++;
                }
            }
            while (i < ValPos) 
            {
                newMatrix->setEntry(Valr[i], Valc[i], Valv[i]);
                i++;
            }
            while (j < B->ValPos) 
            {
                newMatrix->setEntry(B->Valr[j], B->Valc[j], -B->Valv[j]);
                j++;
            }
            return newMatrix;
        }
        SparseMatrix<T> * multiply(SparseMatrix<T> * B){
            //perform multiplication if the sizes of the matrices are compatible.
            if(col!=B->row)
            {
                throw "Matrices have incompatible sizes";
            }
            SparseMatrix<T> * newMatrix = new SparseMatrix<T>(row,B->col);
            for(int i=0;i<ValPos;i++)
            {
                for(int j=0;j<B->getValpos();j++)
                {
                    if(Valc[i] == B->Valr[j])
                    {
                        newMatrix->setEntry(Valr[i], B->Valc[j], newMatrix->getEntry(Valr[i], B->Valc[j])+(Valv[i]*B->Valv[j]));
                    }
                }
            }
            return newMatrix;
        }
        
        
        // Only call this function if you know the size of matrix is reasonable.
        void printMatrix(){
            if(row>0 && row<=1000 && col>0 && col<=1000)
            {
                for(int i=0;i<row;i++)
                {
                    for(int j=0;j<col;j++)
                    {
                        cout << getEntry(i,j) << ' ';
                    }
                    cout << endl;
                }
            }
        }
        
        //This is for printing only non-zero entries
        void printNZMatrix(){
            for(int i=0;i < ValPos;i++)
            {
                cout<<Valr[i]<<' '<<Valc[i]<<' '<<Valv[i]<<endl;
            }
        }
};

/* UPLOAD END */

int main(){
    SparseMatrix<int> X(10000,10000), Y(10000,10000);
    X.setEntry(1,3,4);
    X.setEntry(7,8,2);
    Y.setEntry(1,6,4);
    Y.setEntry(1,3,4);
    Y.setEntry(7,7,2);
    X.printMatrix();
    cout << endl;
    Y.printMatrix();
    cout << endl;
    X.add(&Y)->printMatrix();
    cout << endl;
    X.subtract(&Y)->printMatrix();
    
    
    Y.multiply(&X)->printNZMatrix();
    return 0;
}