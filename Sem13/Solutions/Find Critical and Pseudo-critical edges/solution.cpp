class Solution {
public:
    struct DSU {
        vector<int> parent, size;
        int components;

        DSU(int n) : parent(n), size(n, 1), components(n) {
            for (int i = 0; i < n; i++) parent[i] = i;
        }

        int find(int x) {
            if (parent[x] == x) return x;
            return parent[x] = find(parent[x]);
        }

        bool unite(int a, int b) {
            a = find(a);
            b = find(b);
            if (a == b) return false;

            if (size[a] < size[b]) swap(a, b);
            parent[b] = a;
            size[a] += size[b];
            components--;
            return true;
        }
    };

    long long computeMST(
        int n,
        const vector<array<int,4>>& edgesSorted,
        int skipEdge,
        int forceEdge
    ) {
        const long long INF = 1e18;
        DSU dsu(n);
        long long weight = 0;

        if (forceEdge != -1) {
            int u = edgesSorted[forceEdge][0];
            int v = edgesSorted[forceEdge][1];
            int w = edgesSorted[forceEdge][2];
            if (dsu.unite(u, v)) weight += w;
        }

        for (int i = 0; i < (int)edgesSorted.size(); i++) {
            if (i == skipEdge || i == forceEdge) continue;

            int u = edgesSorted[i][0];
            int v = edgesSorted[i][1];
            int w = edgesSorted[i][2];

            if (dsu.unite(u, v)) weight += w;
            if (dsu.components == 1) break;
        }

        return (dsu.components == 1) ? weight : INF;
    }

    vector<vector<int>> findCriticalAndPseudoCriticalEdges(
        int n,
        vector<vector<int>>& edges
    ) {
        int m = edges.size();

        // {u, v, w, originalIndex}
        vector<array<int,4>> edgesSorted;
        for (int i = 0; i < m; i++) {
            edgesSorted.push_back({
                edges[i][0],
                edges[i][1],
                edges[i][2],
                i
            });
        }

        sort(edgesSorted.begin(), edgesSorted.end(),
             [](const array<int,4>& a, const array<int,4>& b) {
                 if (a[2] != b[2]) return a[2] < b[2];
                 return a[3] < b[3];
             });

        long long baseMST = computeMST(n, edgesSorted, -1, -1);

        vector<int> critical;
        vector<int> pseudoCritical;

        for (int i = 0; i < m; i++) {
            long long without = computeMST(n, edgesSorted, i, -1);
            if (without > baseMST) {
                critical.push_back(edgesSorted[i][3]);
            } else {
                long long with = computeMST(n, edgesSorted, -1, i);
                if (with == baseMST) {
                    pseudoCritical.push_back(edgesSorted[i][3]);
                }
            }
        }

        return {critical, pseudoCritical};
    }
};
