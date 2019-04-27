/*
 * @lc app=leetcode.cn id=386 lang=cpp
 *
 * [386] 字典序排数
 */
class Solution {
public:
    vector<int> lexicalOrder(int n) {
        int cur = 1;
        vector<int> res(n);
        
        for(int i=0;i<n;++i)
        {
            res[i] = cur;
            if(cur*10<=n)   cur*=10;
            else
            {
                if(cur >= n)  cur/=10;
                cur += 1;
                while(cur%10==0)    cur/=10;
            }
        }
        
        return res;
        
    }
};

