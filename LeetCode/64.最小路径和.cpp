/*
 * @lc app=leetcode.cn id=64 lang=cpp
 *
 * [64] 最小路径和
 */
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        if(m==0)    return 0;
        int n = grid[0].size();
        if(n==0)    return 0;
        vector<int> dp = vector<int>(n,0);
        dp[0] = grid[0][0];
        for(int i=1;i<n;++i)
        {
            dp[i] = grid[0][i]+dp[i-1];
        }
        for(int i=1;i<m;++i)
        {
            dp[0] = dp[0] + grid[i][0];
            for(int j=1;j<n;++j)
            {
                dp[j] = min(dp[j-1],dp[j])+grid[i][j];
            }
        }
        return dp[n-1];
    }
};

