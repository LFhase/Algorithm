/*
 * @lc app=leetcode.cn id=32 lang=cpp
 *
 * [32] 最长有效括号
 *
 * https://leetcode-cn.com/problems/longest-valid-parentheses/description/
 *
 * algorithms
 * Hard (25.56%)
 * Total Accepted:    7.1K
 * Total Submissions: 27.9K
 * Testcase Example:  '"(()"'
 *
 * 给定一个只包含 '(' 和 ')' 的字符串，找出最长的包含有效括号的子串的长度。
 * 
 * 示例 1:
 * 
 * 输入: "(()"
 * 输出: 2
 * 解释: 最长有效括号子串为 "()"
 * 
 * 
 * 示例 2:
 * 
 * 输入: ")()())"
 * 输出: 4
 * 解释: 最长有效括号子串为 "()()"
 * 
 * 
 */
class Solution {
public:
    int longestValidParentheses(string s) {
        int len = s.length();
        vector<int> dp(len+1,0);
        stack<pair<char,int>> togo;
        int res = 0;
        for(int i=1;i<=len;++i)
        {
            char c = s[i-1];
            if(!togo.empty()&&(c==')'&&togo.top().first=='('))
            {
                pair<char,int> tp = togo.top(); 
                togo.pop();
                dp[i] = dp[tp.second-1]+i-tp.second+1;
                res = max(res,dp[i]);
            }
            else
            {
                togo.push(make_pair(c,i));
            }
        }
        
        
        return res;
    }
};
