#include <bits/stdc++.h>
using namespace std;

 struct DSU
{
    vector<int> parent, heaviest;
    vector<bool> is_parent;

    DSU(int n)
    {
        parent.resize(n);
        heaviest.resize(n, 0);
        is_parent.resize(n, true);

        for(int i = 0; i < n; i++)
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

    bool my_union(int u, int v, int w)
    {
        int p_u = my_find(u);
        int p_v = my_find(v);

        if(p_u == p_v)
        {
            return false;
        }
        
        parent[p_u] = p_v;
        heaviest[p_v] = w;
        is_parent[p_u] = false;
        return true;
    }
     
     void print_heaviest() const
     {
         vector<int> res;
         
         for(int i = 0; i < is_parent.size(); i++)
         {
             if(is_parent[i])
             {
                 res.push_back(heaviest[i]);
             }
         }
         
         sort(res.begin(), res.end());
         
         for(auto& w : res)
         {
             cout << w << " ";
         }
     }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
        
    int u, v, w;
    int V, E, K;
    cin >> V >> E >> K;
    vector<pair<int, pair<int, int>>> edges;
    for(int i = 0; i < E; i++)
    {
        cin >> u >> v >> w;
        edges.push_back({w, {u, v}});
    }
    
    sort(edges.begin(), edges.end());
    
    DSU s(V);
    
    int cnt = 0;
    for(int i = 0; i < edges.size(); i++)
    {
        if(cnt == V - K)
            break;
        
        auto& edge = edges[i];
        int vert1 = edge.second.first, vert2 = edge.second.second, curr_weight = edge.first;
        
        if(s.my_union(vert1, vert2, curr_weight))
        {
            cnt++;
        }
    }

    s.print_heaviest();
    
    return 0;
}
