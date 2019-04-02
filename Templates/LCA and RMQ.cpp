
// one demensional RMQ
int dp[2][MAXN][20];   // rmq
int mm[MAXN];   // log value
int val[MAXN];  // original array
int N;

void initRMQ()
{
    mm[0] = -1;
    for(int i=1;i<=N;++i)
    {
        mm[i] = ((i&(i-1))==0)?mm[i-1]+1:mm[i-1];
        dp[0][i][0] = dp[1][i][0] = val[i];
    }
    for(int j=1;j<=mm[N];++j)
        for(int i=1;i+(1<<j)-1<=N;++i)
            dp[0][i][j] = max(dp[0][i][j-1],dp[0][i+(1<<(j-1))][j-1]),
            dp[1][i][j] = min(dp[1][i][j-1],dp[1][i+(1<<(j-1))][j-1]);
}

int rmq(int x, int y)
{
    int k = mm[y-x+1];
    int maxn = max(dp[0][x][k],dp[0][y-(1<<k)+1][k]);
    int minn = min(dp[1][x][k],dp[1][y-(1<<k)+1][k]);
    return  maxn-minn;
}

// two demensional RMQ

int val[MAXN][MAXN];
int dp[2][MAXN][MAXN][9][9];
int mm[MAXN];
int N, M;

void initRMQ()
{
    mm[0] = -1;
    for(int i=1;i<=N;++i)
        mm[i] = ((i&(i-1)) == 0)?mm[i-1]+1:mm[i-1];
    for(int i=1;i<=N;++i)
        for(int j=1;j<=M;++j)
            dp[1][i][j][0][0] = dp[0][i][j][0][0] = val[i][j];
    for(int ii=0;ii<=mm[N];++ii)
        for(int jj=0;jj<=mm[M];++jj)
            if(ii+jj)
                for(int i=1;i+(1<<ii)-1<=N;++i)
                    for(int j=1;j+(1<<jj)-1<=M;++j)
                        if(ii)
                            dp[0][i][j][ii][jj]=max(dp[0][i][j][ii-1][jj],
                                                    dp[0][i+(1<<(ii-1))][j][ii-1][jj]),
                            dp[1][i][j][ii][jj]=min(dp[1][i][j][ii-1][jj],
                                                    dp[1][i+(1<<(ii-1))][j][ii-1][jj]);
                        else
                            dp[0][i][j][ii][jj]=max(dp[0][i][j][ii][jj-1],
                                                    dp[0][i][j+(1<<(jj-1))][ii][jj-1]),
                            dp[1][i][j][ii][jj]=min(dp[1][i][j][ii][jj-1],
                                                    dp[1][i][j+(1<<(jj-1))][ii][jj-1]);
}

int rmq(int x1, int y1, int x2, int y2)
{
    int k1 = mm[x2-x1+1];
    int k2 = mm[y2-y1+1];
    x2 = x2 - (1<<k1)+1;
    y2 = y2 - (1<<k2)+1;
    int maxn = max(max(dp[0][x1][y1][k1][k2],dp[0][x1][y2][k1][k2]),
                max(dp[0][x2][y1][k1][k2],dp[0][x2][y2][k1][k2]));
    int minn = min(min(dp[1][x1][y1][k1][k2],dp[1][x1][y2][k1][k2]),
                min(dp[1][x2][y1][k1][k2],dp[1][x2][y2][k1][k2]));
    return  maxn-minn;
}

int main()
{
    //freopen("input","r",stdin);
    //freopen("output","w+",stdout);
    int B, Q;
    while(scanf("%d%d%d",&N,&B,&Q)!=EOF)
    {
        M = N;
        for(int i=1;i<=N;++i)
            for(int j=1;j<=N;++j)
                scanf("%d",&val[i][j]);
        initRMQ();
        while(Q--)
        {
            int x1, y1;
            scanf("%d%d",&x1,&y1);
            printf("%d\n",rmq(x1,y1,x1+B-1,y1+B-1));
        }
    }
    return 0;
}


