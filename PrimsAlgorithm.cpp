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
    void primsAlgorithm();
};

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

void Graph::primsAlgorithm(){
    int v = totalVertices();
    bool* visited = new bool[v];
    int* nbr = new int[v];
    int* dist = new int[v];
    for(int i=0;i<v;i++){
        visited[i] = false;
        dist[i] = INT_MAX;
        nbr[i] = -1;
    }
    visited[0] = true;
    for(int i=0;i<v;i++){
        if(graph[0][i]!=0){
            nbr[i] = 0;
            dist[i] = graph[0][i];
        }
    }
    int cost = 0;
    int i = v-1;
    while(i>0){
        int u = -1;
        int tempDis = INT_MAX;
        for(int j=0;j<v;j++){
            if(visited[j]==false){
                if(dist[j]<tempDis){
                    tempDis = dist[j];
                    u = j;
                }
            }
        }
        cout << "Edge taken: " << u << "--" << nbr[u] << " with weight: " << dist[u] << endl;
        if(u==-1 || tempDis == INT_MAX)break;
        cost += dist[u];
        visited[u] = true;
        for(int j=0;j<v;j++){
            if(visited[j]==false && graph[u][j]!=0){
                if(dist[j]>graph[u][j]){
                    dist[j] = graph[u][j];
                    nbr[j] = u;
                }
            }
        }
        i--;
    }
    cout<<"\nTotal Cost of Minimum Spanning Tree Obtained:- "<<cost;
    delete[] visited;
    delete[] nbr;
    delete[] dist;
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
    cout<<"This Program is dedicated to explore Prims Algorithm\n";

    // Create a graph with 5 vertices
    Graph G(5);

    // Manually add edges (Undirected and Weighted)
    G.addEdge(0, 1, 2);
    G.addEdge(0, 3, 3);
    G.addEdge(0, 4, 6);
    G.addEdge(1, 2, 1);
    G.addEdge(2, 4, 5);
    G.addEdge(2, 0, 4);

    // Display the graph (optional)
    G.displayGraph();

    // Run Prim's Algorithm
    G.primsAlgorithm();
    
    return 0;
}
