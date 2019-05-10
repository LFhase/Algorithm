/*
 * @lc app=leetcode.cn id=462 lang=cpp
 *
 * [462] 最少移动次数使数组元素相等 II
 */
class Solution {
public:
    int minMoves2(vector<int>& nums) {
        int len = nums.size();
        
        map<int,int> cnt;
        for(int i=0;i<len;++i)
        {
            cnt[nums[i]]++;
        }
        int res = (*cnt.begin()).first;
        long long min_cost = 0;
        int last = (*cnt.begin()).first;
        int left_cnt = 0;
        long long cost = 0;
        for(pair<int,int> u: cnt)
        {
            cost += (u.first-res)*u.second;
        }
        min_cost = cost;
        for(pair<int,int> u: cnt)
        {
            cost -= 1LL*(len-left_cnt)*(u.first-last);
            cost += 1LL*left_cnt*(u.first-last);
            left_cnt += u.second;
            last = u.first;
            if(cost<min_cost)   
            {
                res = u.first;
                min_cost = cost;
            }
        }
        return min_cost;
    }
};

