// Brute Force Bridge Detection DFS Approach

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
    void DFSdisplay(int src,int& count,int* pre,int* post,bool* visited,int* parent);
    bool checkPathExistBetweenTwoNodes(int node1,int node2);
    void bridgeDetection();
    ~Graph(){
        for(int i=0;i<v;i++){
            delete[] graph[i];
        }
        delete[] graph;
    }
};

void Graph::bridgeDetection(){
    bool bridgeExist = false;
    for(int i=0;i<v;i++){
        for(int j=0;j<i;j++){
            if(graph[i][j]){
                graph[i][j] = 0;
                graph[j][i] = 0;
                bool bridgeCheck = !checkPathExistBetweenTwoNodes(i,j);
                if(bridgeCheck){
                    bridgeExist = true;
                    cout<<"Edge ("<<i<<","<<j<<") is a Bridge\n";
                }
                graph[i][j] = 1;
                graph[j][i] = 1;
            }
        }
    }
    if(!bridgeExist){
        cout<<"No Bridge Exist\n";
    }
}

bool Graph::checkPathExistBetweenTwoNodes(int node1,int node2){
    if(node1>=v || node2>=v)return false;
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
    DFSdisplay(node1,count,pre,post,visited,parent);
    if(visited[node1] && visited[node2])return true;
    for(int i=0;i<v;i++){
        visited[i] = false;
        pre[i] = -1;
        post[i] = -1;
        parent[i] = -1;
    }
    count = 0;
    DFSdisplay(node2,count,pre,post,visited,parent);
    if(visited[node1] && visited[node2])return true;

    delete[] pre;
    delete[] post;
    delete[] parent;
    delete[] visited;

    return false;
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
    cout << "\nWelcome to the World of Programming\n";
    cout << "Program detects Bridges using Brute Force DFS\n";

    // Graph with 6 vertices (0 to 5)
    Graph G(6);

    // Undirected Edges with 5 bridges
    G.addEdge(0, 1, 1);   // Bridge
    G.addEdge(1, 2, 1);   // Bridge
    G.addEdge(2, 3, 1);   // Bridge
    G.addEdge(3, 4, 1);   // Bridge
    G.addEdge(1, 5, 1);   // Bridge

    cout << "\nAdjacency Matrix of the Graph:\n";
    G.displayGraph();

    cout << "\nBridges in the Graph:\n";
    G.bridgeDetection();

    return 0;
}
