/*
 * @lc app=leetcode.cn id=22 lang=cpp
 *
 * [22] 括号生成
 *
 * https://leetcode-cn.com/problems/generate-parentheses/description/
 *
 * algorithms
 * Medium (68.63%)
 * Total Accepted:    15.1K
 * Total Submissions: 21.9K
 * Testcase Example:  '3'
 *
 * 给出 n 代表生成括号的对数，请你写出一个函数，使其能够生成所有可能的并且有效的括号组合。
 * 
 * 例如，给出 n = 3，生成结果为：
 * 
 * [
 * ⁠ "((()))",
 * ⁠ "(()())",
 * ⁠ "(())()",
 * ⁠ "()(())",
 * ⁠ "()()()"
 * ]
 * 
 * 
 */
struct par{
    string content;
    int left;
    int right;
    par(string s="", int a=0, int b=0)
    {
        content = s;
        left = a;
        right = b;
    }
};

bool operator < (const par& a, const par& b)
{
    if(a.left!=b.left)  return a.left<b.left;
    else    return a.right<b.right;
}


class Solution {
public:
    vector<string> generateParenthesis(int n) {
        
        par adam = par("",n,n);
        vector<string> res;
        
        queue<par> togo;
        togo.push(adam);
        
        while(!togo.empty())
        {
            int sz = togo.size();
            for(int i=0;i<sz;++i)
            {
                par tp = togo.front();
                togo.pop();
                if(tp.left==0)
                {
                    for(int j=1;j<=tp.right;++j)
                        tp.content += ')';
                    res.push_back(tp.content);
                }
                else
                {
                    togo.push(par(tp.content+'(',tp.left-1,tp.right));
                    if(tp.left<tp.right)
                    {
                        togo.push(par(tp.content+')',tp.left,tp.right-1));
                    }
                }
            }
        }
        return res;
    }
    
};

