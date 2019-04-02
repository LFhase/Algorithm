
// count the appearance of each digit in [a,b]
ll pow_10[20];
ll dp[15][15][15];

void init()
{
    pow_10[1] = 1LL;
    for(int i=2;i<=15;++i)   pow_10[i]=10LL*pow_10[i-1];
    for(int i=0;i<10;++i)   dp[1][i][i] = 1;
    for(int i=2;i<=12;++i)
        for(int j=0;j<10;++j)
            for(int k=0;k<10;++k)
            {
                for(int l=0;l<10;++l)
                    dp[i][j][l] += dp[i-1][k][l];
                dp[i][j][j] += pow_10[i-1];
            }
}

ll rans[10];
ll lans[10];

void solve(ll* ans, ll num)
{
    for(int i=0;i<10;++i)   ans[i]=0LL;
    if(num<0)   return;
    if(!num)
    {
        ans[0] = 1;
        return;
    }
    int len = 15;
    while(num<pow_10[len])  len--;

    for(int i=1;i<len;++i)
        for(int j=1;j<10;++j)
            for(int k=0;k<10;++k)
                ans[k] += dp[i][j][k];
    ans[0]++;
    int x = num/pow_10[len];
    for(int i=1;i<x;++i)
        for(int k=0;k<10;++k)
            ans[k] += dp[len][i][k];
    num%=pow_10[len];
    ans[x]+=num+1;
    len--;
    for(int t=len;t;--t)
    {
        int x = num/pow_10[t];
        for(int i=0;i<x;++i)
            for(int k=0;k<10;++k)
                ans[k] += dp[t][i][k];
        num%=pow_10[t];
        ans[x]+=num+1;
    }
}

int main()
{
    //freopen("input","r",stdin);
    //freopen("output","w+",stdout);
    ll a, b;
    init();
    while(scanf("%lld%lld",&a,&b)!=EOF)
    {
        solve(lans,a-1);
        solve(rans,b);
        for(int i=0;i<10;++i)   rans[i] -= lans[i];
        for(int i=0;i<9;++i)
            printf("%lld ",rans[i]);
        printf("%lld\n",rans[9]);
    }
    return 0;
}


// Bit Enumeration Inclusion-exclusion Algorithm
double pp[25];
int N;

int main()
{
    //freopen("input","r",stdin);
    //freopen("output","w+",stdout);
    while(scanf("%d",&N)!=EOF)
    {
        for(int i=1;i<=N;++i)   scanf("%lf",pp+i);
        double ans = 0;
        double tmp = 0;
        int cnt = 0;
        for(int i=1;i<(1<<N);++i)
        {
            tmp = 0;
            cnt = 0;
            for(int j=0;j<N;++j)
                if(1&(i>>j))
                {
                    cnt++;
                    tmp += pp[j+1];
                }
            if(cnt&1) ans += 1.0/tmp;
            else    ans -= 1.0/tmp;
        }
        printf("%.6f\n",ans);
    }


    return 0;
}



// Digit DP Template
ll dp[15][10];
ll dig[15];

int dfs(int pos, int pre, int limit, int zero)
{
    if(pos==0)  return 1;
    if(!limit&&!zero&&dp[pos][pre]!=-1) return dp[pos][pre];
    int top = limit?dig[pos]:9;

    int cnt = 0;
    for(int i=0;i<=top;++i)
    {
        if(zero||(pre-i)>=2||(i-pre)>=2)
        {
            if(i==0&&zero)  cnt += dfs(pos-1,i,0,1);
            else if(i==top&&limit)  cnt += dfs(pos-1,i,1,0);
            else    cnt += dfs(pos-1,i,0,0);
        }
    }
    if(!limit&&!zero)   dp[pos][pre]=cnt;
    return cnt;
}

ll solve(ll n)
{

    int len = 0;
    while(n)
    {
        dig[++len] = n%10;
        n/=10;
    }
    memset(dp,-1,sizeof(dp));
    return dfs(len,-2,1,1);
}

int main()
{
    //freopen("input","r",stdin);
    //freopen("output","w+",stdout);
    ll a, b;

    while(scanf("%lld%lld",&a,&b)!=EOF)
    {
        printf("%lld\n",solve(b)-solve(a-1LL));
    }
    return 0;
}

