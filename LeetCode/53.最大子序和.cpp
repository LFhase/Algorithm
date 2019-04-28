/*
 * @lc app=leetcode.cn id=53 lang=cpp
 *
 * [53] 最大子序和
 */
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int res = nums[0];
        int cur = 0;
        int len = nums.size();
        for(int i=0;i<len;++i)
        {
            if(cur>0)   cur += nums[i];
            else    cur = nums[i];
            res = max(res,cur);
        }

        return res;
    }
};

