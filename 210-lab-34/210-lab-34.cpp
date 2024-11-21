#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>
#include <queue>

using namespace std;

const int SIZE = 9;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair; // Creates alias 'Pair' for the pair<int,int> data type

class Graph {
public:
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;

    // Graph Constructor
    Graph(vector<Edge> const &edges)
    {
        adjList.resize(SIZE); // resize the vector to hold SIZE elements of type vector<Edge>
        for (auto &edge : edges)
        {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;
            adjList[src].push_back(make_pair(dest, weight));  // insert at the end
            adjList[dest].push_back(make_pair(src, weight)); // for an undirected graph, add an edge from dest to src also
        }
    }
    // Print the graph's adjacency list
    void printGraph()
    {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++)
        {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }

    //DFS Depth First Search
    void DFS(int start) {
        unordered_set<int> visited;
        stack<int> stack;
        stack.push(start);

        cout << "DFS starting from vertex " << start << ": ";
        while (!stack.empty()) {
            int v = stack.top();
            stack.pop();

            if (visited.find(v) == visited.end()) {
                cout << v << " ";
                visited.insert(v);
            }

            for (auto &neighbor : adjList[v]) {
                if (visited.find(neighbor.first) == visited.end()) {
                    stack.push(neighbor.first);
                }
            }
        }

        cout << endl;
    }

    void BFS(int start) {
    unordered_set<int> visited;
    queue<int> queue;
    queue.push(start);

        cout << "BFS starting from vertex " << start << ": ";
        while(!queue.empty()) {
            int v = queue.front();
            queue.pop();

            if (visited.find(v) == visited.end()) {
                cout << v << " ";
                visited.insert(v);
            }

            for (auto &neighbor : adjList[v]) {
                if (visited.find(neighbor.first) == visited.end()) {
                    queue.push(neighbor.first);
                }
            }
        }

    cout << endl;
    }
};

int main()
{
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        {0, 1, 12},
        {0, 2, 8},
        {0, 3, 21},
        {2, 3, 6},
        {2, 6, 2},
        {5, 6, 6},
        {4, 5, 9},
        {7, 8, 10},
        {5, 2, 7},
        {1, 9, 5},
        {7, 6, 3},
        {5, 5, 5},
        {2, 0, 9}};
    // Creates graph
    Graph graph(edges);
    // Prints adjacency list representation of graph
    graph.printGraph();

    //Perform DFS and BFS
    graph.DFS(0);
    graph.BFS(0);
    return 0;
}