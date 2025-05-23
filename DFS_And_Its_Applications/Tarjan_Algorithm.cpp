// Optimal Articulation Point Algorithm


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
    void DFS(int src);
    void DFSdisplay(int src,int& count,int* pre,int* post,bool* visited,int* parent);
    void findArticulationPoint();
    ~Graph(){
        for(int i=0;i<v;i++){
            delete[] graph[i];
        }
        delete[] graph;
    }
};

void Graph::DFS(int src){
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
    DFSdisplay(src,count,pre,post,visited,parent);
    
    int par;
    for(int i=0;i<v;i++){
        if(parent[i] == -1)par = i;
    }
    int countChildOfRoot = 0;
    for(int i=0;i<v;i++){
        if(parent[i] == par)countChildOfRoot++;
    }
    if(countChildOfRoot>1)cout<<"\nNode "<<par<<" is the Articulation Point";


    delete[] pre;
    delete[] post;
    delete[] parent;
    delete[] visited;
}

void Graph::DFSdisplay(int src,int& count,int* pre,int* post,bool* visited,int* parent){
    if(count>=2*v)return;
    visited[src] = true;
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

void Graph::findArticulationPoint(){
    for(int i=0;i<v;i++){
        DFS(i);
    }
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
    graph[des][src] = weight;
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

int main(){
    cout<<"\nWelcome to the World of Programming\n";
    cout<<"Program is dedicated to find Articulation Points Using Tarjan's Algorithm \nIt uses Depth First Search Using Pre and Post Method\n";

    Graph G(5);

    // 🔗 Test Case: Expected articulation points = 0, 2, 3
    G.addEdge(0, 1, 1);  // 0-1
    G.addEdge(0, 2, 1);  // 0-2
    G.addEdge(2, 3, 1);  // 2-3
    G.addEdge(3, 4, 1);  // 3-4

    cout << "\nAdjacency Matrix of the Graph:\n";
    G.displayGraph();

    G.findArticulationPoint();  

    return 0;
}