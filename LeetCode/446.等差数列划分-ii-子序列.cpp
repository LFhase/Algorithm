/*
 * @lc app=leetcode.cn id=446 lang=cpp
 *
 * [446] 等差数列划分 II - 子序列
 */

class Solution {
public:
    unordered_map<long long, int>* cnt;
    int numberOfArithmeticSlices(vector<int>& A) {
        int len = A.size();
        cnt = new unordered_map<long long, int>[len]();
        int res = 0;
        long long tmp;
        int tmp2;
        for(int i=1;i<len;++i)
        {
            for(int j=0;j<i;++j)
            {
                tmp = 1LL*A[i]-A[j];
                if(cnt[j].count(tmp))      tmp2 = cnt[j][tmp];
                else    tmp2 = 0;
                cnt[i][tmp]+=tmp2+1;
                res += tmp2;
            }
        }
        
        return res;
    }
};

