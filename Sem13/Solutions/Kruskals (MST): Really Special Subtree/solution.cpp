struct DSU {
    vector<int> parent, sz;
    int comps;

    DSU(int n) : parent(n + 1), sz(n + 1, 1), comps(n) {
        for (int i = 0; i <= n; i++) parent[i] = i;
    }

    int find(int node) {
        if (node == parent[node]) return node;
        return parent[node] = find(parent[node]);
    }

    bool unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;

        if (sz[u] < sz[v]) swap(u, v);
        parent[v] = u;
        sz[u] += sz[v];
        comps--;
        return true;
    }

    int get_comps() const { return comps; }
};

int kruskals(int g_nodes, vector<int> g_from, vector<int> g_to, vector<int> g_weight) {
    struct Edge { int u, v, w; };
    vector<Edge> es;
    es.reserve(g_from.size());

    for (int i = 0; i < (int)g_from.size(); i++) {
        es.push_back({g_from[i], g_to[i], g_weight[i]});
    }

    sort(es.begin(), es.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    DSU dsu(g_nodes);
    long long total = 0;

    for (const auto& e : es) {
        if (dsu.unite(e.u, e.v)) {
            total += e.w;
            if (dsu.get_comps() == 1) break; 
        }
    }

    return total; 
}
