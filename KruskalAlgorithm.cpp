// Failed Implementation of Kruskal using Components Array Without DSU Data Structure
// This Algorithm can fail as sometimes it could not detect the cycles properly

#include <iostream>
#include <climits>
using namespace std;

class Edge{
public:
    int src;
    int des;
    int weight;
    Edge(){

    }
    Edge(int src,int des,int weight){
        this->src = src;
        this->des = des;
        this->weight = weight;
    }
};

void sortEdge(Edge* edges,int totalEdges){
    for(int i=0;i<totalEdges-1;i++){
        bool flag = true;
        for(int j=0;j<totalEdges-i-1;j++){
            if(edges[j].weight>edges[j+1].weight){
                Edge temp = edges[j];
                edges[j] = edges[j+1];
                edges[j+1] = temp;
                flag = false;
            }
        }
        if(flag)break;
    }
}

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
    void kruskalAlgorithm();
    int totalEdges();
    Edge* createEdgeList();
};

int Graph::totalVertices(){
    return v;
}

int Graph::totalEdges(){
    int edgeCount = 0;
    for(int i=0;i<v;i++){
        for(int j=0;j<i;j++){
            if(graph[i][j])edgeCount++;
        }
    }
    return edgeCount;
}

Edge* Graph::createEdgeList(){
    int edgeCount = totalEdges();
    Edge* edges = new Edge[edgeCount];
    int k = 0;
    for(int i=0;i<v;i++){
        for(int j=0;j<i;j++){
            if(graph[i][j]){
                Edge e(i,j,graph[i][j]);
                edges[k++] = e;
            }
        }
    }
    return edges;
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

void Graph::kruskalAlgorithm(){
    Edge* edges = createEdgeList();
    int edgeCount = totalEdges();
    sortEdge(edges,edgeCount);
    int* components = new int[v];
    for(int i=0;i<v;i++){
        components[i] = i;
    }
    int cost = 0;
    int i = v-1;
    int idx = 0;
    while(i>0){
        int v1 = edges[idx].src;
        int v2 = edges[idx].des;
        if(components[v1]!=components[v2]){
            cost+=edges[idx].weight;
            for(int j=0;j<v;j++){
                cout<<components[j];
                if(components[j]==components[v2]){
                    components[j] = components[v1];
                }
            }
            cout<<endl;
            cout<<"Edge taken:- "<<v1<<"--"<<v2<<" having weight :- "<<edges[idx].weight<<endl;
            i--;
        }
        idx++;
    }
    cout<<"\nTotal Cost of Minimum Spanning Tree Obtained:- "<<cost;
    delete[] components;
    delete[] edges;
}

void Graph::addEdge(int src,int des,int weight){
    if(src>=v || des >=v)cout<<"Invalid Vertices Entered by You\n";
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
    cout << "This Program is dedicated to explore Kruskal Algorithm\n";

    // Option 1: Manual Entry (used currently)
    Graph G(5);
    G.addEdge(0, 1, 2);
    G.addEdge(0, 3, 3);
    G.addEdge(0, 4, 6);
    G.addEdge(1, 2, 1);
    G.addEdge(2, 4, 5);
    G.addEdge(0, 2, 4);

    // Option 2: Enable this for user input
    // Graph G = makeGraph();

    G.displayGraph();
    G.kruskalAlgorithm();

    return 0;
}
