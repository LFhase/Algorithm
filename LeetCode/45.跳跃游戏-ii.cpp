/*
 * @lc app=leetcode.cn id=45 lang=cpp
 *
 * [45] 跳跃游戏 II
 */
class Solution {
public:
    int jump(vector<int>& nums) {
        int step = 0;
        int cur_reach = 0;
        int nxt_reach = 0;
        int len = nums.size();
        if(len==1)  return 0;
        for(int i=0;i<len;++i)
        {
            nxt_reach = max(i+nums[i],nxt_reach);
            if(nxt_reach>=len-1)    return ++step;
            if(i==cur_reach)
            {
                step++;
                cur_reach = nxt_reach;
            }
        }
        return step;
    }
};

