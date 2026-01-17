int prims(int n, vector<vector<int>> edges, int start) {
    vector<vector<pair<int,int>>> adj(n + 1);
    adj.reserve(n + 1);

    for (const auto &e : edges) {
        int u = e[0], v = e[1], w = e[2];
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<char> inMST(n + 1, 0);

    // <weight, node>
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, start});

    long long total = 0;
    int taken = 0;

    while (!pq.empty() && taken < n) {
        // works only on versions of C++ > 14
        auto [w, u] = pq.top();
        pq.pop();

        if (inMST[u]) continue;

        inMST[u] = 1;
        total += w;
        taken++;

        for (auto [v, wt] : adj[u]) {
            if (!inMST[v]) pq.push({wt, v});
        }
    }

    return total; 
}
