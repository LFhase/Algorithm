/*
 * @lc app=leetcode.cn id=40 lang=cpp
 *
 * [40] 组合总和 II
 *
 * https://leetcode-cn.com/problems/combination-sum-ii/description/
 *
 * algorithms
 * Medium (54.02%)
 * Total Accepted:    9.6K
 * Total Submissions: 17.7K
 * Testcase Example:  '[10,1,2,7,6,1,5]\n8'
 *
 * 给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
 * 
 * candidates 中的每个数字在每个组合中只能使用一次。
 * 
 * 说明：
 * 
 * 
 * 所有数字（包括目标数）都是正整数。
 * 解集不能包含重复的组合。 
 * 
 * 
 * 示例 1:
 * 
 * 输入: candidates = [10,1,2,7,6,1,5], target = 8,
 * 所求解集为:
 * [
 * ⁠ [1, 7],
 * ⁠ [1, 2, 5],
 * ⁠ [2, 6],
 * ⁠ [1, 1, 6]
 * ]
 * 
 * 
 * 示例 2:
 * 
 * 输入: candidates = [2,5,2,1,2], target = 5,
 * 所求解集为:
 * [
 * [1,2,2],
 * [5]
 * ]
 * 
 */
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(),candidates.end());
        unordered_map<int, vector<vector<int>>> res;
        int len = candidates.size();
        for(int i=0;i<len;++i)
        {
            for(int j=target-1;j>=0;--j)
            {
                if(res[j].size()==0)    continue;
                int nxt = j + candidates[i];
                if(nxt>target)  continue;
            
                for(vector<int> v: res[j])
                {
                    v.push_back(candidates[i]);
                    res[nxt].push_back(v);
                }
            }
            res[candidates[i]].push_back(vector<int>(1,candidates[i]));
        }
        set<vector<int>> u_set;
        for(vector<int> u: res[target]) u_set.insert(u);
        vector<vector<int>> ans;
        for(vector<int> u: u_set)   ans.push_back(u);
            
        return ans;
    }
};

