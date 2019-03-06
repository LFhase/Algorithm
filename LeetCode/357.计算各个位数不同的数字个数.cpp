/*
 * @lc app=leetcode.cn id=357 lang=cpp
 *
 * [357] 计算各个位数不同的数字个数
 *
 * https://leetcode-cn.com/problems/count-numbers-with-unique-digits/description/
 *
 * algorithms
 * Medium (42.83%)
 * Total Accepted:    1.5K
 * Total Submissions: 3.5K
 * Testcase Example:  '2'
 *
 * 给定一个非负整数 n，计算各位数字都不同的数字 x 的个数，其中 0 ≤ x < 10^n 。
 * 
 * 示例:
 * 
 * 输入: 2
 * 输出: 91 
 * 解释: 答案应为除去 11,22,33,44,55,66,77,88,99 外，在 [0,100) 区间内的所有数字。
 * 
 * 
 */
class Solution {
public:
    int fac[15];
    Solution()
    {
        fac[0] = 1;
        for(int i=1;i<=10;++i)  fac[i] = fac[i-1]*i;
    }
    int AA(int x, int n)
    {
        if(x>n) return 0;
        else if(x==n)   return 1;
        return fac[n]/fac[n-x];
    }
    int CC(int x, int n)
    {
        if(x>n) return 0;
        else if(x==n)   return 1;
        return AA(x,n)/fac[x];
    }
    
    int countNumbersWithUniqueDigits(int n) {
        if(n<0||n>10)   return 0;
        else if(n==1)   return 10;
        else if(n==0)   return 1;
        int res = AA(n,10);
        for(int i=1;i<n;++i)
        {
            res += (n-i)*AA(n-i-1,9);
        }
        return res;
    }
};

