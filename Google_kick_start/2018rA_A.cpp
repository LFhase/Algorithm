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
#include <sstream>

using namespace std;

#define FSIO  ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define DEBUG(a)   cout<<"DEBUG: "<<(a)<<endl;
#define ll long long
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
const ll MOD = 1e9+7 ;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const int INF = 1e9+7;
const double PI = acos(-1.0);
const double EPS = 1e-8;

int _;

using namespace std;

int dig[20];
ll pow_10[20];

void init()
{
    pow_10[0] = 1LL;
    for(int i=1;i<=16;++i)  pow_10[i]=pow_10[i-1]*10LL;
}

ll dfs(int len, int is_ge)
{
    if(len<0)    return 0;
    if(!is_ge&&dig[len]%2==0)   return dfs(len-1,is_ge);
    if(is_ge==1)
    {
        return -1LL*dig[len]*pow_10[len]+dfs(len-1,is_ge);
    }
    else if(is_ge==-1)
    {
        return -1LL*(8-dig[len])*pow_10[len]+dfs(len-1,is_ge);
    }
    else
    {
        if(dig[len]==9) return 1LL*pow_10[len]+dfs(len-1,-1);
        return min(1LL*pow_10[len]+dfs(len-1,-1),1LL*pow_10[len]+dfs(len-1,1));
    }
}

ll solve(ll n)
{
    int len = 0;
    while(n)
    {
        dig[len++] = n%10;
        n/=10LL;
    }

    return dfs(len-1, 0);
}


int main()
{
    //freopen("test.in","r+",stdin);
    //freopen("test.out","w+",stdout);
    FSIO;
    init();
    ll n;
    int T;  cin>>T;
    for(int t=1;t<=T;++t)
    {
        cin>>n;
        cout<<"Case #"<<t<<": ";
        cout<<solve(n)<<endl;
    }
    return 0;
}
