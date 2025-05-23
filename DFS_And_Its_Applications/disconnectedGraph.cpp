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
    bool disconnected = false;
    DFSdisplay(src,count,pre,post,visited,parent);
    cout<<endl;
    for(int i=0;i<v;i++){
        if(visited[i] == false)disconnected = true;
    }

    if(disconnected){
        cout<<"Your Graph is disconnected\n";
    }
    else{
        cout<<"Your Graph is not disconnected\n";
    }
    
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
    cout<<"Program is dedicated to find whether a graph is disconnected or not by Depth First Search Using Pre and Post Method\n";

    // Create a graph with 5 vertices (0 to 4)
    Graph G(5);

    // Hardcoded Edges
    G.addEdge(0, 1, 1);
    G.addEdge(0, 2, 1);
    // G.addEdge(1, 3, 1);
    G.addEdge(1, 4, 1);

    cout << "\nAdjacency Matrix of the Graph:\n";
    G.displayGraph();

    cout << "\nDFS Traversal starting from vertex 0:\n";
    G.DFS(0);

    return 0;
}
