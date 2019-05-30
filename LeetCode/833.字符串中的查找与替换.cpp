/*
 * @lc app=leetcode.cn id=833 lang=cpp
 *
 * [833] 字符串中的查找与替换
 */
class Solution {
public:
    string findReplaceString(string S, vector<int>& indexes, vector<string>& sources, vector<string>& targets) {
        vector<pair<int,int>> mask;
        
        string res;
        int ixlen = indexes.size();
        int slen = S.length();
        int ixcur = 0;
        int scur = 0;
        
        for(int i=0;i<ixlen;++i)
        {
            mask.push_back(make_pair(indexes[i],i));
        }
        sort(mask.begin(),mask.end());
        
        while(ixcur<ixlen)
        {
            if(scur==indexes[mask[ixcur].second])
            {
                int flag = 1;
                for(int j=0;j<sources[mask[ixcur].second].length();++j)
                {
                    if(S[j+scur]!=sources[mask[ixcur].second][j])
                    {
                        flag = 0;
                        break;
                    }
                }
                
                if(!flag)   
                {
                    ixcur++;
                    continue;
                }
                for(int j=0;j<targets[mask[ixcur].second].length();++j)
                {
                    res.push_back(targets[mask[ixcur].second][j]);
                } 
                scur+=sources[mask[ixcur].second].length();
                ixcur++;
            }
            else
            {
                res.push_back(S[scur]);
                scur++;
            }
        }
        while(scur<slen)
        {
            res.push_back(S[scur]);
            scur++;
        }
        return res;
    }
};

