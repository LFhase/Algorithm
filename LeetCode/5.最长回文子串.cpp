/*
 * @lc app=leetcode.cn id=5 lang=cpp
 *
 * [5] 最长回文子串
 *
 * https://leetcode-cn.com/problems/longest-palindromic-substring/description/
 *
 * algorithms
 * Medium (24.60%)
 * Total Accepted:    39.3K
 * Total Submissions: 159.9K
 * Testcase Example:  '"babad"'
 *
 * 给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。
 * 
 * 示例 1：
 * 
 * 输入: "babad"
 * 输出: "bab"
 * 注意: "aba" 也是一个有效答案。
 * 
 * 
 * 示例 2：
 * 
 * 输入: "cbbd"
 * 输出: "bb"
 * 
 * 
 */
class Solution {
public:
    string longestPalindrome(string s) {
        int len = s.length();
        if(len==0)  return "";
        vector<vector<int>> dp(len,vector<int>(len));
        int max_len = 1;
        string res;
        
        for(int i=0;i<len;++i)  dp[i][i] = 1;
        for(int i=0;i+1<len;++i)
        {
            if(s[i]==s[i+1])
            {
                dp[i][i+1] = 1;
                max_len = 2;
            }
        }
        for(int sl = 3;sl<=len;++sl)
        {
            for(int l = 0;l+sl-1<len;++l)
            {
                int r = l+sl-1;
                if(dp[l+1][r-1]&&s[l]==s[r])    
                {
                    dp[l][r] = 1;
                    max_len = sl;
                }
            }
        }
        for(int i=0;i+max_len-1<len;++i)
        {
            if(dp[i][i+max_len-1])
            {
                res = s.substr(i,max_len);
            }
        }
        return res;
    }
};

