/*
 * @lc app=leetcode.cn id=78 lang=cpp
 *
 * [78] 子集
 */
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int len = nums.size();
        long long upper = 1LL<<len;
        vector<vector<int>> res;
        for(long long i=0;i<upper;++i)
        {
            vector<int> tmp;
            for(int j=0;j<len;++j)
            {
                if(i>>j&1LL)
                {
                    tmp.push_back(nums[j]);
                }
            }
            res.push_back(tmp);
        }
        return res;
    }
};

