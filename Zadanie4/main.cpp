#include <iostream>
#include <limits>

using namespace std;

const int numVertices = 6;

void dijkstra(int graph[numVertices][numVertices], int start, int dest) {
    int distances[numVertices];
    int prev[numVertices];
    bool visited[numVertices] = { false };

    for (int i = 0; i < numVertices; i++) {
        distances[i] = numeric_limits<int>::max();
        prev[i] = -1;
    }

    distances[start] = 0;

    for (int count = 0; count < numVertices - 1; count++) {
        int u = -1;
        int minDist = numeric_limits<int>::max();


        for (int i = 0; i < numVertices; i++) {
            if (!visited[i] && distances[i] < minDist) {
                minDist = distances[i];
                u = i;
            }
        }


        visited[u] = true;


        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && graph[u][v] != 0 && distances[u] != numeric_limits<int>::max() &&
                distances[u] + graph[u][v] < distances[v]) {
                distances[v] = distances[u] + graph[u][v];
                prev[v] = u;
            }
        }
    }

    if (distances[dest] == numeric_limits<int>::max()) {
        cout << "No path from node " << start << " to node " << dest << endl;
    } else {
        cout << "Shortest path from node " << start << " to node " << dest << " has length " << distances[dest] << endl;
        cout << "Path: ";
        int u = dest;
        int path[numVertices];
        int pathIndex = 0;

        while (u != -1) {
            path[pathIndex++] = u;
            u = prev[u];
        }

        for (int i = pathIndex - 1; i >= 0; i--) {
            cout << path[i];
            if (i > 0) {
                cout << " -> ";
            }
        }
        cout << endl;
    }
}

int main() {
    int graph[numVertices][numVertices] = {
            { 0, 0, 2, 0, 5, 0 },
            { 7, 0, 0, 2, 0, 0 },
            { 0, 0, 0, 0, 0, 12 },
            { 0, 0, 10, 0, 0, 0 },
            { 0, 3, 6, 8, 0, 0 },
            { 0, 0, 0, -20, 3, 0 }
    };

    int startVertex = 0;
    int destVertex = 3;

    dijkstra(graph, startVertex, destVertex);

    return 0;
}