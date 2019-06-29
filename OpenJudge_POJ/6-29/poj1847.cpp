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


int main()
{
    int T;
    cin>>T;
    int odd_ans = 0;
    int even_ans = 0;
    while(T--)
    {
        int tmp;
        cin>>tmp;
        int n_odd = odd_ans;
        int n_even = even_ans;
        if(even_ans+tmp>odd_ans)    n_odd = even_ans+tmp;
        if(odd_ans-tmp>even_ans)    n_even = odd_ans-tmp;
        odd_ans = n_odd;
        even_ans = n_even;
    }
    cout<<(max(odd_ans,even_ans))<<endl;
    return 0;
}
