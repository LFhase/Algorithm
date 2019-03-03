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

int val[MAXN];
ll suf_sum[MAXN];


int main()
{
    //freopen("test.in","r+",stdin);
    //freopen("test.out","w+",stdout);
    //FSIO;
    int T; cin>>T;
    int N, K;
    for(int t=1;t<=T;++t)
    {
        cin>>N>>K;
        double res = 0;
        REP(i,1,N)
        {
            scanf("%d",val+i);//cin>>val[i];
            res += (double)val[i]/N;
        }
        sort(val+1,val+1+N);
        suf_sum[N+1] = 0;
        IREP(i,N,1) suf_sum[i]=suf_sum[i+1]+val[i];
        int cur = 0;
        while(K--)
        {
            while(cur<=N&&val[cur]<=res)    cur++;
            if(cur>N)   break;

            res = res*(cur-1)/N+(double)suf_sum[cur]/N;
        }
        printf("Case #%d: %.6f\n",t,res);
    }
    return 0;
}
