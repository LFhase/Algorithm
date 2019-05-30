/*
 * @lc app=leetcode.cn id=632 lang=cpp
 *
 * [632] 最小区间
 */
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <stack>
#include <bitset>

using namespace std;

#define FSIO  ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define DEBUG(a)   cout<<"DEBUG: "<<(a)<<endl;
#define ll  long long
#define ull unsigned long long
#define ld long double
#define pb push_back
#define MP make_pair
#define X  first
#define Y  second
#define REP(i,st,ed)    for(int i=st;i<=ed;++i)
#define IREP(i,st,ed)   for(int i=st;i>=ed;--i)
#define TCASE(T)    cin>>T;while(T--)


const int MAXN = 100005;
const ll MOD = 1e9+7  ;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const int INF = 1e9+7;
const double PI = acos(-1.0);
const double EPS = 1e-8;

int _;

using namespace std;
class Solution {
public:
    void compare(int& ansl, int& ansr, int& l, int& r)
    {
        if((r-l<ansr-ansl)||((r-l==ansr-ansl)&&l<ansl))
        {
            ansl = l;
            ansr = r;
        }
    }

    vector<int> smallestRange(vector<vector<int>>& nums) {
        int k = nums.size();
        vector<int> mk(k,0);
        vector<pair<int,int>> num;
        for(int i=0;i<k;++i)
        {
            for(int u:nums[i])
            {
                num.push_back(make_pair(u,i));
            }
        }
        sort(num.begin(),num.end());
        int l = 0;
        int r = 0;
        mk[num[l].Y] = 1;
        int cnt = 1;

        int ansl=num[0].X;
        int ansr=num[num.size()-1].X;

        while(l<num.size())
        {
            if(cnt==k)
            {
                compare(ansl,ansr,num[l].X,num[r].X);
                mk[num[l].Y]--;
                if(mk[num[l].Y]==0) cnt--;
                l++;
                if(l>=num.size())    break;

            }
            else
            {
                r++;
                if(r>=num.size())    break;
                mk[num[r].Y]++;
                if(mk[num[r].Y]==1) cnt++;
            }

        }
        vector<int> res;
        res.push_back(ansl);
        res.push_back(ansr);
        return res;
    }
};


int main()
{

    cin>>_;
    vector<vector<int>> togo;
    while(_--)
    {
        vector<int> tmp;
        int temp;
        int len;
        cin>>len;
        while(len--)
        {
            cin>>temp;
            tmp.pb(temp);
        }
        togo.pb(tmp);
    }
    Solution().smallestRange(togo);
    return 0;
}


