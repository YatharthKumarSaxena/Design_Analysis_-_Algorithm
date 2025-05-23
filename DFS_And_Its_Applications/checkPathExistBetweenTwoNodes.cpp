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
    ~Graph(){
        for(int i=0;i<v;i++){
            delete[] graph[i];
        }
        delete[] graph;
    }
};

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

int main(){
    cout << "\nWelcome to the World of Programming\n";
    cout << "Program is based on check there exist a path between two nodes, Depth First Search Using Pre and Post Method\n";

    // Graph with 6 vertices (0 to 5)
    Graph G(6);

    // Directed Edges
    G.addEdge(0, 1, 1);
    G.addEdge(0, 2, 1);
    G.addEdge(1, 3, 1);
    G.addEdge(1, 4, 1);
    G.addEdge(4, 2, 1);
    G.addEdge(3, 0, 1);

    // Node 5 is disconnected (no outgoing or incoming edge)

    cout << "\nAdjacency Matrix of the Graph:\n";
    G.displayGraph();

    cout << "\n\nChecking Path Existence Between Nodes:\n";

    // Example 1: Path exists from 0 -> 3
    cout << "Is there a path between 0 and 3 (in any direction)? ";
    cout << (G.checkPathExistBetweenTwoNodes(0, 3) ? "Yes" : "No") << endl;

    // Example 2: Path exists from 3 -> 0
    cout << "Is there a path between 3 and 0 (in any direction)? ";
    cout << (G.checkPathExistBetweenTwoNodes(3, 0) ? "Yes" : "No") << endl;

    // Example 3: Path between 2 and 4
    cout << "Is there a path between 2 and 4 (in any direction)? ";
    cout << (G.checkPathExistBetweenTwoNodes(2, 4) ? "Yes" : "No") << endl;

    // Example 4: Path between 1 and 2
    cout << "Is there a path between 1 and 2 (in any direction)? ";
    cout << (G.checkPathExistBetweenTwoNodes(1, 2) ? "Yes" : "No") << endl;

    // Example 5: Path between 0 and 5
    cout << "Is there a path between 0 and 5 (in any direction)? ";
    cout << (G.checkPathExistBetweenTwoNodes(0, 5) ? "Yes" : "No") << endl;

    // Example 6: Path between 5 and 2
    cout << "Is there a path between 5 and 2 (in any direction)? ";
    cout << (G.checkPathExistBetweenTwoNodes(5, 2) ? "Yes" : "No") << endl;
    
    return 0;
}
