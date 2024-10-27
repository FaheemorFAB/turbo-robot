/*Kruskal's Algorithm finds the Minimum Spanning Tree (MST) by adding edges in ascending order of weight, ensuring no cycles are formed.*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E;
    vector<Edge> edges;
};

struct subset {
    int parent;
    int rank;
};

Graph* createGraph(int V, int E) {
    Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    return graph;
}

int find(subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

void KruskalMST(Graph* graph) {
    int V = graph->V;
    vector<Edge> result(V);
    int e = 0, i = 0;

    sort(graph->edges.begin(), graph->edges.end(), compareEdges);

    subset* subsets = new subset[V];
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1 && i < graph->E) {
        Edge nextEdge = graph->edges[i++];
        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        if (x != y) {
            result[e++] = nextEdge;
            Union(subsets, x, y);
        }
    }

    cout << "Following are the edges in the constructed MST" << endl;
    for (i = 0; i < e; ++i)
        cout << result[i].src << " -- " << result[i].dest << " == " << result[i].weight << endl;

    delete[] subsets;
}

int main() {
    int V = 4;
    int E = 5;
    Graph* graph = createGraph(V, E);

    graph->edges.push_back({0, 1, 10});
    graph->edges.push_back({0, 2, 6});
    graph->edges.push_back({0, 3, 5});
    graph->edges.push_back({1, 3, 15});
    graph->edges.push_back({2, 3, 4});

    KruskalMST(graph);

    return 0;
}
