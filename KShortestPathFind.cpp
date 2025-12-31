#include <iostream>
#include <string>
using namespace std;

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
        VecList(const VecList<T>& other){
            length = other.length;
            capacity = other.capacity;
            arr = new T[capacity];
            for(int i=0;i<length;i++){
                arr[i] = other.arr[i];
            }
        }
        VecList<T>& operator=(const VecList<T>& other){
            if(this == &other) return *this;
            delete [] arr;
            length = other.length;
            capacity = other.capacity;
            arr = new T[capacity];
            for(int i=0;i<length;i++){
                arr[i] = other.arr[i];
            }
            return *this;
        }
        ~VecList(){
            delete [] arr;
        }
        int getLength() const {
            return length;
        }
        bool isEmpty() const {
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
        T getEleAtPos(int i) const {
            if(i >= length || i < 0)
                throw "Illegal position";
            return arr[i];
        }
        int locateEle(T x) const {
            for(int i=0;i<length;i++){
                if(arr[i]==x)
                    return i;
            }
            return -1;
        }
        void insertLast(T x){
            insertEleAtPos(length, x);
        }
        T& operator[](int i){
             if(i >= length || i < 0)
                throw "Illegal position";
            return arr[i];
        }
        const T& operator[](int i) const {
             if(i >= length || i < 0)
                throw "Illegal position";
            return arr[i];
        }
        void clear(){
            length = 0;
        }
        void printList() const {
            for(int i=0;i<length;i++)
                cout << arr[i] << " ";
        }
};

template <class T>
struct DNode{
    T data;
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
        void push(T x){
            DNode<T>* tmp = new DNode<T>;
            tmp->data = x;
            tmp->next = top;
            top = tmp;
            length++;
        }
        T pop(){
            if(length==0) throw "Stack Empty!";
            DNode<T>* tmp = top;
            top = top->next;
            T tmpData = tmp->data;
            delete tmp;
            length--;
            return tmpData;
        }
        T getTop(){
            if(length==0) throw "Stack Empty!";
            return top->data;
        }
};

template <class T>
struct Edge{
    T start;
    T end;
    int weight;
};

const int INF = 1e9;

struct Path {
    VecList<int> nodes;
    int cost;
};

template <class T>
class AMGraph{ //we need the number of vertices fixed if we are using this approach
    //our edges don't contain weights here.
    private:
        int numVer, numEdge;
        VecList<T> verList; // list of vertices
        int** adjMatrix;
        bool directed;
        
        // Helper to check if two paths are equal
        bool arePathsEqual(const Path& p1, const Path& p2) {
            if (p1.nodes.getLength() != p2.nodes.getLength()) return false;
            for (int i = 0; i < p1.nodes.getLength(); ++i) {
                if (p1.nodes[i] != p2.nodes[i]) return false;
            }
            return true;
        }

