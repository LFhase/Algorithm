/*
 * @lc app=leetcode.cn id=434 lang=cpp
 *
 * [434] 字符串中的单词数
 */
class Solution {
public:
    int countSegments(string s) {
        int res = 0;
        int len = s.length();
        int flag = 0;
        for(int i=0;i<len;++i)
        {
            if(flag==0&&s[i]!=' ')  flag = 1;
            if(flag==1&&s[i]==' ')
            {
                res++;
                flag = 0;
            }
        }
        if(flag)    res++;
        return res;
    }
};

