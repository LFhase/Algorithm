/*
 * @lc app=leetcode.cn id=30 lang=cpp
 *
 * [30] 串联所有单词的子串
 *
 * https://leetcode-cn.com/problems/substring-with-concatenation-of-all-words/description/
 *
 * algorithms
 * Hard (24.77%)
 * Total Accepted:    4.6K
 * Total Submissions: 18.8K
 * Testcase Example:  '"barfoothefoobarman"\n["foo","bar"]'
 *
 * 给定一个字符串 s 和一些长度相同的单词 words。找出 s 中恰好可以由 words 中所有单词串联形成的子串的起始位置。
 * 
 * 注意子串要与 words 中的单词完全匹配，中间不能有其他字符，但不需要考虑 words 中单词串联的顺序。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：
 * ⁠ s = "barfoothefoobarman",
 * ⁠ words = ["foo","bar"]
 * 输出：[0,9]
 * 解释：
 * 从索引 0 和 9 开始的子串分别是 "barfoor" 和 "foobar" 。
 * 输出的顺序不重要, [9,0] 也是有效答案。
 * 
 * 
 * 示例 2：
 * 
 * 输入：
 * ⁠ s = "wordgoodgoodgoodbestword",
 * ⁠ words = ["word","good","best","word"]
 * 输出：[]
 * 
 * 
 */
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        
        vector<int> res;
        int s_len = s.length();
        
        
        if(words.size()==0) 
        {
            //for(int i=0;i<s_len;++i)    res.push_back(i);
            return res;
        }
        
        int len = words[0].length();
        int n = words.size();
        map<string,int> record;
        int idx = 0;
        
        vector<int> cnt(n+1,0);
        for(string word: words) 
        {
            if(record[word]==0)
            {
                record[word] = ++idx;
                cnt[idx] = 1;
            }
            else    cnt[record[word]]++;
        }
         

        for(int i=0;i+len*n<=s_len;++i)
        {
            string tmp = s.substr(i,len);
            if(record[tmp]!=0)
            {
                vector<int> t_cnt = cnt;
                int flag = 1;
                for(int k=0;k<n;++k)
                {
                    tmp = s.substr(i+len*k,len);
                    if(t_cnt[record[tmp]])
                    {
                        t_cnt[record[tmp]]--;
                    }
                    else 
                    {
                        flag = 0;
                        break;
                    }
                }
                if(flag)    res.push_back(i);
            }
        }
        return res;
    }
};