    public:
        AMGraph(){ // we don't want this used.
        }
        AMGraph(T* arr, int n, bool dir=false){
            // n for number of vertices
            // default for undirected graph
            // edges to be added later.
            
            numVer = n;
			numEdge = 0;
			for(int i=0;i<n;i++){
				verList.insertLast(arr[i]);
			}
			directed = dir;
			
			adjMatrix = new int*[n];
			for(int i=0;i<n;i++){
				adjMatrix[i] = new int[n];
				for(int j=0;j<n;j++)
					adjMatrix[i][j] = 0;		
			}
        }
        AMGraph(T* arr, int n, Edge<T>** eArr, int e,bool dir=false){
            // n for number of vertices
            // default for undirected graph
            // edges to be added now. 
            
            numVer = n;
			numEdge = 0;
			for(int i=0;i<n;i++){
				verList.insertLast(arr[i]);
			}
			directed = dir;
			
			adjMatrix = new int*[n];
			for(int i=0;i<n;i++){
				adjMatrix[i] = new int[n];
				for(int j=0;j<n;j++)
					adjMatrix[i][j] = 0;			
			}
			
			for(int i=0;i<e;i++){
				addEdge(eArr[i]->start,eArr[i]->end,eArr[i]->weight);
			}
        }
        ~AMGraph(){
            for(int i=0;i<numVer;i++){
            	delete [] adjMatrix[i];
			}
			delete [] adjMatrix;
        }
        void addEdge(Edge<T> e){
            addEdge(e.start,e.end, e.weight);
        }
        void addEdge(T st, T en, int weight=1){
            int sIndex = verList.locateEle(st);
            int eIndex = verList.locateEle(en);
            if(adjMatrix[sIndex][eIndex]!=0) return;
            numEdge++;
            adjMatrix[sIndex][eIndex] = weight;
            if(!directed) adjMatrix[eIndex][sIndex] = weight;
        }
        void removeEdge(Edge<T> e){
            removeEdge(e.start,e.end);            
        }
        void removeEdge(T st, T en){
            int sIndex = verList.locateEle(st);
            int eIndex = verList.locateEle(en);
            if(adjMatrix[sIndex][eIndex]==0) return;
            numEdge--;
            adjMatrix[sIndex][eIndex] = 0;
            if(!directed) adjMatrix[eIndex][sIndex] = 0;
        }
        void printGraph(){
            cout << "Vertices:" << endl;
            for(int i=0;i<numVer;i++)
                cout << verList.getEleAtPos(i) << " ";
                
            cout << endl << "Edges:" << endl;
            char sLeft = (directed ? '<' : '(');
            char sRight = (directed ? '>' : ')');
            for(int i=0;i<numVer;i++){
                for(int j=i+1;j<numVer;j++){
                    if(adjMatrix[i][j] !=0) cout << sLeft << verList.getEleAtPos(i) << "," << verList.getEleAtPos(j) << sRight << ", weight = " <<  adjMatrix[i][j]<<endl; 
                }
            }
            if(!directed) return;
            for(int i=0;i<numVer;i++){
                for(int j=0;j<i;j++){
                    if(adjMatrix[i][j] !=0) cout << sLeft << verList.getEleAtPos(i) << "," << verList.getEleAtPos(j) << sRight << ", weight = " <<  adjMatrix[i][j]<<endl; 
                }
            }
        }
        int** getMatrix(){
            return adjMatrix; 
        }
        int getNumVer(){
            return numVer;
        }
        
        // Dijkstra's algorithm
        bool AdjDijkstra(int start, int end, bool* bannedNodes, Path& resultPath) {
            int* dist = new int[numVer];
            int* parent = new int[numVer];
            bool* visited = new bool[numVer];

            for(int i=0;i<numVer;i++) {
                dist[i] = INF;
                parent[i] = -1;
                visited[i] = false;
            }

            if (bannedNodes[start] || bannedNodes[end]) {
                delete[] dist; delete[] parent; delete[] visited;
                return false;
            }

            dist[start] = 0;

            for (int i=0;i<numVer;i++) 
            {
                int u = -1;
                int minDist = INF;
                for (int j=0;j<numVer;j++) 
                {
                    if (!visited[j] && dist[j] < minDist) {
                        u = j;
                        minDist = dist[j];
                    }
                }
                if (u == -1 || dist[u] == INF) break;
                if (u == end) break;
                visited[u] = true;

                for (int v=0;v<numVer;v++) 
                {
                    if (adjMatrix[u][v] != 0) 
                    { // There is an edge
                        if (bannedNodes[v]) continue;

                        if (dist[u] + adjMatrix[u][v] < dist[v]) {
                            dist[v] = dist[u] + adjMatrix[u][v];
                            parent[v] = u;
                        }
                    }
                }
            }

            if (dist[end] == INF) {
                delete[] dist; delete[] parent; delete[] visited;
                return false;
            }

            resultPath.cost = dist[end];
            resultPath.nodes.clear();
            
            LinkStack<int> s;
            int current = end;
            while (current != -1) {
                s.push(current);
                current = parent[current];
            }
            
            while(!s.isEmpty()){
                resultPath.nodes.insertLast(s.pop());
            }

            delete[] dist; delete[] parent; delete[] visited;
            return true;
        }

