class Solution {
public:
    struct DSU {
        vector<int> parent, sz;
        int comps;

        DSU(int n) : parent(n), sz(n, 1), comps(n) {
            for (int i = 0; i < n; i++) 
              parent[i] = i;
        }

        int find(int x) {
            if (parent[x] == x) return x;
            return parent[x] = find(parent[x]);
        }

        bool unite(int a, int b) {
            a = find(a);
            b = find(b);
            if (a == b) return false;

            if (sz[a] < sz[b]) swap(a, b);
            parent[b] = a;
            sz[a] += sz[b];
            comps--;   
            return true;
        }

        int getComps() const {
            return comps;
        }
    };

    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = (int)isConnected.size();
        DSU dsu(n);

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (isConnected[i][j] == 1) {
                    dsu.unite(i, j);
                }
            }
        }

        return dsu.getComps();
    }
};
