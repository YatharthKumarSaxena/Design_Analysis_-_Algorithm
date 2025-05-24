#include <iostream>
#include <climits>
using namespace std;

class Graph{
    int v;
    int** graph;
public:
    Graph(int v){
        this->v = v;
        graph = new int*[v];
        for(int i=0;i<v;i++){
            graph[i] = new int[v];
        }
        for(int i=0;i<v;i++){
            for(int j=0;j<v;j++){
                graph[i][j] = 0;
            }
        }
    }
    void displayGraph();
    void addEdge(int src,int des,int weight);
    int totalVertices();
    void totalStronglyConnectedComponents();
    void DFSdisplay(int src,int& count,int* pre,int* post,bool* visited,int* parent);
    ~Graph(){
        for(int i=0;i<v;i++){
            delete[] graph[i];
        }
        delete[] graph;
    }
};

void Graph::totalStronglyConnectedComponents(){
    bool* visited = new bool[v];
    int* post = new int[v];
    int* pre = new int[v];
    int* parent = new int[v];
    for(int i=0;i<v;i++){
        visited[i] = false;
        pre[i] = -1;
        post[i] = -1;
        parent[i] = -1;
    }
    int count=0;
    cout<<"\nComplete DFS Traversal is given below:-\n";
    for(int i=0;i<v;i++){
        if(visited[i] == false)DFSdisplay(i,count,pre,post,visited,parent);
    }
    int** reverseGraph = new int*[v];
    for(int i=0;i<v;i++){
        reverseGraph[i] = new int[v];
    }
    cout<<endl;
    // Taking Transpose of Graph
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
            reverseGraph[i][j] = graph[j][i];
        }
    }
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
            graph[i][j] = reverseGraph[j][i];
        }
    }
    int* alterPost = new int[v];
    for(int i=0;i<v;i++){
        visited[i] = false;
        alterPost[i] = -1;
    }
    int c = 0;
    int scc = 1;
    while(true){
        int loop = 0;
        int maxPost = -1;
        int src = -1;
        for(int i=0;i<v;i++){
            if(maxPost<post[i] && visited[i] == false){
                maxPost = post[i];
                src = i;
            }
        }
        if(src != -1){
            cout<<scc<<"th Strongly Connected Component is displayed below:-\n";
            DFSdisplay(src,c,pre,alterPost,visited,parent);
            cout<<endl;
            scc += 1;
        }
        else break;
        for(int i=0;i<v;i++){
            if(visited[i])loop++;
        }
        if(loop == v)break;
    }
    
    cout<<"\nTotal Strongly Connected Components Present in Your Graph :- "<<scc-1<<endl;
    // Taking Transpose of Graph
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
            reverseGraph[i][j] = graph[j][i];
        }
    }
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
            graph[i][j] = reverseGraph[j][i];
        }
    }
    
    for(int i=0;i<v;i++) delete[] reverseGraph[i];
    delete[] reverseGraph;
    delete[] pre;
    delete[] post;
    delete[] parent;
    delete[] visited;
}

void Graph::DFSdisplay(int src,int& count,int* pre,int* post,bool* visited,int* parent){
    if(count>=2*v)return;
    visited[src] = true;
    cout<<src<<" ";
    pre[src] = count;
    count = count+1;
    for(int i=0;i<v;i++){
        if(graph[src][i] && visited[i]==false){
            parent[i] = src;
            DFSdisplay(i,count,pre,post,visited,parent);
        }
    }
    post[src] = count;
    count = count+1;
}

int Graph::totalVertices(){
    return v;
}

void Graph::displayGraph(){
    cout<<"  ";
    for(int i=0;i<v;i++){
        cout<<i<<" ";
    }
    cout<<endl;
    for(int i=0;i<v;i++){
        cout<<i<<' ';
        for(int j=0;j<v;j++){
            cout<<graph[i][j]<<" ";
        }
        cout<<endl;
    }
}

void Graph::addEdge(int src,int des,int weight){
    if(src>=v || des >=v){
        cout<<"Invalid Vertices Entered by You\n";
        return;
    }
    graph[src][des] = weight;
    cout<<"Edge added successfully\n";
}

Graph makeGraph(){
    cout<<"Please enter the total number of vertices in your Graph:- ";
    int v;
    cin>>v;
    Graph G(v);
    while(true){
        int choice;
        cout<<"Press 0 to exit adding edges process\n";
        cout<<"Press 1 to continue adding edges process\n";
        cout<<"\nPlease enter your choice:- ";
        cin>>choice;
        if(!choice)break;
        else{
            int src,des,weight;
            cout<<"Please enter the Source Node:- ";
            cin>>src;
            cout<<"Please enter the Destination Node:- ";
            cin>>des;
            cout<<"Please enter the weight of Edge:- ";
            cin>>weight;
            G.addEdge(src,des,weight);
        }
    }
    cout<<"\nYour Graph is Created Successfully\n";
    return G;
}

int main() {
    cout << "\nWelcome to the World of Programming\n";
    cout << "Program is based on Kosaraju algorithm to find total number of Strongly Connected Components using DFS Using Pre and Post Method\n";

    // Create a graph with 18 vertices (0 to 17)
    Graph G(18);

    // 🧩 SCC 1: 0 -> 1 -> 2 -> 0
    G.addEdge(0, 1, 1);
    G.addEdge(1, 2, 1);
    G.addEdge(2, 0, 1);

    // 🧩 SCC 2: 3 -> 4 -> 5 -> 3
    G.addEdge(3, 4, 1);
    G.addEdge(4, 5, 1);
    G.addEdge(5, 3, 1);

    // 🧩 SCC 3: 6 -> 7 -> 8 -> 6 -> 9
    G.addEdge(6, 7, 1);
    G.addEdge(7, 8, 1);
    G.addEdge(8, 6, 1);
    G.addEdge(6, 9, 1); // 9 is not in cycle

    // 🧩 SCC 4: 10 -> 11 -> 12 -> 10
    G.addEdge(10, 11, 1);
    G.addEdge(11, 12, 1);
    G.addEdge(12, 10, 1);

    // 🧩 SCC 5: 13 -> 14 -> 15 -> 16 -> 13 (includes node 17 as tail)
    G.addEdge(13, 14, 1);
    G.addEdge(14, 15, 1);
    G.addEdge(15, 16, 1);
    G.addEdge(16, 13, 1);
    G.addEdge(16, 17, 1); // 17 is tail node (not part of SCC)

    // Display adjacency matrix
    cout << "\nAdjacency Matrix of the Graph:\n";
    G.displayGraph();

    // Call Kosaraju-based SCC detection
    G.totalStronglyConnectedComponents();

    return 0;
}
