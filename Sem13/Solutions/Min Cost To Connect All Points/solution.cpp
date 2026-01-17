class Solution {
public:
    struct DSU
    {
        vector<int> parent, size;

        DSU(int n)
        {
            parent.resize(n + 1);
            size.resize(n + 1, 1);

            for(int i = 0; i < n + 1; i++)
            {
                parent[i] = i;
            }
        }

        int my_find(int node)
        {
            if(node == parent[node]) 
            {
                return node;
            }

            return parent[node] = my_find(parent[node]);
        }

        bool my_union(int u, int v)
        {
            int p_u = my_find(u);
            int p_v = my_find(v);

            if(p_u == p_v)
            {
                return false;
            }

            if(size[p_u] > size[p_v])
            {
                parent[p_v] = p_u;
                size[p_u] += size[p_v];
            }
            else
            {
                parent[p_u] = p_v;
                size[p_v] += size[p_u];
            }

            return true;
        }
    };
    int minCostConnectPoints(vector<vector<int>>& points) {
        vector<array<int, 3>> adj;

        for(int i = 0; i < points.size(); i++)
        {
            for(int j = i + 1; j < points.size(); j++)
            {
                int dist = abs(points[i][0] - points[j][0]) +
                abs(points[i][1] - points[j][1]);

                adj.push_back({i, j, dist});
            }
        }

        sort(adj.begin(), adj.end(), [](const array<int, 3>& a, const array<int, 3>& b)
        {
            return a[2] < b[2];
        });

        DSU s(points.size());
        int res = 0;

        for(int i = 0; i < adj.size(); i++)
        {
            int from = adj[i][0], to = adj[i][1], dist = adj[i][2];

            if(s.my_union(from, to))
            {
                res += dist;
            }
        }

        return res;

    }
};
