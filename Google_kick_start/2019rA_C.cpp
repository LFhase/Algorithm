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

const int MAXN = 1000005;
const ll MOD = 998244353  ;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const int INF = 1e9+7;
const double PI = acos(-1.0);
const double EPS = 1e-8;

int _;

using namespace std;



int l[MAXN], r[MAXN], bias[MAXN];
int N;
int Q;
int mk[MAXN];
vector<pair<int,int>> book;

int judge(int k)
{
    REP(i,1,Q)  l[i]=book[i-1].X, r[i]=-book[i-1].Y, bias[i]=book[i-1].X;

    REP(i,1,Q)
    {
        int st = bias[i];
        int ed = r[i];
        int cnt = 0;
        REP(j,i+1,Q)
        {
            if(r[j]<=r[i])
            {
                if(l[j]<=st)
                {
                    st = max(r[j]+1,st);
                }
                else
                {
                    cnt += l[j]-st;
                    st = max(st,r[j]+1);
                    if(cnt>=k)
                    {
                        ed = l[j]-(cnt-k);
                        break;
                    }
                }
            }
        }
        if(cnt<k)
        {
            cnt += r[i]-st+1;
            if(cnt<k)   return 0;
            ed = r[i]-(cnt-k)+1;
        }
        REP(j,i+1,Q)
        {
            if(l[j]>=ed)    break;
            if(r[j]>r[i])
            {
                bias[j] = max(bias[j],r[i]+1);
            }
        }
    }
    return 1;
}

int main()
{
    //freopen("test.in","r+",stdin);
    //freopen("test.out","w+",stdout);
    FSIO;
    int T;  cin>>T;
    for(int tt=1;tt<=T;++tt)
    {
        cin>>N>>Q;
        book.clear();
        REP(i,1,Q)
        {
            cin>>l[i]>>r[i];
            book.pb(MP(l[i],-r[i]));
        }
        sort(book.begin(),book.end());
        int L = 0;
        int R = N;
        int ans = -1;
        while(L<=R)
        {
            int mid = (L+R)>>1;
            if(judge(mid))
            {
                ans = mid;
                L = mid+1;
            }
            else
            {
                R = mid-1;
            }
        }

        cout<<"Case #"<<tt<<": "<<ans<<endl;
    }

    return 0;
}
