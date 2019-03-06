/*
 * @lc app=leetcode.cn id=17 lang=cpp
 *
 * [17] 电话号码的字母组合
 *
 * https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number/description/
 *
 * algorithms
 * Medium (47.68%)
 * Total Accepted:    16.1K
 * Total Submissions: 33.8K
 * Testcase Example:  '"23"'
 *
 * 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。
 * 
 * 给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
 * 
 * 
 * 
 * 示例:
 * 
 * 输入："23"
 * 输出：["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
 * 
 * 
 * 说明:
 * 尽管上面的答案是按字典序排列的，但是你可以任意选择答案输出的顺序。
 * 
 */
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<vector<string> > map = {{"a","b","c"},
                                     {"d","e","f"},
                                     {"g","h","i"},
                                     {"j","k","l"},
                                     {"m","n","o"},
                                     {"p","q","r","s"},
                                     {"t","u","v"},
                                     {"w","x","y","z"}};
        vector<string> res;
        int len = digits.length();
        
        if(len==0)  return res;
        for(string c: map[(digits[0]-'0')-2])   res.push_back(c);
        for(int i=1;i<len;++i)
        {
            int sz = res.size();
            vector<string> tmp;
            for(string c: map[(digits[i]-'0')-2])
            {
                for(int j=0;j<sz;++j)
                {
                    tmp.push_back(res[j]+c);
                }
            }
            res = tmp;
            tmp.clear();
        }
        return res;
    }
};
