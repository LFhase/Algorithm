/*
 * @lc app=leetcode.cn id=20 lang=cpp
 *
 * [20] 有效的括号
 *
 * https://leetcode-cn.com/problems/valid-parentheses/description/
 *
 * algorithms
 * Easy (36.54%)
 * Total Accepted:    48.9K
 * Total Submissions: 133.9K
 * Testcase Example:  '"()"'
 *
 * 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。
 * 
 * 有效字符串需满足：
 * 
 * 
 * 左括号必须用相同类型的右括号闭合。
 * 左括号必须以正确的顺序闭合。
 * 
 * 
 * 注意空字符串可被认为是有效字符串。
 * 
 * 示例 1:
 * 
 * 输入: "()"
 * 输出: true
 * 
 * 
 * 示例 2:
 * 
 * 输入: "()[]{}"
 * 输出: true
 * 
 * 
 * 示例 3:
 * 
 * 输入: "(]"
 * 输出: false
 * 
 * 
 * 示例 4:
 * 
 * 输入: "([)]"
 * 输出: false
 * 
 * 
 * 示例 5:
 * 
 * 输入: "{[]}"
 * 输出: true
 * 
 */
class Solution {
public:
    bool isValid(string s) {
        stack<char> to_match;
        int len = s.length();
        for(int i=0;i<len;++i)
        {
            if(s[i]=='('||s[i]=='['||s[i]=='{')
            {
                to_match.push(s[i]);
            }
            else if(s[i]==')'||s[i]==']'||s[i]=='}')
            {
                if(to_match.empty())    return 0;
                char tp = to_match.top();
                to_match.pop();
                if((s[i]==')'&&tp=='(')||
                   (s[i]==']'&&tp=='[')||
                   (s[i]=='}'&&tp=='{'))
                    continue;
                else    return 0;
            }
            else    return 0;
        }
        return to_match.empty();
    }
};
