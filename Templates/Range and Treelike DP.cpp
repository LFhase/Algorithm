// range dp 
// verified by stone merge 
int xx[MAXN];
int prefix[MAXN];
int s[MAXN][MAXN];
int dp[MAXN][MAXN];
int N;

int cal(int i, int j, int k)
{
    if(k>=j)    return INF;
    else    return prefix[j]-prefix[k]+prefix[k]-prefix[i-1];
}

int main()
{
    //freopen("input","r",stdin);
    //freopen("output","w+",stdout);
    while(scanf("%d",&N)!=EOF)
    {
        for(int i=1;i<=N;++i)   scanf("%d",xx+i);
        for(int i=1;i<=N;++i)   xx[i+N] = xx[i];
        N*=2;
        prefix[0] = 0;
        for(int i=1;i<=N;++i)   prefix[i] = prefix[i-1]+xx[i];

        memset(dp,0,sizeof(dp));
        for(int i=1;i<=N;++i)   s[i][i]=i;
        for(int len=2;len<=N;++len)
            for(int l=1;l+len-1<=N;++l)
            {
                int r = l+len-1;
                dp[l][r] = INF;
                for(int k=s[l][r-1];k<=s[l+1][r];++k)
                {
                    int tmp = dp[l][k]+dp[k+1][r]+cal(l,r,k);
                    if(tmp<=dp[l][r])
                    {
                        dp[l][r]=tmp;
                        s[l][r]=k;
                    }
                }
            }
        int res = dp[1][N/2];
        for(int i=2;i+N/2-1<=N;++i)
            res = min(res,dp[i][i+N/2-1]);
        printf("%d\n",res);
    }
    return 0;
}



// stone merge: huge input 
// GarsiaWachs Algorithm
// using Btree with O(NlogN)
// now O(N*N)
int xx[MAXN];
int N;

int arr[MAXN];
int sz;
int res;

void go(int pos)
{
    arr[pos-1] += arr[pos];
    for(int i=pos;i<sz;++i)
        arr[i] = arr[i+1];
    res += arr[pos-1];
    int cur;
    int tmp = arr[pos-1];
    for(cur=pos-1;cur>=2&&arr[cur-1]<tmp;--cur)    arr[cur]=arr[cur-1];
    arr[cur]=tmp;
    sz--;
    /*cout<<sz<<": ";
    for(int i=0;i<=sz;++i)
        cout<<arr[i]<<" ";
    cout<<"---"<<res<<endl;*/
    while(cur>=3&&arr[cur]>=arr[cur-2])
    {
        int last = sz - cur;
        go(cur-1);
        cur = sz-last;
    }
}

int main()
{
    //freopen("input","r",stdin);
    //freopen("output","w+",stdout);
    while(scanf("%d",&N)!=EOF&&N)
    {
        for(int i=1;i<=N;++i)   scanf("%d",xx+i);
        res = 0;
        memset(arr,0,sizeof(arr));
        arr[0] = INF;
        sz = 0;
        for(int i=1;i<=N;++i)
        {
            arr[++sz]=xx[i];
            while(sz>=3&&arr[sz-2]<=arr[sz])    go(sz-1);
        }
        while(sz>1) go(sz);
        printf("%d\n",res);
    }
    return 0;
}



// Tree like DP
struct Edge{
    int u, v, w;
    int next;
    Edge(int u=0, int v=0, int w=0, int next=-1): u(u), v(v), w(w), next(next) {}
}edge[MAXN];
int head[MAXN];
int cnt_edge;

void init()
{
    memset(head,-1,sizeof(head));
    cnt_edge = 0;
}

void add_edge(int u, int v, int w)
{
    ++cnt_edge;
    edge[cnt_edge] = Edge(u,v,w);
    edge[cnt_edge].next = head[u];
    head[u] = cnt_edge;
}

int dp[MAXN][MAXN];
int N, Q;

void rua(int u, int fa)
{
    int lson = -1, wlson = -1;
    int rson = -1, wrson = -1;
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        int v = edge[i].v;
        if(v!=fa)
        {
            if(lson==-1){lson=v; wlson=edge[i].w; continue;}
            if(rson==-1){rson=v; wrson=edge[i].w; continue;}
        }
    }
    if(lson!=-1)    rua(lson,u);
    if(rson!=-1)    rua(rson,u);
    if(lson!=-1&&rson!=-1)
    {
        for(int i=1;i<=Q;++i)
        {
            dp[u][i] = max(dp[lson][i-1]+wlson,dp[u][i]);
            dp[u][i] = max(dp[rson][i-1]+wrson,dp[u][i]);
            for(int j=0;j+2<=i;++j)
                dp[u][i] = max(dp[u][i],dp[lson][j]+wlson+dp[rson][i-2-j]+wrson);
        }
    }
    else if(lson!=-1||rson!=-1)
    {
        int v = -1, w=-1;
        if(lson!=-1) v = lson, w=wlson;
        else    v = rson, w=wrson;

        for(int i=1;i<=Q;++i)
            dp[u][i] = max(dp[v][i-1]+w,dp[u][i]);
    }
}

int main()
{
    //freopen("input","r",stdin);
    //freopen("output","w+",stdout);
    while(scanf("%d%d",&N,&Q)!=EOF)
    {
        init();
        int u, v, w;
        for(int i=1;i<N;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            add_edge(u,v,w);
            add_edge(v,u,w);
        }
        memset(dp,0,sizeof(dp));
        rua(1,-1);
        printf("%d\n",dp[1][Q]);
    }
    return 0;
}
