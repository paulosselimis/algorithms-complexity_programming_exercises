#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

// Define a pair for profit and weight
typedef pair<int, int> EdgeWeight;
// Define a pair for an edge
typedef pair<EdgeWeight, pair<int, int>> Edge;

// Disjoint Set (Union-Find) for Kruskal's Algorithm
struct DisjointSet {
    vector<int> parent, rank;

    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int u) {
        if (u != parent[u]) parent[u] = find(parent[u]);
        return parent[u];
    }

    void unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) parent[rootV] = rootU;
            else if (rank[rootU] < rank[rootV]) parent[rootU] = rootV;
            else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

// Graph class to manage edges
class Graph {
    int V; // Number of vertices
    vector<Edge> edges; // List of edges

public:
    Graph(int V) : V(V) {}

    void addEdge(int u, int v, int p, int w) {
        edges.push_back({{p, w}, {u, v}});
    }

    // Function to compute MST with adjusted weights for a given r
    pair<int, int> kruskalMST(double r) {
       

        // Sort edges by adjusted weights
        sort(edges.begin(), edges.end(), [&](const Edge &a, const Edge &b) {
            return (a.first.first - r * a.first.second) > (b.first.first - r * b.first.second);
        });

        // Run Kruskal's algorithm to form the MST
        DisjointSet ds(V);
        int totalProfit = 0, totalWeight = 0;

        for (const auto &edge : edges) {
            int u = edge.second.first;
            int v = edge.second.second;
            int profit = edge.first.first;
            int weight = edge.first.second;

            if (ds.find(u) != ds.find(v)) {
                ds.unite(u, v);
                totalProfit += profit; // Accumulate actual profit
                totalWeight += weight; // Accumulate actual weight
            }
        }

        return {totalProfit, totalWeight};
    }

    
    // Function to find the maximum profit-to-weight ratio
    pair<int, int> maximizeRatio() {
        // Calculate the maximum initial value for `high` as max(p(e) / w(e))
        double high = 0.0;
        for (const auto &edge : edges) {
            high = max(high, edge.first.first / static_cast<double>(edge.first.second));
        }

        double low = 0.0, epsilon = 1e-6;
        pair<int, int> bestTree = {0, 0}; // {totalProfit, totalWeight}

        while (high - low > epsilon) {
            double mid = (low + high) / 2.0;
            pair<int, int> mst = kruskalMST(mid);

            // Check if the current ratio is feasible
            if (mst.second > 0) {
                double currentRatio = mst.first / static_cast<double>(mst.second);
                if (currentRatio >= mid) {
                    bestTree = mst;
                    low = mid; // Increase the ratio
                } else {
                    high = mid; // Decrease the ratio
                }
            }
        }

        return bestTree;
    }

};

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int V, E;
    scanf("%d %d", &V, &E);

    Graph graph(V);

    for (int i = 0; i < E; i++) {
        int u, v, p, w;
        scanf("%d %d %d %d", &u, &v, &p, &w);
        graph.addEdge(u - 1, v - 1, p, w);
    }

    pair<int, int> result = graph.maximizeRatio();

    int gcdValue = gcd(result.first, result.second);
    printf("%d %d\n", result.first / gcdValue, result.second / gcdValue);

    return 0;
}