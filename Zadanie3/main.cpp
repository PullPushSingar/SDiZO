#include <iostream>
#include <vector>
#include <algorithm>
#define N 6
using namespace std;


struct Edge {
    int source, dest, weight;
};

struct DisjointSet {
    vector<int> parent;
    vector<int> weight;

    DisjointSet(int n) {
        parent.resize(n);
        weight.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            weight[i] = 0;
        }
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void merge(int source, int dest) {
        int pu = find(source);
        int pv = find(dest);
        if (pu == pv) {
            return;
        }
        if (weight[pu] > weight[pv]) {
            parent[pv] = pu;
        } else if (weight[pu] < weight[pv]) {
            parent[pu] = pv;
        } else {
            parent[pu] = pv;
            weight[pv]++;
        }
    }
};

vector<Edge> kruskal(vector<Edge>& edges, int n) {
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    DisjointSet ds(n);

    vector<Edge> mst;

    for (Edge& e : edges) {
        if (ds.find(e.source) != ds.find(e.dest)) {
            mst.push_back(e);
            ds.merge(e.source, e.dest);
        } else{
            cout << "Odrzucono sciezke " << e.source + 1 << " - " << e.dest + 1 << " : " << e.weight << endl;
        }
    }

    return mst;
}

vector<Edge> simmetricalToEdge(int arr[N][N], int n){
    vector<Edge> edges;
    for(int i = 0; i < n; i++){
        for(int j = 0;j < n; j++){
            if(arr[i][j]!=0 && j != i){
                edges.push_back({i,j,arr[i][j]});
            }

        }
    }
    return edges;
}

int main() {
    int n = N;
    int arr[N][N] = {
//            {0,2,0,6,0},
//            {2,0,3,8,5},
//            {0,3,0,0,7},
//            {6,8,0,0,9},
//            {0,5,7,9,0}, //1
//            {0,7,0,2,0},
//            {7,0,3,0,4},
//            {0,3,0,0,5},
//            {2,0,0,0,6},
//            {0,4,5,6,0}, //2
//            {0,5,4,0,0},
//            {5,0,3,2,0},
//            {4,3,0,6,0},
//            {0,2,6,0,5},
//            {0,0,0,5,0}, // 3
//            {0,4,3,0,0},
//            {4,0,1,2,0},
//            {3,1,0,5,0},
//            {0,2,5,0,6},
//            {0,0,0,6,0}, // 4
//            {0,3,6,0,0},
//            {3,0,2,4,0},
//            {6,2,0,5,1},
//            {0,4,5,0,3},
//            {0,0,1,3,0}, // 5
            {0,1,0,1,0,2},
            {1,0,3,2,0,2},
            {0,3,0,0,0,3},
            {1,2,0,0,4,4},
            {0,0,0,4,0,4}, //1
            {2,2,3,4,4,0},
    };
    vector<Edge> edges = simmetricalToEdge(arr,n);
    vector<Edge> mst = kruskal(edges, n);
    int sum = 0;
    for (Edge& e : mst) {
        cout << e.source + 1 << " - " << e.dest + 1 << " : " << e.weight << endl;
        sum +=e.weight;
    }
    cout << "MST: " << sum << endl;
    return 0;
}
