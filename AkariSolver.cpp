#include<iostream>
#include<list>
#include<algorithm>
using namespace std;

template <class T>
struct DNode{
    T Pos[5];                     //#Pos0 is relative Pos,Pos1-2 is center Pos
    DNode<T>* next;
};

template <class T>
class LinkStack{
    private:
        DNode<T>* top;
        int length;
    public:
        LinkStack(){
            top = NULL;
            length = 0;
        }
        ~LinkStack(){
            while(top!=NULL){
                DNode<T>* tmp = top;
                top = top->next;
                delete tmp;
            }
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void push(T* Pos){
            DNode<T>* tmp = new DNode<T>;
            for(int i=0;i<5;i++)
                tmp->Pos[i] = Pos[i];
            tmp->next = top;
            top = tmp;
            length++;
        }
        T* pop(){
            if(length==0) throw "Stack Empty!";
            DNode<T>* tmp = top;
            top = top->next;
            T* tmpPos = new T[5];
            for(int i=0;i<5;i++)
                tmpPos[i] = tmp->Pos[i];
            delete tmp;
            length--;
            return tmpPos;
        }
        T* getTop(){
            if(length==0) throw "Stack Empty!";
            return top->Pos;
        }
        T getTop(int i)
        {
            if(length==0) throw "Stack Empty!";
            return top->Pos[i];
        }
        void printStack(){
            cout << "Stack top: ";
            DNode<T>* tmp = top;
            while(tmp!=NULL){
                cout << tmp->Pos[3] << " ";
                tmp = tmp->next;
            }
            cout << ":stack bottom" << endl;
        }
};

struct leaddark{
    int Row;
    int Col;
    int Value;
    int surround;
    bool lastfull;
};

class AkariSolver{
    private:
        LinkStack<int>* LightStack;
        int** LightState;
        int** BlockState;
        int** NoplaceState;
        leaddark* LeadDark;
        int LeadDarkNum;
        int Row;
        int Col;
        int LeadDirection[4][2] = {
            {-1,0},
            {0,-1},
            {0,1},
            {1,0}
        };
    public:
        AkariSolver(char** map,int row,int col)
        {
            Row = row+2;
            Col = col+2;
            LightStack = new LinkStack<int>();
            LightState = new int*[Row];
            BlockState = new int*[Row];
            NoplaceState = new int*[Row];
            LeadDark = new leaddark[row*col];
            LeadDarkNum = 0;
            for(int i=0;i < Row;i++)
            {
                LightState[i] = new int[Col];
                BlockState[i] = new int[Col];
                NoplaceState[i] = new int[Col];
                for(int j=0;j < Col;j++)
                {
                    NoplaceState[i][j] = 0;
                }
            }
            for(int i=1;i < Row-1;i++)
            {
                for(int j=1;j < Col-1;j++)
                {
                    switch (map[i-1][j-1])
                    {
                    case '.':
                        LightState[i][j] = 0;
                        BlockState[i][j] = -3;
                        break;
                    case 'X':
                        LightState[i][j] = 1;                            
                        BlockState[i][j] = -1;
                        NoplaceState[i][j]++;
                        break;
                    case '0':
                        LightState[i][j] = 1;
                        BlockState[i][j] = 0;
                        for(int k=0;k < 4;k++)
                        {
                            NoplaceState[i+LeadDirection[k][0]][j+LeadDirection[k][1]]++;
                        }
                        break;
                    case '1':
                        LightState[i][j] = 1;
                        LeadDarkNum++;
                        BlockState[i][j] = LeadDarkNum;
                        NoplaceState[i][j]++;
                        LeadDark[LeadDarkNum].Row = i;
                        LeadDark[LeadDarkNum].Col = j;
                        LeadDark[LeadDarkNum].Value = 1;
                        LeadDark[LeadDarkNum].surround = 0;
                        LeadDark[LeadDarkNum].lastfull = false;
                        break;
                    case '2':
                        LightState[i][j] = 1;
                        LeadDarkNum++;
                        BlockState[i][j] = LeadDarkNum;
                        NoplaceState[i][j]++;
                        LeadDark[LeadDarkNum].Row = i;
                        LeadDark[LeadDarkNum].Col = j;
                        LeadDark[LeadDarkNum].Value = 2;
                        LeadDark[LeadDarkNum].surround = 0;
                        LeadDark[LeadDarkNum].lastfull = false;
                        break;
                    case '3':
                        LightState[i][j] = 1;
                        LeadDarkNum++;
                        BlockState[i][j] = LeadDarkNum;
                        NoplaceState[i][j]++;
                        LeadDark[LeadDarkNum].Row = i;
                        LeadDark[LeadDarkNum].Col = j;
                        LeadDark[LeadDarkNum].Value = 3;
                        LeadDark[LeadDarkNum].surround = 0;
                        LeadDark[LeadDarkNum].lastfull = false;
                        break;
                    case '4':
                        LightState[i][j] = 1;
                        LeadDarkNum++;
                        BlockState[i][j] = LeadDarkNum;
                        NoplaceState[i][j]++;
                        LeadDark[LeadDarkNum].Row = i;
                        LeadDark[LeadDarkNum].Col = j;
                        LeadDark[LeadDarkNum].Value = 4;
                        LeadDark[LeadDarkNum].surround = 0;
                        LeadDark[LeadDarkNum].lastfull = false;
                        break;   
                    default:
                        throw "Invalid Map!";
                    }
                }
            }
            for(int i=0;i < Row;i++)
            {
                LightState[i][0] = 1;
                LightState[i][Col-1] = 1;
                BlockState[i][0] = -1;
                BlockState[i][Col-1] = -1;
                NoplaceState[i][0]++;
                NoplaceState[i][Col-1]++;
            }
            for(int i=0;i < Col;i++)
            {
                LightState[0][i] = 1;
                LightState[Row-1][i] = 1;
                BlockState[0][i] = -1;
                BlockState[Row-1][i] = -1;
                NoplaceState[0][i]++;
                NoplaceState[Row-1][i]++;
            }
        }
        ~AkariSolver()
        {
            delete LightStack;
            delete[] LeadDark;
            for(int i=0;i < Row;i++)
            {
                delete[] LightState[i];
                delete[] BlockState[i];
                delete[] NoplaceState[i];
            }
            delete[] LightState;
            delete[] BlockState;
            delete[] NoplaceState;
        }
        int* searchpoint(int* Pos)
        {
            int i=0,j=0;
            int wanderpoint[2];
            if(Pos[4]) // leaddark 模式
            {
                int leadpoint[2] = {0,0};
                leadpoint[0] = LeadDark[Pos[0]].Row;
                leadpoint[1] = LeadDark[Pos[0]].Col;
                for(i = Pos[3];i < 4;i++)
                {
                    wanderpoint[0] = leadpoint[0]+LeadDirection[i][0];
                    wanderpoint[1] = leadpoint[1]+LeadDirection[i][1];
                    if(BlockState[wanderpoint[0]][wanderpoint[1]] == -3 && LightState[wanderpoint[0]][wanderpoint[1]] == 0 && NoplaceState[wanderpoint[0]][wanderpoint[1]] == 0)
                    {
                        LightStack->push(Pos);
                        Lightup(Pos,1);
                        // cout<<Pos[0]<<" "<<Pos[3]<<" "<<endl;      //
                        if(Pos[3] == 3)
                        {
                            Pos[3] = 0;
                            Pos[0]++;
                            if(Pos[0] == LeadDarkNum+1)
                            {
                                Pos[0] = 1;
                                Pos[1] = 1;
                                Pos[2] = 0;
                                Pos[4] = 0;
                            }
                        }
                        else
                        {
                            Pos[3]++;
                        }
                        return Pos;
                    }
                    Pos[3]++;
                }
                // 4 个方向都试过但没有放置：重置相对位置，进入下一个编号块或转为 grid 模式
                Pos[3] = 0;
                Pos[0]++;
                if(Pos[0] == LeadDarkNum+1)
                {
                    Pos[0] = 1;
                    Pos[1] = 1;
                    Pos[2] = 0;
                    Pos[4] = 0;
                }
            }
            else // grid 模式
            {   
                if(LightState[Pos[0]][Pos[1]] == 0 && BlockState[Pos[0]][Pos[1]] == -3)
                {
                    // 尝试从 Pos[2]（上次尝试到的方向）开始的两个方向
                    for(i = Pos[2]; i < 2; i++)
                    {
                        wanderpoint[0] = Pos[0]+LeadDirection[i+2][0]*Pos[3];
                        wanderpoint[1] = Pos[1]+LeadDirection[i+2][1]*Pos[3];
                        while(BlockState[wanderpoint[0]][wanderpoint[1]] < -1)
                        {
                            if(BlockState[wanderpoint[0]][wanderpoint[1]] == -3 && LightState[wanderpoint[0]][wanderpoint[1]] == 0 && NoplaceState[wanderpoint[0]][wanderpoint[1]] == 0)
                            {
                                LightStack->push(Pos);
                                Lightup(Pos,1);
                                // cout<<Pos[2]<<" "<<Pos[3]<<" "<<endl;    //
                                Pos[3] = 0;
                                Pos[2] = 0;
                                if(Pos[1] == Col-1)
                                {
                                    Pos[0]++;
                                    Pos[1] = 1;
                                }
                                else
                                {
                                    Pos[1]++;
                                }
                                return Pos;
                            }
                            Pos[3]++;
                            wanderpoint[0] += LeadDirection[i+2][0];
                            wanderpoint[1] += LeadDirection[i+2][1];
                        }
                        Pos[3] = 1;
                        Pos[2]++;
                    }   
                }
                else
                {
                    Pos[3] = 0;
                    Pos[2] = 0;
                    if(Pos[1] == Col-1)
                    {
                        Pos[0]++;
                        Pos[1] = 1;
                    }
                    else
                    {
                        Pos[1]++;
                    }
                }        
            }
            return Pos;
        }
        void Lightup(int* Pos,int light)                               //light up a point and search leaddark around it
        {
            int i=0,j=0;
            int row;
            int col;
            int wanderpoint[2];
            if(Pos[4])
            {
                row = LeadDark[Pos[0]].Row + LeadDirection[Pos[3]][0];
                col = LeadDark[Pos[0]].Col + LeadDirection[Pos[3]][1];
            }
            else
            {
                row = Pos[0] + LeadDirection[Pos[2]+2][0]*Pos[3];
                col = Pos[1] + LeadDirection[Pos[2]+2][1]*Pos[3];
            }
            LightState[row][col] += light;
            if(light == 1)
            {
                BlockState[row][col] = -2;                     //-2 for light in the block,-3 for empty,-1 for dark
                // cout<<"Match:"<<row<<" "<<col<<endl;              //
            }
            else
            {
                BlockState[row][col] = -3;
                // cout<<"DisMatch:"<<row<<" "<<col<<endl;                //
            }
            for(i = 0;i < 4;i++)
            {
                if(Pos[4])
                {
                    bool currentfull;
                    wanderpoint[0] = row + LeadDirection[i][0];
                    wanderpoint[1] = col + LeadDirection[i][1];
                    if(BlockState[wanderpoint[0]][wanderpoint[1]] > 0 )
                    {
                        LeadDark[BlockState[wanderpoint[0]][wanderpoint[1]]].surround += light;
                        currentfull = LeadDark[BlockState[wanderpoint[0]][wanderpoint[1]]].surround == LeadDark[BlockState[wanderpoint[0]][wanderpoint[1]]].Value;
                        if(LeadDark[BlockState[wanderpoint[0]][wanderpoint[1]]].lastfull == false && currentfull)
                        {
                            LeadDark[BlockState[wanderpoint[0]][wanderpoint[1]]].lastfull = true;
                            for(j = 0;j < 4;j++)
                            {
                                NoplaceState[wanderpoint[0]+LeadDirection[j][0]][wanderpoint[1]+LeadDirection[j][1]] += light;
                            }
                        }
                        else if(LeadDark[BlockState[wanderpoint[0]][wanderpoint[1]]].lastfull == true && !currentfull)
                        {
                            LeadDark[BlockState[wanderpoint[0]][wanderpoint[1]]].lastfull = false;
                            for(j = 0;j < 4;j++)
                            {
                                NoplaceState[wanderpoint[0]+LeadDirection[j][0]][wanderpoint[1]+LeadDirection[j][1]] += light;
                            }
                        }
                    }
                }
                else
                {
                    wanderpoint[0] = row + LeadDirection[i][0];
                    wanderpoint[1] = col + LeadDirection[i][1];
                }
                while(BlockState[wanderpoint[0]][wanderpoint[1]] < -1)
                {
                    LightState[wanderpoint[0]][wanderpoint[1]] += light;
                    wanderpoint[0] += LeadDirection[i][0];
                    wanderpoint[1] += LeadDirection[i][1];
                }           
            }
        }
        bool simplejudge()
        {
            int n = 0,i = 1,j = 1,k = 2;
            bool outbreak = false,trace = true;
            for(i=1;i < Row-1;i++)
            {
                for(j=1;j < Col-1;j++)
                {
                    if(LightState[i][j] == 0 && BlockState[i][j] == -3)
                    {
                        for(k=0;k < 4;k++)
                        {
                            while(BlockState[i+n*LeadDirection[k][0]][j+n*LeadDirection[k][1]] < -1)
                            {
                                if(BlockState[i+n*LeadDirection[k][0]][j+n*LeadDirection[k][1]] == -3 
                                    && LightState[i+n*LeadDirection[k][0]][j+n*LeadDirection[k][1]] == 0 
                                    && NoplaceState[i+n*LeadDirection[k][0]][j+n*LeadDirection[k][1]] == 0)
                                {
                                    n = 0;
                                    outbreak = true;
                                    trace = false;
                                    break;
                                }
                                n++;
                            }
                            n = 1;
                            if(outbreak)
                            {
                                outbreak = false;
                                break;
                            }
                        }
                        if(trace) return true;
                        else trace = true;
                    }                         
                }
            }
            return false;        
        }
        bool judgeState(int* nextPos)
        {
            // 如果栈非空并且栈顶记录表明当前是在 leaddark 模式（top.Pos[4] == 1）
            if (nextPos[4])
            {
                for(int idx=nextPos[0]-1;idx >= 1;idx--)
                { 
                    // 当且仅当实测灯数 != 要求灯数时视为冲突，需要回溯
                    if(!LeadDark[idx].lastfull)
                    {
                        return true;
                    }
                }
                return false;
            }
            else if(nextPos[0]==1 && nextPos[1]==1 && nextPos[2] == 0)
            {
                for(int idx=LeadDarkNum;idx>=1;idx--)
                { 
                    // 当且仅当实测灯数 != 要求灯数时视为冲突，需要回溯
                    if(!LeadDark[idx].lastfull)
                    {
                        return true;
                    }
                }
                return false && simplejudge();
            }
            else
            {
                // grid 模式：Pos[2] == 2 表示两种方向都试过、无法放置 -> 回溯
                return (nextPos[2] == 2);
            }
        }
        int* TraceBack()
        {   
            int* Pos;         
            Pos = LightStack->pop();
            Lightup(Pos,-1);
            Pos[3]++; 
            return Pos;
        }
        bool CompleteSolver()
        {
            // int n=1;                          //
            int* nextPos = new int[5];
            nextPos[3] = 0;
            nextPos[0] = 1;
            nextPos[1] = 0;
            nextPos[4] = 1;
            nextPos[2] = 0;

            while (nextPos[0] != Row-1 || nextPos[1] != Col-1)
            // while(n < 1000)
            {
                // cout<<"turn:"<<n<<endl;            //
                nextPos = searchpoint(nextPos);
                if(judgeState(nextPos))
                {
                    int* tmp = TraceBack();   // TraceBack 返回的是新分配的数组（与 pop() 配套）
                    delete[] nextPos;         // 释放旧的 nextPos 避免泄漏
                    nextPos = tmp;
                }
                // cout<<"nextPos"<<nextPos[0]<<" "<<nextPos[1]<<" "<<nextPos[2]<<" "<<nextPos[3]<<" "<<nextPos[4]<<endl;
                // n++;                       //
            }

            return true;
        }
        void PrintMap()
        {
            int i=1,j=1;
            for(i = 1;i < Row-1;i++)
            {
                for(j = 1;j < Col-1;j++)
                {
                    if(BlockState[i][j] > 0)
                    {
                        cout << LeadDark[BlockState[i][j]].Value;
                    }
                    else if(BlockState[i][j] == 0)
                    {
                        cout << "0";
                    }
                    else if(BlockState[i][j] == -1)
                    {
                        cout << "X";
                    }
                    else if(BlockState[i][j] == -2)
                    {
                        cout << "L";
                    }
                    else if(BlockState[i][j] == -3)
                    {
                        cout << ".";
                    }
                }
            }
            cout << endl;
        }

        
};

int main()
{
    int row,col;
    char** map;
    cin >> row >> col;
    map = new char*[row];
    for(int i=0;i < row;i++)
    {
        map[i] = new char[col];
    }
    for(int i=0;i < row;i++)
    {
        for(int j=0;j < col;j++)
        {
            cin>>map[i][j];
        }
    }
    AkariSolver Akari(map,row,col);
    if(Akari.CompleteSolver())
    {
        Akari.PrintMap();    
    }
    return 0;
}