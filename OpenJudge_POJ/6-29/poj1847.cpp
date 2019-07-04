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


const int MAXN = 105;
const ll MOD = 1e9+7  ;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const int INF = 1e9+7;
const double PI = acos(-1.0);
const double EPS = 1e-8;

int _;

using namespace std;

vector<int> G[MAXN];
int mk[MAXN];
int N;
int st, ed;
int res;

void dfs(int u, int cost)
{
    if(mk[u])   return;
    if(u==ed)   
    {
        res = min(res,cost);
        return;
    }
    if(cost>res) return;
    mk[u] = 1;
    for(int i=0;i<G[u].size();++i)
    {
        dfs(G[u][i],cost+(i!=0));
    }
    mk[u] = 0;
}


int main()
{
    while(scanf("%d%d%d",&N,&st,&ed)!=EOF)
    {
        for(int i=1;i<=N;++i)
        {
            G[i].clear();
            int K;
            scanf("%d",&K);
            int tmp;
            for(int j=1;j<=K;++j)
            {
                scanf("%d",&tmp);
                G[i].push_back(tmp);
            }
        }
        memset(mk,0,sizeof(mk));
        res = 1e9+7;
        dfs(st,0);
        if(res==1e9+7)  res=-1;
        printf("%d\n",res);
    }   
    return 0;
}
