/*
 * @lc app=leetcode.cn id=479 lang=cpp
 *
 * [479] 最大回文数乘积
 *
 * https://leetcode-cn.com/problems/largest-palindrome-product/description/
 *
 * algorithms
 * Hard (27.40%)
 * Total Accepted:    873
 * Total Submissions: 3.2K
 * Testcase Example:  '1'
 *
 * 你需要找到由两个 n 位数的乘积组成的最大回文数。
 * 
 * 由于结果会很大，你只需返回最大回文数 mod 1337得到的结果。
 * 
 * 示例:
 * 
 * 输入: 2
 * 
 * 输出: 987
 * 
 * 解释: 99 x 91 = 9009, 9009 % 1337 = 987
 * 
 * 说明:
 * 
 * n 的取值范围为 [1,8]。
 * 
 */
#define ll long long 

class Solution {
public:
    ll mypow(ll x, ll n){
        
        ll res = 1;
        while(n--)  res*=x;
        return res;
    }
    

    
    int largestPalindrome(int n) {
        ll upper = mypow(10,n)-1LL;
        ll lower = upper/10;
        for(ll x=upper;x>lower;--x){
            string tmp = to_string(x);
            ll num = atoi(tmp.c_str());
            reverse(tmp.begin(),tmp.end());
            num = num*mypow(10,n);
            num = num+(ll)atoi(tmp.c_str());
            for(ll aa=upper;aa*aa>=num;--aa){
                if(num%aa==0)
                {
                    return num%1337LL;
                }
            }
        }
        return upper;
    }
};

