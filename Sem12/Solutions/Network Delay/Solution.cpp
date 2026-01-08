class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<pair<int, int>> adj[n+1];
        for(auto vec: times){
            adj[vec[0]].push_back({vec[1], vec[2]});
        }

        vector<int> time(n+1, INT_MAX);
        time[k] = 0;
        priority_queue< pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, k});
        while(!pq.empty()){
            int currTime = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            // Or vector<bool> visited
            if(currTime > time[node]) continue;

            for(auto it: adj[node]){
                int next = it.first;
                int timetaken = it.second;
                if(currTime + timetaken < time[next]){
                    pq.push({currTime + timetaken, next});
                    time[next] = currTime + timetaken;
                }
            }
        }
        
        int answer = INT_MIN;
        for(int i = 1; i <= n; i++){
            answer = max(answer, time[i]);
        }
        return (answer != INT_MAX) ? answer : -1;
    }
};
