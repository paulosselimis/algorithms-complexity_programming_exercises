#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int weight;
    Edge(int t, int w) : to(t), weight(w) {}
};

struct State {
    int k;
    int time;
    int node;
    State(int k_, int t_, int n_) : k(k_), time(t_), node(n_) {}
};

struct CompareState {
    bool operator()(const State& a, const State& b) {
        if (a.k != b.k) {
            return a.k > b.k; // prioritize lower k
        } else {
            return a.time > b.time; // then lower time
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, s, t, B;
    cin >> N >> M >> s >> t >> B;

    vector<vector<Edge>> adj(N+1); // nodes are 1-based
    for (int i = 0; i < M; ++i) {
        int u, v, l;
        cin >> u >> v >> l;
        adj[u].emplace_back(v, l);
    }

    int k_max = M;
    const int INF = B + 1;
    vector<vector<int>> dist(N+1, vector<int>(k_max + 1, INF));
    dist[s][0] = 0;

    priority_queue<State, vector<State>, CompareState> pq;
    pq.emplace(0, 0, s);

    int answer = -1;

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        int current_k = current.k;
        int current_time = current.time;
        int current_node = current.node;

        if (current_node == t && current_time <= B) {
            answer = current_k;
            break;
        }

        if (current_time > dist[current_node][current_k]) {
            continue; // a better state already exists
        }

        for (const Edge& e : adj[current_node]) {
            int v = e.to;
            int l = e.weight;

            // Option 1: take the edge normally
            int new_time = current_time + l;
            int new_k = current_k;
            if (new_time < dist[v][new_k]) {
                dist[v][new_k] = new_time;
                pq.emplace(new_k, new_time, v);
            }

            // Option 2: take the edge as instant
            new_time = current_time;
            new_k = current_k + 1;
            if (new_k <= k_max) {
                if (new_time < dist[v][new_k]) {
                    dist[v][new_k] = new_time;
                    pq.emplace(new_k, new_time, v);
                }
            }
        }
    }

    cout << (answer != -1 ? answer : -1) << endl;

    return 0;
}