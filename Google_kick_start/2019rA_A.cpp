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

int stu[MAXN];

int main()
{
    //freopen("test.in","r+",stdin);
    //freopen("test.out","w+",stdout);
    FSIO;
    int T; cin>>T;
    for(int tt=1;tt<=T;++tt)
    {

        int N, P;
        cin>>N>>P;
        REP(i,1,N)  cin>>stu[i];
        sort(stu+1,stu+1+N);
        int rating = stu[P];
        ll cost = 0;
        ll last_cost = 0;
        REP(i,1,P)  cost += 1LL*(rating-stu[i]);
        last_cost = cost;
        REP(i,P+1,N)
        {
            ll tmp_cost = 1LL*(P-1)*(stu[i]-stu[i-1])+last_cost-(rating-stu[i-P]);
            cost = min(tmp_cost,cost);
            rating = stu[i];
            last_cost = tmp_cost;
        }
        cout<<"Case #"<<tt<<": ";
        cout<<cost<<endl;
    }

    return 0;
}
