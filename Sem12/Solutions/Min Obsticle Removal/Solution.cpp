int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};
class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n,INT_MAX));
        vector<vector<bool>> vis(m, vector<bool>(n,0));
        deque<pair<int,int>> q;
        q.push_front({0,0});
        dp[0][0] = 0;
        while(!q.empty()) {
            pair<int,int> p = q.front();
            q.pop_front();
            int cx = p.first;
            int cy = p.second;
            if (cx == m-1 && cy == n-1){
                return dp[m-1][n-1];
            }
            for(int i=0;i<4;i++) {
                int tx = cx + dx[i];
                int ty = cy + dy[i];
                if(tx >=0 && tx < m && ty >=0 && ty < n) {
                    if(!vis[tx][ty]) {
                        dp[tx][ty] = dp[cx][cy] + (grid[tx][ty] == 1);
                        if(grid[tx][ty] == 1) {
                            q.push_back({tx,ty});
                        } else {
                            q.push_front({tx,ty});
                        }
                        vis[tx][ty] = true;
                    }
                }
            }
        }

        return dp[m-1][n-1];
    }
};
