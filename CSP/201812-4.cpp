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
int father[MAXN];
int N, M;

void init( )
{
    int i;
    for(i=1;i<=N;i++)
        father[i]=i;
}

int find(int x)
{
    while(father[x]!=x)
        x=father[x];
    return x;
}

void merge(int a,int b)
{
    int temp_a,temp_b;
    temp_a=find(a);
    temp_b=find(b);
    if(temp_a<temp_b)   swap(temp_a,temp_b);
    if(temp_a!=temp_b)
        father[temp_a]=temp_b;
}

struct edge
{
    int u,v;
    int cost;
    edge(int a=0,int b=0,int c=0):u(a), v(b), cost(c) {}
}edges[MAXN<<1];

bool operator<(const edge& a, const edge& b)
{
    return a.cost < b.cost;
}

int ans;

int kruskal()
{
    sort(edges+1,edges+1+M);
    init();
    int res = 0;
    edge temp;
    int cnt = 0;
    for(int i=1;i<=M;++i)
    {
        temp = edges[i];
        if(find(temp.u)!=find(temp.v))
        {
            merge(temp.u,temp.v);
            res += temp.cost;
            cnt++;
            ans = max(ans,temp.cost);
        }
    }
    if(cnt<N-1) return -1;
    return res;
}

int main()
{
    //freopen("test.in","r+",stdin);
    //freopen("test.out","w+",stdout);
    //FSIO;
    cin>>N;
    int root;

    int u, v, w;
    cin>>M;
    cin>>root;
    for(int i=1;i<=M;++i)
    {
        cin>>u>>v>>w;
        edges[i] = edge(u,v,w);
    }
    kruskal();
    cout<<ans<<endl;
    return 0;
}
