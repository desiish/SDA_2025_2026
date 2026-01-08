class Solution {
public:
    int minimumTime(vector<vector<int>>& grid) {
        if (grid[0][1] > 1 && grid[1][0] > 1) return -1;
        
        int rows = grid.size();
        int cols = grid[0].size();
        int maxPos = rows * cols;
        
        priority_queue<pair<int, int>, 
                      vector<pair<int, int>>, 
                      greater<pair<int, int>>> minHeap;
        
        minHeap.push({0, 0}); // time, encoded position
        
        vector<bool> seen(maxPos, false); 
        seen[0] = true;
        
        const int moves[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
        while (!minHeap.empty()) {
            auto [currTime, pos] = minHeap.top();
            int currRow = pos / cols;
            int currCol = pos % cols;
            
            minHeap.pop();
            
            if (currRow == rows - 1 && currCol == cols - 1) 
                return currTime;
            
            for (const auto& move : moves) {
                int nextRow = move[0] + currRow;
                int nextCol = move[1] + currCol;
                int nextPos = nextRow * cols + nextCol;
                
                if (nextRow >= 0 && nextCol >= 0 && 
                    nextRow < rows && nextCol < cols && 
                    !seen[nextPos]) {
                    
                    int waitTime = ((grid[nextRow][nextCol] - currTime) % 2 == 0) ? 1 : 0;
                    int nextTime = max(currTime + 1, grid[nextRow][nextCol] + waitTime);
                    
                    minHeap.push({nextTime, nextPos});
                    seen[nextPos] = true;
                }
            }
        }
        return -1;
    }
};