// LCA based on ST 
int head[MAXN];
int curedgeno;

struct Edge{
    int u, v;
    int next;
    Edge(int u=0, int v=0, int next=-1): u(u), v(v), next(next) {}
}edge[MAXN<<1];

void init()
{
    memset(head,-1,sizeof(head));
    curedgeno = 0;
}

void add_edge(int u, int v)
{
    ++curedgeno;
    edge[curedgeno] = Edge(u,v);
    edge[curedgeno].next = head[u];
    head[u] = curedgeno;
}

int rmq[MAXN<<1];
struct ST{
    int mm[MAXN<<1];
    int dp[MAXN<<1][20];
    void init(int N)
    {
        mm[0] = -1;
        for(int i=1;i<=N;++i)
        {
            mm[i] = ((i&(i-1))==0)?mm[i-1]+1:mm[i-1];
            dp[i][0] = i;
        }
        for(int j=1;j<=mm[N];++j)
            for(int i=1;i+(1<<j)-1<=N;++i)
                dp[i][j] = rmq[dp[i][j-1]]<=rmq[dp[i+(1<<(j-1))][j-1]]?
                            dp[i][j-1]:dp[i+(1<<(j-1))][j-1];

    }

    int query(int a, int b)
    {
        if(a>b) swap(a,b);
        int k = mm[b-a+1];
        return rmq[dp[a][k]] <= rmq[dp[b-(1<<k)+1][k]]?dp[a][k]:dp[b-(1<<k)+1][k];
    }
};

int F[MAXN<<1];
int P[MAXN];
int cnt;
ST st;

void dfs(int u,int pre,int dep)
{
    F[++cnt] = u;
    rmq[cnt] = dep;
    P[u] = cnt;
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        int v = edge[i].v;
        if(v==pre) continue;
        dfs(v,u,dep+1);
        F[++cnt] = u;
        rmq[cnt] = dep;
    }
}

void LCA_init(int root, int node_num)
{
    cnt = 0;
    dfs(root,root,0);
    st.init((node_num<<1)-1);
}

int query_lca(int u, int v)
{
    return F[st.query(P[u],P[v])];
}

bool flag[MAXN];

int main()
{
    //freopen("input","r",stdin);
    //freopen("output","w+",stdout);
    int N;
    cin>>_;
    while(_--)
    {
        scanf("%d",&N);
        int u, v;
        init();
        memset(flag,0,sizeof(flag));
        for(int i=1;i<N;++i)
        {
            scanf("%d%d",&u,&v);
            add_edge(u,v);
            add_edge(v,u);
            flag[v] = 1;
        }
        int root;
        for(int i=1;i<=N;++i)
            if(!flag[i])
            {
                root = i;
                break;
            }
        LCA_init(root,N);
        scanf("%d%d",&u,&v);
        printf("%d\n",query_lca(u,v));
    }
    return 0;
}



// LCA based on DP
int head[MAXN];
int curedgeno;

struct Edge{
    int u, v;
    int next;
    Edge(int u=0, int v=0, int next=-1): u(u), v(v), next(next) {}
}edge[MAXN<<1];

void init()
{
    memset(head,-1,sizeof(head));
    curedgeno = 0;
}

void add_edge(int u, int v)
{
    ++curedgeno;
    edge[curedgeno] = Edge(u,v);
    edge[curedgeno].next = head[u];
    head[u] = curedgeno;
}


const int DEG = 30;

bool flag[MAXN];
queue<int> togo;

int fa[MAXN][DEG];
int deg[MAXN];

