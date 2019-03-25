#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <string>
#include <vector>
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

const int MAXN = 200005;
const ll MOD = 998244353  ;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const int INF = 1e9+7;
const double PI = acos(-1.0);
const double EPS = 1e-8;

int _;

using namespace std;

int aa[MAXN];
ll ram[MAXN];


ll powermod(ll n,ll k, ll MOD)
{
    ll ans=1;
    while(k)
    {
        if(k&1)
        {
            ans=((ans%MOD)*(n%MOD))%MOD;
        }
        n=((n%MOD)*(n%MOD))%MOD;
        k>>=1;
    }
    return ans;
}

ll dp[MAXN][2];
vector<int> togo;
ll N, K;

ll solve()
{
    if(togo.size()==0)  return 1;
    else if(togo.size()==1)
    {
        if(togo[0]==-1) return K;
        else    return 1;
    }

    int first = togo[0];
    int last = togo[togo.size()-1];
    if(first==last&&first!=-1&&togo.size()==2)  return 0;
    if(first==-1&&last==-1) return powermod(K-1,togo.size()-1,MOD)*K%MOD;
    if(first==-1||last==-1) return powermod(K-1,togo.size()-1,MOD);

    int len = togo.size();

    dp[0][0] = 1;
    dp[1][0] = K-2+(first==last);
    dp[1][1] = !(first==last);
    for(int i=2;i+1<len;++i)
    {
        if(togo[i+1]!=last)
        {
            dp[i][1] = dp[i-1][0];
            dp[i][0] = (dp[i-1][1]*(K-1)%MOD+dp[i-1][0]*(K-2)%MOD)%MOD;
        }
        else
        {
            //dp[i][1] = dp[i-1][0];
            dp[i][0] = (dp[i-1][1]*(K-1)%MOD+dp[i-1][0]*(K-2)%MOD)%MOD;
        }
    }
    return dp[len-2][0];
}


int main()
{
    //freopen("test.in","r+",stdin);
    //freopen("test.out","w+",stdout);
    FSIO;
    while(cin>>N>>K)
    {
        ll res = -1;
        memset(ram,-1,sizeof(ram));
        REP(i,1,N)  cin>>aa[i];
        togo.clear();
        for(int i=1;i<=N;i+=2)
        {
            if(aa[i]!=-1)
            {
                togo.pb(aa[i]);
                if(res==-1) res = solve();
                else    res = res*solve()%MOD;
                togo.clear();
                togo.pb(aa[i]);
            }
            else    togo.pb(aa[i]);
        }
        if(!togo.empty())
        {
            if(res==-1) res = solve();
            else    res = res*solve()%MOD;
            togo.clear();
        }
        for(int i=2;i<=N;i+=2)
        {
            if(aa[i]!=-1)
            {
                togo.pb(aa[i]);
                if(res==-1) res = solve();
                else    res = res*solve()%MOD;
                togo.clear();
                togo.pb(aa[i]);
            }
            else    togo.pb(aa[i]);
        }
        if(!togo.empty())
        {
            if(res==-1) res = solve();
            else    res = res*solve()%MOD;
            togo.clear();
        }
        cout<<res%MOD<<endl;
    }

    return 0;
}