        // Yen's Algorithm with Constraints
        VecList<Path> KShortestPathsFind(int start, int end, int K, int maxTrans, VecList<int>& globalBannedNodes) {
            VecList<Path> A;
            VecList<Path> B; 
            VecList<Path> validPaths; 

            bool* bannedNodes = new bool[numVer];
            for(int i=0;i<numVer;i++) bannedNodes[i] = false;

            // Prepare banned nodes for Dijkstra (exclude start/end)
            for(int i=0; i<globalBannedNodes.getLength(); i++) 
            {
                int node = globalBannedNodes[i];
                if (node != start && node != end) 
                    bannedNodes[node] = true;
            }

            Path p0;
            
            if (AdjDijkstra(start, end, bannedNodes, p0)) 
            {
                A.insertLast(p0);
                if (maxTrans < 0 || (p0.nodes.getLength() - 2) <= maxTrans) 
                    validPaths.insertLast(p0);
            } 
            else 
            {
                delete[] bannedNodes;
                return validPaths;
            }

            int k = 1;
            while (validPaths.getLength() < K) 
            {
                if (k > A.getLength()) break; 

                Path prevPath = A[k - 1];
                
                for (int i=0;i<prevPath.nodes.getLength() - 1;i++)
                {
                    int spurNode = prevPath.nodes[i];
                    VecList<int> rootPathNodes;
                    int rootPathCost = 0;

                    for (int j=0;j<=i;j++) 
                    {
                        int node = prevPath.nodes[j];
                        rootPathNodes.insertLast(node);
                        if (j > 0) {
                            int prev = prevPath.nodes[j - 1];
                            rootPathCost += adjMatrix[prev][node];
                        }
                    }

                    // Temporarily remove edges
                    VecList<Edge<int>> removedEdges;
                    for (int pIdx = 0; pIdx < A.getLength(); ++pIdx) 
                    {
                        Path p = A[pIdx];
                        if (p.nodes.getLength() > i + 1) {
                            bool sameRoot = true;
                            for (int j=0;j<=i;j++) {
                                if (p.nodes[j] != rootPathNodes[j]) {
                                    sameRoot = false;
                                    break;
                                }
                            }
                            if (sameRoot) {
                                int u = p.nodes[i];
                                int v = p.nodes[i + 1];
                                if(adjMatrix[u][v] != 0) {
                                    Edge<int> e; e.start = u; e.end = v; e.weight = adjMatrix[u][v];
                                    removedEdges.insertLast(e);
                                    adjMatrix[u][v] = 0;
                                    if(!directed) adjMatrix[v][u] = 0;
                                }
                            }
                        }
                    }

                    // Temporarily ban nodes in root path
                    for (int j=0;j<i;j++) 
                    {
                        int node = rootPathNodes[j];
                        if(node != end)
                             bannedNodes[node] = true;
                    }

                    Path spurPath;
                    if (AdjDijkstra(spurNode, end, bannedNodes, spurPath)) 
                    {
                        Path totalPath;
                        for(int j=0; j<rootPathNodes.getLength(); j++)
                            totalPath.nodes.insertLast(rootPathNodes[j]);
                        
                        totalPath.nodes.deleteEleAtPos(totalPath.nodes.getLength()-1);
                        
                        for(int j=0;j<spurPath.nodes.getLength();j++)
                            totalPath.nodes.insertLast(spurPath.nodes[j]);
                        
                        totalPath.cost = rootPathCost + spurPath.cost;

                        bool exists = false;
                        for(int bIdx=0;bIdx<B.getLength();bIdx++){
                            if(arePathsEqual(B[bIdx], totalPath)){
                                exists = true;
                                break;
                            }
                        }
                        if(!exists){
                            B.insertLast(totalPath);
                        }
                    }

                    // Restore edges
                    for(int r=0; r<removedEdges.getLength(); r++)
                    {
                        Edge<int> e = removedEdges[r];
                        adjMatrix[e.start][e.end] = e.weight;
                        if(!directed) adjMatrix[e.end][e.start] = e.weight;
                    }

                    // Unban nodes in root path
                    for (int j=0;j<i;j++) 
                    {
                        int node = rootPathNodes[j];
                        // Only unban if it wasn't globally banned
                        bool globallyBanned = false;
                        for(int g=0; g<globalBannedNodes.getLength(); g++){
                            if(globalBannedNodes[g] == node) {
                                globallyBanned = true;
                                break;
                            }
                        }
                        if(!globallyBanned && node != end)
                            bannedNodes[node] = false;
                    }
                }

                if (B.isEmpty()) break;

                int minIdx = -1;
                int minCost = INF;
                for(int i=0; i<B.getLength(); i++)
                {
                    if(B[i].cost < minCost){
                        minCost = B[i].cost;
                        minIdx = i;
                    }
                }
                
                if(minIdx != -1)
                {
                    Path bestPath = B[minIdx];
                    A.insertLast(bestPath);
                    B.deleteEleAtPos(minIdx);
                    
                    if (maxTrans < 0 || (bestPath.nodes.getLength() - 2) <= maxTrans) {
                        validPaths.insertLast(bestPath);
                    }
                }
                else break;
                k++;
            }
            delete[] bannedNodes;
            return validPaths;
        }
};

