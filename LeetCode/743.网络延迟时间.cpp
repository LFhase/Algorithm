/*
 * @lc app=leetcode.cn id=743 lang=cpp
 *
 * [743] 网络延迟时间
 */
class Solution {
public:
    vector<vector<pair<int,int>>>   G;
    vector<int> mask;
    
    void rua(int u, int cost)
    {
        if(mask[u]!=-1&&mask[u]<=cost)     return;
        mask[u] = cost;
        for(pair<int,int> p: G[u])
        {
            int v = p.first;
            int w = p.second;
            rua(v,cost+w);
        }
    }
    
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        int len = times.size();
        mask = vector<int>(N+1,-1);
        G = vector<vector<pair<int,int>>>(N+1,vector<pair<int,int>>());
        for(int i=0;i<len;++i)
        {
            int u = times[i][0];
            int v = times[i][1];
            int w = times[i][2];
            G[u].push_back(make_pair(v,w));
        }
        priority_queue<pair<int,int>> togo;
        togo.push(make_pair(0,K));
        mask[K] = 0;
        while(!togo.empty())
        {
            pair<int,int> p = togo.top();  
            togo.pop();
            int u = p.second;
            int cc = -p.first;
            if(mask[u]<cc) continue;
            for(pair<int,int> p: G[u])
            {
                int v = p.first;
                int w = p.second;
                if(mask[v]==-1||mask[v]>w+cc)
                {
                    mask[v] = w+cc;
                    togo.push(make_pair(-w-cc,v));
                }
            }
        }
        //rua(K,0);
        int res = 0;
        for(int i=1;i<=N;++i)  
        {
            if(mask[i]==-1)
            {
                res = -1;
                break;
            }
            else    res = max(res,mask[i]);
        }
        return res;
    }
};
