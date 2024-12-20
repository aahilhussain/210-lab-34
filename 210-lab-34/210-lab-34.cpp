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

    void MSTedge() {
        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        int src = 0;
        vector<int> key(SIZE, INT_MAX);
        vector<int> parent(SIZE, -1);
        vector<bool> inMST(SIZE, false);

        pq.push(make_pair(0, src)); 
        key[src] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            inMST[u] = true;

            for(auto &neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if(!inMST[v] && key[v] > weight) {
                    key[v] = weight;
                    pq.push(make_pair(key[v], v));
                    parent[v] = u;
                }
            }
        }

        cout << "Minimum Spanning Tree edges:" << endl;
        for(int i = 1; i<SIZE; i++) {
            if (parent[i] != -1) {
                cout << "Edge from " << parent[i] << " to " << i << " with capacity: " << key[i] << " units" << endl;
            }
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
        {2, 0, 9}
    };

    Graph graph(edges); 
    
    int choice;

    do { 
        cout << "Transportation Network Menu: " << endl;
        cout << "[1] Display Transportation network" << endl;
        cout << "[2] Check " << endl;
        cout << "[3] Plan Transportation Route(DFS)" << endl;
        cout << "[4] Calculate shortest paths" << endl;
        cout << "[5] Find Minimum Spanning Tree" << endl;
        cout << "[0] Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
    
        switch (choice) {
            case 1: 
                graph.printGraph();
                break;
            case 2:
                graph.BFS(0);
                break;
            case 3:
                graph.DFS(0);
                break;
            case 4:
                graph.dijkstra(0);
                break;
            case 5:
                graph.MSTedge();
                break;
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again" << endl;
        }
    } while (choice != 0);

    return 0;
}