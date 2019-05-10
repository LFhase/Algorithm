/*
 * @lc app=leetcode.cn id=354 lang=cpp
 *
 * [354] 俄罗斯套娃信封问题
 */
class Solution {
public:
    vector<int> nums;
    vector<pair<int,int>> evp;
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int len = envelopes.size();
        for(int i=0;i<len;++i)
        {
            evp.push_back(make_pair(envelopes[i][0],envelopes[i][1]));
        }
        sort(evp.begin(),evp.end());
        nums = vector<int>(len,1);
        int res = 0;
        for(int i=0;i<len;++i)
        {
            for(int j=0;j<i;++j)
            {
                if(evp[i].first>evp[j].first&&evp[i].second>evp[j].second)
                {
                    nums[i] = max(nums[i],nums[j]+1);
                }
            }
            res = max(res,nums[i]);
        }
        
        return res;
    }
};

