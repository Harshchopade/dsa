#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int N = 6;
string places[N] = {"College", "Library", "Cafeteria", "Hostel", "Playground", "Auditorium"};

// Adjacency Matrix
int adjMatrix[N][N] = {0};

// Adjacency List
vector<int> adjList[N];

// DFS using Adjacency List
void dfs(int node, vector<bool>& visited) {
    visited[node] = true;
    cout << places[node] << " ";

    for (int neighbor : adjList[node]) {
        if (!visited[neighbor])
            dfs(neighbor, visited);
    }
}

// BFS using Adjacency Matrix
void bfs(int start) {
    vector<bool> visited(N, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << places[node] << " ";

        for (int i = 0; i < N; i++) {
            if (adjMatrix[node][i] && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

int main() {
    // Add edges
    // College-0, Library-1, Cafeteria-2, Hostel-3, Playground-4, Auditorium-5

    auto addEdge = [](int u, int v) {
        // For Matrix
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;

        // For List
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    };

    addEdge(0, 1); // College - Library
    addEdge(0, 2); // College - Cafeteria
    addEdge(1, 3); // Library - Hostel
    addEdge(2, 4); // Cafeteria - Playground
    addEdge(4, 5); // Playground - Auditorium

    cout << "DFS (Adjacency List): ";
    vector<bool> visited(N, false);
    dfs(0, visited); // Start DFS from College
    cout << endl;

    cout << "BFS (Adjacency Matrix): ";
    bfs(0); // Start BFS from College
    cout << endl;

    return 0;
}
