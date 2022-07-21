/*
Union-Find Algorithm for cycle detection in a graph
Algorithm:
a. Create disjoint sets for each vertex of the graph
b. For every edge u, v in the graph
    i. Find the root of the sets to which elements u and v belongs.
    ii. If both u and v have the same root in disjoint sets, a cycle is found.
    
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Data Structure to store a graph edge
struct Edge {
  int src;
  int dest;
};

// A class to represent a graph object
class Graph {
 public:
    // a vector of vectors to represent an adjacency List
    vector<vector<int> > adjList;
  
    // Graph constuctor
    Graph(vector<Edge> const &edges, int n) {
        // resize the vector to hold 'n' elements of type 'vector<int>'
        adjList.resize(n);
      
        // add edges to the undirected graph
        for (auto &edge : edges) {
            adjList[edge.src].push_back(edge.dest);
        }
    }
};

// A class to represent a disjoint set
class DisjointSet {
    unordered_map<int, int> parent;
  public:
    // Perform Makeset operation
    void MakeSet(int n) {
        // create 'n' disjoint sets (one for each vertex)
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
  
    // Find the root of the set in which element 'k' belongs
    int Find(int k) {
        // if 'k' is root
        if (parent[k] == k) {
            return k;
        }
      
        // return for the parent until we find the root
        return Find(parent[k]);
    }
  
    // Perform Union of two subsets
    void Union(int a, int b) {
        // Find the root of the sets in which elements 'x' and 'y' belongs
        int x = Find(a);
        int y = Find(b);
        parent[x] = y;
    }
};

// Returns true if the graph has a cycle
bool findCycle(const Graph &graph, int n) {
    // Initialize DisjointSet object
    DisjointSet ds;
  
    // create a singleton set for each element of the universe
    ds.Makeset(n);
    // consider every edge(u, v)
    for (int u = 0; u < n; u++) {
        // Recur for all adjancent vertices
        for (int v : graph.adjList[u]) {
             // find the root of the sets to which elements 'u' and 'v' belongs
             int x = ds.Find(u);
             int y = ds.Find(v);
             // if both u and v have same parent, cycle is found
             if (x == y) {
                return true;
             }
             else
             {
               ds.Union(x, y);
             }
        }
    }
    return false;
}
int main()
{
  // vector of graph edges
    vector<Edge> edges =
    {
        {0, 1}, {0, 6}, {0, 7}, {1, 2}, {1, 5}, {2, 3},
        {2, 4}, {7, 8}, {7, 11}, {8, 9}, {8, 10}, {10, 11}
        // edge (10, 11) introduces a cycle in the graph
    };
 
    // total number of nodes in the graph (labelled from 0 to 11)
    int n = 12;
 
    // build a graph from the given edges
    Graph graph(edges, n);
 
    if (findCycle(graph, n)) {
        cout << "Cycle Found";
    }
    else {
        cout << "No Cycle Found";
    }
    return 0;
}