int getIndex(string* names, int n, const string& name) {
    for (int i = 0; i < n; i++) {
        if (names[i] == name) return i;
    }
    return -1;
}

int main() {
    int M, N;
    cin >> M >> N;
    string* namesArr = new string[M];
    for (int i = 0; i < M; i++) {
        cin >> namesArr[i];
    }
    AMGraph<string> g(namesArr, M, false); // Undirected
    for (int i = 0; i < N; i++) 
    {
        string S1, S2;
        int w;
        cin >> S1 >> S2 >> w;
        g.addEdge(S1, S2, w);
    }

    string command;
    VecList<int> bannedIndices;
    int maxTrans = -1;
    cout << "Please enter your next request." << endl;
    cout << "Options include: ban X, unban X, maxTrans Y, paths A B k, quit." << endl;
    while (true) 
    {
        cin >> command;
        if (command == "quit") 
        {
            break;
        } 
        else if (command == "ban") 
        {
            string s;
            cin >> s;
            int idx = getIndex(namesArr, M, s);
            if (idx != -1) {
                // Check if already banned
                bool alreadyBanned = false;
                for(int i=0; i<bannedIndices.getLength(); i++){
                    if(bannedIndices[i] == idx) {
                        alreadyBanned = true;
                        break;
                    }
                }
                if(!alreadyBanned){
                    bannedIndices.insertLast(idx);
                }
            }
        } 
        else if (command == "unban") 
        {
            string s;
            cin >> s;
            int idx = getIndex(namesArr, M, s);
            if (idx != -1) {
                int pos = bannedIndices.locateEle(idx);
                if (pos != -1) {
                    bannedIndices.deleteEleAtPos(pos);
                }
            }
        } 
        else if (command == "maxTrans") 
        {
            cin >> maxTrans;
        } 
        else if (command == "paths") 
        {
            string s1, s2;
            int k;
            cin >> s1 >> s2 >> k;
            int start = getIndex(namesArr, M, s1);
            int end = getIndex(namesArr, M, s2);

            if (start != -1 && end != -1) 
            {
                VecList<Path> paths = g.KShortestPathsFind(start, end, k, maxTrans, bannedIndices);
                
                cout << "There are " << paths.getLength() << " paths." << endl;
                for (int i = 0; i < paths.getLength(); i++) {
                    cout << "Path " << i << ": ";
                    Path p = paths[i];
                    for (int j = 0; j < p.nodes.getLength(); j++) {
                        cout << namesArr[p.nodes[j]] << (j == p.nodes.getLength() - 1 ? "" : " -> ");
                    }
                    cout << ", distance = " << p.cost << endl;
                }
            } 
            else 
            {
                cout << "There are 0 paths." << endl;
            }
        }
        else 
        {
            cout << "Invalid command." << endl;
        }
        cout << endl << "Please enter your next request." << endl;
        cout << "Options include: ban X, unban X, maxTrans Y, paths A B k, quit." << endl;
    }
    
    delete[] namesArr;
    return 0;
}
