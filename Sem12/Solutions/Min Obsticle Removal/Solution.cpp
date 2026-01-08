class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> distances(m, vector<int>(n, INT_MAX));
        deque<pair<int, int>> dq;

        distances[0][0] = 0;
        dq.push_front({0, 0});

        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};

        while (!dq.empty()) {
            auto [x, y] = dq.front();
            dq.pop_front();

            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d];
                int ny = y + dy[d];

                if (nx < 0 || ny < 0 || nx >= m || ny >= n)
                    continue;

                int cost = grid[nx][ny];

                if (distances[x][y] + cost < distances[nx][ny]) {
                    distances[nx][ny] = distances[x][y] + cost;

                    if (cost == 0) {
                        dq.push_front({nx, ny});
                    } else {
                        dq.push_back({nx, ny});
                    }
                }
            }
        }

        return distances[m - 1][n - 1];
    }
};
