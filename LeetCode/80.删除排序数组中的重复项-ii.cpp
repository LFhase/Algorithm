/*
 * @lc app=leetcode.cn id=80 lang=cpp
 *
 * [80] 删除排序数组中的重复项 II
 */
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int len = nums.size();
        int p1 = 0;
        int cnt = 0;
        int i = 0;
        while(i<len)
        {
            cnt = 1;
            while(i+cnt<len&&nums[i]==nums[i+cnt])
            {
                cnt++;
            }
            for(int tt=0;tt<min(cnt,2);++tt)    
            {
                nums[p1]=nums[i];
                p1++;
            }
            i += cnt;
        }
        int res = p1;
        for(int i=0;i<len-p1;++i)   nums.pop_back();
        return res;
    }
};

