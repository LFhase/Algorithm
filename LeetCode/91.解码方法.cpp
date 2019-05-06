/*
 * @lc app=leetcode.cn id=91 lang=cpp
 *
 * [91] 解码方法
 */
class Solution {
public:
    int numDecodings(string s) {
        vector<int> dp(s.length()+1,0);
        int len = s.length();
        dp[0] = 1;
        for(int i=0;i<len;++i)
        {
            if(s[i]>'0')    dp[i+1] = dp[i];
            if(i>=1&&(s[i-1]-'0')>=1&&((s[i-1]-'0')*10+(s[i]-'0'))<=26&&((s[i-1]-'0')*10+(s[i]-'0'))>=1)
            {
                dp[i+1] += dp[i-1];
            }
        }
        return dp[len];
    }
};
