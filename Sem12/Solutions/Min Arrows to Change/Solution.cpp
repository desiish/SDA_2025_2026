class Solution {
public:
  int minCost(vector<vector<int>>& grid) {
    const int m = grid.size();
    const int n = grid[0].size();
    deque<pair<int, int>> q{{0, 0}};
    vector<bool> visited(m * n);
    vector<vector<int>> dirs{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    while (!q.empty()) {
      auto [p, cost] = q.front(); q.pop_front();
      int x = p % n, y = p / n;

      if (x == n - 1 && y == m - 1) return cost;
      if (visited[p]) continue;

      visited[p]=true;
      for (int i = 0; i < 4; ++i) {
        int tx = x + dirs[i][0], ty = y + dirs[i][1];
        int tp = ty * n + tx;
        if (tx < 0 || ty < 0 || tx >= n || ty >= m || visited[tp]) continue;
        if (grid[y][x] == i + 1)
          q.emplace_front(tp, cost);
        else
          q.emplace_back(tp, cost + 1);
      }
    }
    return -1;
  }
};
