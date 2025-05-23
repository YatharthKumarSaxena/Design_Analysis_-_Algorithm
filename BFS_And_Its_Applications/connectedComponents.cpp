#include <iostream>
#include <queue>
using namespace std;

class Node{
public:
    int val;
    char color;
    Node(){
        color = 'w';
    }
    Node(int val,char color){
        this->val = val;
        this->color = color;
    }
};

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
    void BFSdisplay(int src,Node* nodes);
    int totalConnectedComponents();
};

int Graph::totalVertices(){
    return v;
}

void Graph::displayGraph(){
    cout<<"\nYour Graph in Adjacency Matrix form looks as given below:-\n";
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

void Graph::BFSdisplay(int src,Node* nodes){
    cout << "\nBFS Traversal starting from Node "<<src<<" :- ";
    nodes[src].color = 'g'; // Mark Source Node as Gray Color as it will be Pushed into Queue
    queue<int>qu;
    qu.push(src);
    while(!qu.empty()){
        int ele = qu.front();
        qu.pop();
        cout<<ele<<" ";
        for(int i=0;i<v;i++){
            if(graph[ele][i]){
                if(nodes[i].color == 'w'){ // Means Node is not pushed in Queue
                    qu.push(i);
                    nodes[i].color = 'g'; // Marked Color of Nofde as Gray when pushed into Queue
                }
            }
        }
        nodes[ele].color = 'b'; // Marked Color of Node as Black means all its Neighbours are Explored
    }
    return;
}

int Graph::totalConnectedComponents(){
    Node* nodes = new Node[v];
    for(int i=0;i<v;i++){
        nodes[i].val = i;
    }
    int count = 0;
    for(int i=0;i<v;i++){
        if(nodes[i].color == 'w'){
            this->BFSdisplay(i,nodes);
            count++;
        }
    }
    return count;
}

int main() {
    cout << "\nWelcome to the World of Programming\n";
    cout << "This Program is dedicated to find total number of connected components in Graph by BFS Algorithm using the Colouring Scheme\n";

    Graph G(7);  // 7 vertices: 0 to 6

    // Hardcoded edges to form two disconnected components
    G.addEdge(0, 1, 1);
    G.addEdge(1, 2, 1);

    G.addEdge(3, 4, 1);

    // Node 5 and 6 are completely isolated

    // Display Graph
    G.displayGraph();

    cout<<"\nTotal number of Connected Components in your Graph:- "<<G.totalConnectedComponents()<<endl;

    return 0;
}