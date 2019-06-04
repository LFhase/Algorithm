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


const int MAXN = 20005;
const ll MOD = 1e9+7  ;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const int INF = 1e9+7;
const double PI = acos(-1.0);
const double EPS = 1e-8;

int _;

using namespace std;

int bowl[10][5];
double G[10][10];
int n;
int mk[10];
double height[10];
int sel[10];

double get_reward(int a, int b)
{
    if(bowl[b][1]>=bowl[a][2])  return bowl[a][0];
    if(bowl[b][2]<=bowl[a][1])  return 0;

    double res = 0;
    if(bowl[b][1]>=bowl[a][1])
    {
        res = max(res,
                  (double)bowl[a][0]*(bowl[b][1]-bowl[a][1])*1.0/(bowl[a][2]-bowl[a][1]));
    }
    if(bowl[b][2]<=bowl[a][2])
    {
        res = max(res,
                  (double)bowl[a][0]*(bowl[b][2]-bowl[a][1])*1.0/(bowl[a][2]-bowl[a][1])-(double)bowl[b][0]);
    }
    if(bowl[b][2]>=bowl[a][2])
    {
        res = max(res,
                  (double)bowl[a][0]-bowl[b][0]*(bowl[b][1]-bowl[a][2])*1.0/(bowl[b][1]-bowl[b][2]));
    }
    return res;
}

int ans;

void rua(int step)
{
    if(step<=0)
    {
        memset(height,0,sizeof(height));
        double res = 0;
        for(int i=n;i>=1;--i)
        {
            for(int j=i+1;j<=n;++j)
            {
                height[sel[i]] = max(height[sel[i]],height[sel[j]]+G[sel[j]][sel[i]]);
            }
            res = max(res,height[sel[i]]+bowl[sel[i]][0]);
        }
        /*for(int i=1;i<=n;++i)
            cout<<height[i]<<" ";
        cout<<endl;*/
        ans = min(ans,(int)res);
        return;
    }
    for(int i=1;i<=n;++i)
    {
        if(!mk[i])
        {
            mk[i] = 1;
            sel[step] = i;
            rua(step-1);
            mk[i] = 0;
        }
    }
}

int main()
{

    TCASE(_)
    {
        scanf("%d",&n);
        memset(mk,0,sizeof(mk));

        for(int i=1;i<=n;++i)
        {
            scanf("%d%d%d",bowl[i],bowl[i]+1,bowl[i]+2);
        }
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                G[i][j] = get_reward(i,j);

        memset(mk,0,sizeof(mk));
        ans = 0x3f3f3f3f;
        rua(n);
        printf("%d\n",ans);
    }

    return 0;
}