void BFS(int root)
{
    while(!togo.empty())    togo.pop();
    deg[root] = 0;
    fa[root][0] = root;
    togo.push(root);
    while(!togo.empty())
    {
        int tmp = togo.front();
        togo.pop();
        for(int i=1;i<DEG;++i)
            fa[tmp][i] = fa[fa[tmp][i-1]][i-1];
        for(int i=head[tmp];i!=-1;i=edge[i].next)
        {
            int v = edge[i].v;
            if(v==fa[tmp][0])   continue;
            deg[v] = deg[tmp] + 1;
            fa[v][0] = tmp;
            togo.push(v);
        }
    }
}

int query_lca(int u, int v)
{
    if(deg[u]>deg[v])   swap(u,v);
    int hu = deg[u], hv = deg[v];
    int tu = u, tv = v;
    for(int det=hv-hu,i=0;det;det>>=1,++i)
        if(det&1)
            tv = fa[tv][i];
    if(tu==tv)  return tu;
    for(int i=DEG-1;i>=0;--i)
    {
        if(fa[tu][i]==fa[tv][i])    continue;
        tu = fa[tu][i];
        tv = fa[tv][i];
    }
    return fa[tu][0];
}

int query_kthfa(int u, int k)
{
    for(int i=0;i<DEG;++i)
        if((k>>i)&1)    u = fa[u][i];
    return u;
}


// Linear Base

struct linear_base
{
    ll base[65];
    linear_base()
    {
        memset(base,0,sizeof(base));
    }
    inline void ins(ll x)
    {
        IREP(i,60,0)
        if((x>>i)&1)
        {
            if(base[i])    x^=base[i];
            else
            {
                base[i] = x;
                break;
            }
        }
    }
    inline ll ask()
    {
        ll t = 0;
        IREP(i,60,0)
        if(!((t>>i)&1)&&base[i])    t^=base[i];
        return t;
    }
    linear_base merge(linear_base b)
    {
        linear_base res = *this;
        IREP(i,60,0)
        {
            if(!b.base[i])  continue;
            IREP(j,i,0)
            {
                if(!((b.base[i]>>j)&1)) continue;
                if(!res.base[j])
                {
                    res.base[j] = b.base[i];
                    break;
                }
                else    b.base[i]^=res.base[j];
            }
        }
        return res;
    }
}lans[MAXN][30];

struct ST{
    int mm[MAXN<<1];
    int dp[MAXN<<1][20];
    int dp_mx[MAXN<<1][20];
    int* rmq;
    void init(int N, int* rmq)
    {
        this->rmq = rmq;
        mm[0] = -1;
        for(int i=1;i<=N;++i)
        {
            mm[i] = ((i&(i-1))==0)?mm[i-1]+1:mm[i-1];
            dp[i][0] = i; dp_mx[i][0] = i;
        }
        for(int j=1;j<=mm[N];++j)
            for(int i=1;i+(1<<j)-1<=N;++i)
                dp[i][j] = rmq[dp[i][j-1]]<rmq[dp[i+(1<<(j-1))][j-1]]?
                            dp[i][j-1]:dp[i+(1<<(j-1))][j-1];

        for(int j=1;j<=mm[N];++j)
            for(int i=1;i+(1<<j)-1<=N;++i)
                dp_mx[i][j] = rmq[dp_mx[i][j-1]]>rmq[dp_mx[i+(1<<(j-1))][j-1]]?
                            dp_mx[i][j-1]:dp_mx[i+(1<<(j-1))][j-1];

    }

    int query_mm(int a, int b)
    {
        if(a>b) swap(a,b);
        int k = mm[b-a+1];
        return rmq[dp[a][k]] <= rmq[dp[b-(1<<k)+1][k]]?dp[a][k]:dp[b-(1<<k)+1][k];
    }

    int query_mx(int a, int b)
    {
        if(a>b) swap(a,b);
        int k = mm[b-a+1];
        return rmq[dp_mx[a][k]] >= rmq[dp_mx[b-(1<<k)+1][k]]?dp_mx[a][k]:dp_mx[b-(1<<k)+1][k];
    }
};