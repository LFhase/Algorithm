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


const int MAXN = 55;
const ll MOD = 1e9+7  ;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const int INF = 1e9+7;
const double PI = acos(-1.0);
const double EPS = 1e-8;

int _;

using namespace std;

char mapp[MAXN][MAXN];
int w, h;
vector<int> res;

void get_rid_x(int x, int y)
{
    mapp[x][y] = '*'; 
    if(x-1>=0&&mapp[x-1][y]=='X')   get_rid_x(x-1,y);
    if(x+1<h&&mapp[x+1][y]=='X')    get_rid_x(x+1,y);
    if(y-1>=0&&mapp[x][y-1]=='X')   get_rid_x(x,y-1);
    if(y+1<w&&mapp[x][y+1]=='X')    get_rid_x(x,y+1);
}

int rua(int x, int y)
{
    int cnt = 0;
    if(mapp[x][y]=='X') 
    {
        cnt++;
        get_rid_x(x,y);
    }
    mapp[x][y] = '.';
    if(x-1>=0&&mapp[x-1][y]!='.')   cnt+=rua(x-1,y);
    if(x+1<h&&mapp[x+1][y]!='.')    cnt+=rua(x+1,y);
    if(y-1>=0&&mapp[x][y-1]!='.')   cnt+=rua(x,y-1);
    if(y+1<w&&mapp[x][y+1]!='.')    cnt+=rua(x,y+1);
    return cnt;
}

int main()
{
    int tt = 0;
    while(scanf("%d%d",&w,&h)!=EOF)
    {
        tt++;
        res.clear();
        if(w==0&&h==0)  break;
        for(int i=0;i<h;++i)    scanf("%s",mapp[i]);
        for(int i=0;i<h;++i)
            for(int j=0;j<w;++j)
                if(mapp[i][j]!='.') 
                {
                    int rt = rua(i,j);
                    if(rt)  res.push_back(rt);
                }
        sort(res.begin(),res.end());
        printf("Throw %d\n",tt);
        for(int i=0;i<res.size();++i)
        {
            printf("%d",res[i]);
            if(i+1<res.size())  printf(" ");
            else printf("\n\n");
        }
        
    }
    return 0;
}
