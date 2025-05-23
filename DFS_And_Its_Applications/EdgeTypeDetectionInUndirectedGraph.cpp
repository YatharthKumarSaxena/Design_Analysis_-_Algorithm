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
    void DFS(int src,int& count,int* pre,int* post,bool* visited,int* parent);
    void edgeTypeDetection();
    ~Graph(){
        for(int i=0;i<v;i++){
            delete[] graph[i];
        }
        delete[] graph;
    }
};

void Graph::edgeTypeDetection(){
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
    DFS(0,count,pre,post,visited,parent);
    for(int i=0;i<v;i++){
        for(int j=0;j<i;j++){
            if(graph[i][j]){ // Means Edge Exist
                if(parent[j] == i){
                    cout<<"Edge ("<<i<<","<<j<<") is Tree Edge\n";
                }
                else if(pre[i]<pre[j] && post[i]>post[j]){
                    cout<<"Edge ("<<i<<","<<j<<") is Forward Edge\n";
                }
                else if(pre[i]>pre[j] && post[i]<post[j]){
                    cout<<"Edge ("<<i<<","<<j<<") is Backward Edge\n";
                }
                else{
                    cout<<"Edge ("<<i<<","<<j<<") is Cross Edge\n";
                }
            }
        }
    }
    
    delete[] pre;
    delete[] post;
    delete[] parent;
    delete[] visited;
}

void Graph::DFS(int src,int& count,int* pre,int* post,bool* visited,int* parent){
    if(count>=2*v)return;
    visited[src] = true;
    pre[src] = count;
    count = count+1;
    for(int i=0;i<v;i++){
        if(graph[src][i] && visited[i]==false){
            parent[i] = src;
            DFS(i,count,pre,post,visited,parent);
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
    cout<<"Program is dedicated to find type of each edge in undirected Graph by Depth First Search Using Pre and Post Method\n";
    cout<<"This Program tells about the type of edge:- Backward Edge and Tree Edge\n";
    
    Graph G(9); // 9 vertices (0 to 8)

    // Add 20 edges
    G.addEdge(0, 1, 1);  // Tree
    G.addEdge(0, 2, 1);  // Tree
    G.addEdge(1, 3, 1);  // Tree
    G.addEdge(1, 4, 1);  // Tree
    G.addEdge(2, 5, 1);  // Tree
    G.addEdge(3, 0, 1);  // Backward
    G.addEdge(4, 1, 1);  // Backward
    G.addEdge(4, 6, 1);  // Tree
    G.addEdge(5, 2, 1);  // Backward
    G.addEdge(5, 7, 1);  // Tree
    G.addEdge(6, 3, 1);  // Cross
    G.addEdge(7, 4, 1);  // Cross
    G.addEdge(7, 8, 1);  // Tree
    G.addEdge(8, 5, 1);  // Backward
    G.addEdge(2, 4, 1);  // Forward
    G.addEdge(0, 6, 1);  // Forward
    G.addEdge(8, 6, 1);  // Cross
    G.addEdge(3, 7, 1);  // Cross
    G.addEdge(6, 8, 1);  // Forward
    G.addEdge(1, 5, 1);  // Forward

    cout << "\nAdjacency Matrix of the Graph:\n";
    G.displayGraph();
    cout<<endl;
    G.edgeTypeDetection();

    return 0;
}
