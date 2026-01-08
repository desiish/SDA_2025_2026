#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

struct Edge {
    int to;
    int len;
    bool type;

    Edge(int t, int l, bool ty) : to(t), len(l), type(ty) {}

    friend bool operator<(const Edge& a, const Edge& b){
        if (a.len == b.len) {
            return a.type == 1;
        }
        return a.len > b.len;
    }

};

const long long INF = 110000000000;
bool visited[100001];
int railroads = 0;

void dijkstra(vector<vector<Edge>>& graph, int start){
    vector<long long> dist;
    int n = graph.size();
    dist.assign(n, INF);

    dist[start] = 0;
    priority_queue<Edge, vector<Edge>> q;

    Edge first(start, 0, 0);
    q.push(first);

    while(!q.empty()){
        int v = q.top().to;
        bool railType = q.top().type;

        q.pop();

        if(!visited[v]){
            visited[v] = true;
            if(railType)railroads++;

            for(auto edge : graph[v]){
                int to = edge.to;
                int len = edge.len;
                bool type = edge.type;

                if(dist[v] + len <= dist[to]){
                    dist[to] = dist[v] + len;
                    Edge e(to, dist[to], type);
                    q.push(e);
                }
            }
        }
    }

}

int main(){
    int n, m, k;
    cin>>n>>m>>k;
    vector<vector<Edge>> graph(n);
    for(int i=0; i<m; i++){
        int u, v, w;
        cin>>u>>v>>w;
        Edge e(v-1, w, 0);
        Edge e1(u-1, w, 0);
        graph[u-1].push_back(e);
        graph[v-1].push_back(e1);
    }

    for(int i=0; i<k; i++){
        int u, w;
        cin>>u>>w;
        Edge e(0, w, 1);
        Edge e1(u-1, w, 1);
        graph[u-1].push_back(e);
        graph[0].push_back(e1);
    }

    dijkstra(graph, 0);

    cout<<k-railroads<<endl;
}