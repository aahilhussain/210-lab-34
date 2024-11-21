#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>
#include <queue>
#include <set>
#include <climits>

using namespace std;

const int SIZE = 10;

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
        cout << "Transportation Network Topology" << endl;
        cout << "===============================" << endl;
        for (int i = 0; i < adjList.size(); i++)
        {
            cout << "City" << i << " connects to:" << endl;
            for (Pair v : adjList[i])
                cout << " -> City " << v.first << " (Distance: " << v.second << " km)" << endl;
            cout << endl;
        }
    }

    //DFS Depth First Search
    void DFS(int start) {
        unordered_set<int> visited;
        stack<int> stack;
        stack.push(start);

        cout << "Network Trace (DFS) from City " << start << ":" << endl;
        cout << "Purpose: Tracing possible routes through the network" << endl;
        cout << "======================================" << endl;
        while (!stack.empty()) {
            int v = stack.top();
            stack.pop();

            if (visited.find(v) == visited.end()) {
                cout << "Inspecting City " << v << endl;
                visited.insert(v);
            }

            for (auto &neighbor : adjList[v]) {
                if (visited.find(neighbor.first) == visited.end()) {
                    cout << " -> Possible route to City " << neighbor.first << " - Distance: " << neighbor.second << " km" << endl;
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

        cout << "Layer-by-Layer Network Inspection (BFS) from City " << start << ":" << endl;
        cout << "Purpose: Analyzing service areas by distance from source" << endl;
        cout << "======================================" << endl;
        while(!queue.empty()) {
            int v = queue.front();
            queue.pop();

            if (visited.find(v) == visited.end()) {
                cout << "Checking City " << v << endl;
                visited.insert(v);
            }

            for (auto &neighbor : adjList[v]) {
                if (visited.find(neighbor.first) == visited.end()) {
                    cout << " -> Next service area: City " << neighbor.first << " - Distance: " << neighbor.second << " km" << endl;
                    queue.push(neighbor.first);
                }
            }
        }

    cout << endl;
    }

    void dijkstra(int start) {
        set<Pair> setds;
        vector<int> dist(SIZE, INT_MAX);

        setds.insert(make_pair(0, start));
        dist[start] = 0;

        while (!setds.empty()) {
            Pair tmp = *(setds.begin());
            setds.erase(setds.begin());

            int u = tmp.second;

            for (auto &neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[v] > dist[u] + weight) {
                    if (dist[v] != INT_MAX) {
                        setds.erase(setds.find(make_pair(dist[v], v)));
                    }

                    dist[v] = dist[u] + weight;
                    setds.insert(make_pair(dist[v], v));
                }
            }
        }

        cout << "Shortest path from node " << start << ";" << endl;
        for (int i = 0; i < SIZE; i++) {
            cout << start << " -> " << i << " : " << dist[i] << endl;
        }
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
        {5, 8, 2},
        {2, 0, 9}};
    // Creates graph
    Graph graph(edges);
    // Prints adjacency list representation of graph
    graph.printGraph();

    //Perform DFS and BFS
    graph.DFS(0);
    graph.BFS(0);

    graph.dijkstra(0);
    return 0;
}