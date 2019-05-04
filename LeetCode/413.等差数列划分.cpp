/*
 * @lc app=leetcode.cn id=413 lang=cpp
 *
 * [413] 等差数列划分
 */
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        int res = 0;
        int last = 0;
        int len = A.size();
        int cur_delta = -1e9+7;
        for(int i=1;i<len;++i)
        {
            if(cur_delta==-1e9+7||A[i]-A[i-1]==cur_delta)
            {
                cur_delta = A[i]-A[i-1];
            }
            else
            {
                if(i-last>=3)
                {
                    res += (1+i-last-3+1)*(i-last-3+1)/2;
                }
                last = i-1;
                cur_delta = A[i]-A[i-1];
            }
        }
        if(len-last>=3)
        {
            res += (1+len-last-3+1)*(len-last-3+1)/2;
        }
        return res;
    }
};

