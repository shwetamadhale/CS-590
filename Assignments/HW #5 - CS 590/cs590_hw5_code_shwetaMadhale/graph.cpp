//Shweta Madhale, CWID : 20015921
/**
Provide an implementation in C++ of the DFS, and BFS algorithms. 
You are given a class declaration in the header file graph.h, which you should implement in graph.cpp. 
You should strictly implement the method signatures provided in the header file. 
As you will see in the skeleton code provided, an Adjacency Matrix representation is used for the graphs. 
We assume that nodes are represented with unique IDs that are integer values starting from 0 to match the indexes in the Adjacency Matrix. 
You are also given a test case for each algorithm in main.cpp. 
You can implement additional test cases for testing purposes, but you don’t have to submit a modified main.cpp. 
Your submission should run successfully using the main method provided. 

Regarding the output of your code, you don’t need to store the distance attribute for BFS, or the discovery and finishing times for DFS. 
For both algorithms the only required output is the following: whenever you visit a node of the graph, print the node ID using a cout instruction to show the sequence that the nodes are visited.


In order to modify your implementation compared to the pseudocode provided in the lecture notes, you are asked to use a C++ set to keep track of the visited nodes instead of coloring the nodes. 
This is a good opportunity to familiarize yourselves with C++ sets if you haven’t used it before.

*/

#include "graph.h"
#include <iostream>
#include <queue>

//Constructor : Creates a graph of size param1
Graph::Graph(int n){

    //Initialize nodes and matrix with param1
    Graph::nodes = n;
    Graph::matrix = new int *[n];


    //Dynamically allocate memory for the graph
    for(int s = 0; s < n; s++){
        Graph::matrix[s] = new int[n];
    }


    //Initialize the graph with 0's
    for(int s = 0; s < n; s++){
        for(int t = 0; t < n; t++){
            Graph::matrix[s][t] = 0;
        }
    }

}


//Constructor : Creates a graph from an adjacency matrix of size param2
Graph::Graph(int** m, int n){

    //Initialize nodes and matrix with param2
    Graph::nodes = n;
    Graph::matrix = new int *[n];


    //Dynamically allocate memory for the graph
    for(int s = 0; s < n; s++){
        Graph::matrix[s] = new int[n];
    }


    //Initialize the graph with values from adjacency matrix
    for(int s = 0; s < n; s++){
        for(int t = 0; t < n; t++){
            Graph::matrix[s][t] = m[s][t];
        }
    }

}

//Destructor Method
Graph::~Graph(){

    for (int s = 0; s < Graph::nodes; s++){
        delete[](Graph::matrix)[s];
    }
    
    delete Graph::matrix;
}

//Set Edge : Sets the value of the edge (u, v) to w, w is the weight of the edge
bool Graph::set_edge(int u, int v, int w){

    //If either edge is negative, or greater than nodes, then return false, else assign weight as value in the matrix
    if(u < 0 || v < 0){
        return false;
    }else if(Graph::nodes - 1 < u || Graph::nodes - 1 < v){
        return false;
    }else{
        Graph::matrix[u][v] = w;
        return true;
    }
}


//DFS : Helper function for dfs, takes a start vertex and a set of discovered vertices as args
void Graph::dfs(int u, set<int>* verticesReached){

    //Insert start vertex to verticesReached set
    verticesReached->insert(u);

    //Print the start vertex on stream
    cout << u << " ";

    //Traverse from start vertex
    //Find vertices which have not been discovered and have non-zero weight
    for(int s = 0; s < Graph::nodes; s++){
        if(verticesReached->count(s) == 0 && matrix[u][s] > 0){
            dfs(s, verticesReached);
        }
    }

}


//DFS : Runs dfs
void Graph::dfs(){

    //Create a set which holds the discovered vertices
    set<int> *verticesReached = new set<int>;
    //Starting from 0 vertex
    int u = 0; 
    //Insert vertices starting from u 
    dfs(u, verticesReached);

    //Expand other adjacent vertices 
    for(int s = 0; s < Graph::nodes; s++){
        if(verticesReached->count(s) == 0){
            dfs(s, verticesReached);
        }
    }

}


//BFS : Helper funciton for bfs, takes a start node and a set of visited nodes as args
void Graph::bfs(int u, set<int>* verticesReached){
    //Insert start vertex to set of discovered vertices
    verticesReached->insert(u);
    //BFS operates on a FIFO, so create a queue for this implementation
    queue<int> *Q = new queue<int>;

    //Push start vertex to the queue
    Q->push(u);

    //Till the queue is not empty, print and pop the vertices
    while(!Q->empty()){

        //Get the first vertex in the queue
        int i = Q->front();
        //Print the first vertex of queue
        cout << i << " ";
        //Remove this first vertex
        Q->pop();

        //Expand all undiscovered vertices from u and have non-zero weight, insert in queue and continue expanding those vertices
        for(int s = 0; s < Graph::nodes; s++){
            if(verticesReached->count(s) == 0 && Graph::matrix[i][s] > 0){
                //Insert node to discovered vertices
                verticesReached->insert(s);
                //Push vertex on the queue
                Q->push(s);
            }
        }

    }

}


//BFS : Runs a bfs from the starting vertex
void Graph::bfs(int u){
    //Create set for discovered vertices
    set<int> *verticesReached = new set<int>;
    //Call BFS helper from starting u vertex
    bfs(u, verticesReached);

}