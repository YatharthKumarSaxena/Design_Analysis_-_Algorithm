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
    int totalVertices();\
    void dijkstraAlgorithm();
};

int Graph::totalVertices(){
    return v;
}

void Graph::dijkstraAlgorithm(){
    int src;
    cout<<"Please enter your Source Node:- ";
    cin>>src;
    int vertices = this->totalVertices();
    int* dis = new int[vertices];
    bool* visited = new bool[vertices];
    for(int i=0;i<vertices;i++){
        dis[i] = INT_MAX;
        visited[i] = false;
    }
    dis[src] = 0;
    int count = 0; // Count Visited Vertices
    while(count<vertices){
        int u;
        int tempDis = INT_MAX;
        for(int i=0;i<v;i++){
            if(visited[i]==true)continue;
            if(dis[i]==INT_MAX)continue;
            if(visited[i]==false){
                if(dis[i]<tempDis){
                    u=i;
                    tempDis = dis[i];
                }
            }
        }
        if(tempDis == INT_MAX){
            break; // No more reachable nodes
        }
        visited[u] = true;
        for(int i=0;i<v;i++){
            if(visited[i]==false){
                if(graph[u][i]!=0 && dis[i]>(graph[u][i]+dis[u])){
                    dis[i] = dis[u] + graph[u][i];
                }
            }
        }
        count++;
    }
    cout<<"\nShortest Distance from Source Node "<<src<<"to Destination Node is given below:- \n";
    for(int i=0;i<vertices;i++){
        cout<<src<<"-> "<<i<<" : "<<dis[i]<<endl;
    }
    return;
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
    if(src>=v || des >=v)cout<<"Invalid Vertices Entered by You\n";
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

int main(){
    cout<<"\nWelcome to the World of Programming\n";
    cout<<"Program is based on Dijkstra Algorithm\n";
    Graph G = makeGraph();
    G.dijkstraAlgorithm();
    return 0;
}
