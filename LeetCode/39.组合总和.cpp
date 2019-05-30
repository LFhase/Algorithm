/*
 * @lc app=leetcode.cn id=39 lang=cpp
 *
 * [39] 组合总和
 */
class Solution {
public:
    vector<vector<int>> res;
    
    void rua(vector<int>& candidates, vector<int>& para, int id, int target){
        if(id>=candidates.size()||candidates[id]>target)   return;
        for(int i=0;i<=target/candidates[id];++i)
        {
            para[id] = i;
            if(i*candidates[id]==target)
            {
                vector<int> tmp;
                for(int j=id;j>=0;--j)
                {
                    for(int k=para[j];k>0;--k)
                    {
                        tmp.push_back(candidates[j]);
                    }
                }
                res.push_back(tmp);
            }
            else
            {
                
                rua(candidates,para,id+1,target-candidates[id]*i);
            }
        }
    }
    
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(),candidates.end());
        res = vector<vector<int>>();
        if(candidates.size()==0)    return res;
        vector<int> para;
        for(int i=0;i<candidates.size();++i)
        {
            para.push_back(0);
        }
        rua(candidates,para,0,target);
        return res;
    }
};

