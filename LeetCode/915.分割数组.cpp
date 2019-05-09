/*
 * @lc app=leetcode.cn id=915 lang=cpp
 *
 * [915] 分割数组
 */
class Solution {
public:
    int partitionDisjoint(vector<int>& A) {
        int len = A.size();
        int left_max = A[0];
        int pivot = 0;
        int tot_max = A[0];
        for(int i=1;i<len;++i)
        {
            tot_max = max(tot_max,A[i]);
            if(left_max>A[i])
            {
                pivot = i;
                left_max = tot_max;
            }
        }
        return pivot+1;
    }
};

