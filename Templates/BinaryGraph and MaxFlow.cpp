

// MAX FLow
// Dinic
struct edge{
    int to, cap, rev;
    edge(int a=0, int b=0, int c=0): to(a), cap(b), rev(c) {}
};

vector<edge> G[MAXN];

int level[MAXN];
int iter[MAXN];

void add_edge(int from, int to, int cap)
{
    G[from].push_back(edge(to,cap,G[to].size()));
    G[to].push_back(edge(from,0,G[from].size()-1));
}

void bfs(int s)
{
    memset(level,-1,sizeof(level));
    queue<int> que;
    level[s] = 0;
    que.push(s);
    while(!que.empty())
    {
        int v = que.front();
        que.pop();
        for(int i=0;i<G[v].size();++i)
        {
            edge& e = G[v][i];
            if(e.cap>0 && level[e.to]<0)
            {
                level[e.to] = level[v] + 1;
                que.push(e.to);
            }
        }
    }
}

int dfs(int v, int t, int f)
{
    if(v==t)    return f;
    for(int& i=iter[v]; i<G[v].size(); ++i)
    {
        edge& e = G[v][i];
        if(e.cap>0 && level[v]<level[e.to])
        {
            int d = dfs(e.to, t, min(f,e.cap));
            if(d>0)
            {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t)
{
    int flow = 0;
    while(1)
    {
        bfs(s);
        if(level[t]<0)  return flow;
        memset(iter,0,sizeof(iter));
        int f = dfs(s,t,INF);
        while(f>0)
        {
            flow += f;
            f = dfs(s,t,INF);
        }
    }
}


// MIN Cost

struct edge{
    int to, cap, cost, rev;
    edge(int a=0, int b=0, int c=0, int d=0): to(a), cap(b), cost(c), rev(d) {}
};

vector<edge> G[MAXN];
int level[MAXN];
int iter[MAXN];
int pre[MAXN], pree[MAXN];
int dis[MAXN], visit[MAXN], incnt[MAXN];
int N, M;

int spfa(int s, int t)
{
    memset(pre,-1,sizeof(pre));
    memset(visit,0,sizeof(visit));
    memset(incnt,0,sizeof(incnt));
    for(int i=0;i<=N+1;++i)   dis[i]=INF;
    deque<int> q;
    q.push_front(s);
    visit[s] = 1;
    dis[s] = 0;
    int flag = 1;
    int now, i, len;
    while (!q.empty())
    {
        now = q.front();
        q.pop_front();
        visit[now] = 0;
        len = G[now].size();
        for(i=0; i<len;++i)
        {
            edge& tmp = G[now][i];
            if (tmp.cap>0&&dis[tmp.to]>dis[now]+tmp.cost)
            {
                dis[tmp.to] = dis[now]+tmp.cost;
                pre[tmp.to] = now;
                pree[tmp.to] = i;
                if (!visit[tmp.to])
                {
                    incnt[tmp.to]++;
                    if(incnt[tmp.to]>N)
                    {
                        flag = 0;
                        break;
                    }
                    // SLF
                    if(!q.empty()&&dis[tmp.to]<dis[q.front()]) q.push_front(tmp.to);
                    else    q.push_back(tmp.to);
                    //q.push(tmp.v);
                    visit[tmp.to] = 1;
                }
            }
        }
        if(!flag)   break;
    }
    if(flag)    return dis[t]!=INF;
    else    return 0;
}

void add_edge(int from, int to, int cap, int cost)
{
    G[from].push_back(edge(to,cap,cost,G[to].size()));
    G[to].push_back(edge(from,0,-cost,G[from].size()-1));
}


void bfs(int s)
{
    memset(level,-1,sizeof(level));
    queue<int> que;
    level[s] = 0;
    que.push(s);
    while(!que.empty())
    {
        int v = que.front();
        que.pop();
        for(int i=0;i<G[v].size();++i)
        {
            edge& e = G[v][i];
            if(e.cap>0 && level[e.to]<0)
            {
                level[e.to] = level[v] + 1;
                que.push(e.to);
            }
        }
    }
}

int dfs(int v, int t, int f)
{
    if(v==t)    return f;
    for(int& i=iter[v]; i<G[v].size(); ++i)
    {
        edge& e = G[v][i];
        if(e.cap>0 && level[v]<level[e.to])
        {
            int d = dfs(e.to, t, min(f,e.cap));
            if(d>0)
            {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t)
{
    int flow = 0;
    while(1)
    {
        bfs(s);
        if(level[t]<0)  return flow;
        memset(iter,0,sizeof(iter));
        int f = dfs(s,t,INF);
        while(f>0)
        {
            flow += f;
            f = dfs(s,t,INF);
        }
    }
}
int maxflow;

int mfmc(int s, int t)
{
    int d;
    int mincost = 0;
    maxflow = 0;
    while(spfa(s,t))
    {
        d = INF;
        for(int i=t; i!=s; i=pre[i])
            d=min(d,G[pre[i]][pree[i]].cap);

        maxflow += d;
        for(int i=t; i!=s; i=pre[i])
        {
            edge& e = G[pre[i]][pree[i]];
            e.cap -= d;
            G[i][e.rev].cap += d;
        }
        mincost += dis[t]*d;
    }
    return mincost;
}




// MAX Flow
// ISAP

struct Edge{
    int to, cap, next;
}edge[MAXN];

int adj[MAXN], cntE;
int dis[MAXN], cur[MAXN], pre[MAXN], num[MAXN];
int source, sink, nv;
int N, M;

void init()
{
    memset(adj,-1,sizeof(adj));
    cntE = 0;
}

void add_edge(int from, int to, int cap)
{
    edge[cntE].to = to;
    edge[cntE].cap = cap;
    edge[cntE].next = adj[from];
    adj[from] = cntE++;

    edge[cntE].to = from;
    edge[cntE].cap = 0;
    edge[cntE].next = adj[to];
    adj[to] = cntE++;
}

void rev_bfs()
{
    memset(num,0,sizeof(num));
    memset(dis,-1,sizeof(dis));
    dis[sink] = 0;
    num[0] = 1;
    queue<int> qqq;
    qqq.push(sink);
    while(!qqq.empty())
    {
        int u = qqq.front();
        qqq.pop();
        for(int i=adj[u];~i;i=edge[i].next)
        {
            int v = edge[i].to;
            if(~dis[v]) continue;
            dis[v] = dis[u] + 1;
            qqq.push(v);
            num[dis[v]]++;
        }
    }
}


int ISAP(int s, int t)
{
    source = s;
    sink = t;
    nv = t+1;
    memcpy(cur,adj,sizeof(adj));
    rev_bfs();
    int flow = 0;
    int u = pre[source] = source;
    while(dis[sink]<nv)
    {
        if(u==sink)
        {
            int f = INF;
            int neck;
            for(int i=source;i!=sink;i=edge[cur[i]].to)
            {
                if(f>edge[cur[i]].cap)
                {
                    f = edge[cur[i]].cap;
                    neck = i;
                }
            }
            for(int i=source;i!=sink;i=edge[cur[i]].to)
            {
                edge[cur[i]].cap -= f;
                edge[cur[i]^1].cap += f;
            }
            flow += f;
            u = neck;
        }
        int i;
        for(i=cur[u];~i;i=edge[i].next)
        {
            if(dis[edge[i].to]+1 == dis[u] && edge[i].cap)
                break;
        }
        if(~i)
        {
            cur[u] = i;
            pre[edge[i].to] = u;
            u = edge[i].to;
        }
        else
        {
            if((--num[dis[u]])==0)  break;
            int cnt = nv;
            for(i=adj[u];~i;i=edge[i].next)
            {
                if(edge[i].cap&&cnt>dis[edge[i].to])
                {
                    cur[u] = i;
                    cnt = dis[edge[i].to];
                }
            }
            dis[u] = cnt + 1;
            num[dis[u]]++;
            u = pre[u];
        }
    }
    return flow;
}





// 最小点覆盖 = 最大匹配数
// 最小边覆盖 = 最大独立集 = N - 最大匹配
// DAG图最小路径覆盖  =  N  - 最大匹配



// Hungary Algorithm 
vector<int> mapp[MAXN];
int inpath[MAXN];
int coverd[MAXN];
int N, M;

int find(int s)
{
    for(int i=0;i<mapp[s].size();++i)
    {
        if(!inpath[mapp[s][i]])
        {
            inpath[mapp[s][i]] = 1;
            if(!coverd[mapp[s][i]] || find(coverd[mapp[s][i]]))
            {
                coverd[mapp[s][i]] = s;
                return 1;
            }
        }
    }
    return 0;
}



// i: 1->N maximum lexicographic
//    N->1 minimum lexicographic
int hungary()
{
    memset(inpath,0,sizeof(inpath));
    memset(coverd,0,sizeof(coverd));
    int res = 0;
    for(int i=1;i<=N;++i)
    {
        memset(inpath,0,sizeof(inpath));
        if(find(i)) res++;
    }
    return res;
}


// KM Algorithm
// verified by HDU 2255
int mapp[MAXN][MAXN];   
int slack[MAXN];
int mapping[MAXN], lx[MAXN], ly[MAXN];
int Nx, Ny;
bool mkx[MAXN], mky[MAXN];
int N;

int dfs(int x)
{
    mkx[x] = 1;
    for(int y=1;y<=Ny;++y)
    {
        if(mky[y])  continue;
        int tmp = lx[x] + ly[y] - mapp[x][y];
        if(!tmp)
        {
            mky[y] = 1;
            if(!mapping[y]||dfs(mapping[y]))
            {
                mapping[y] = x;
                return 1;
            }
        }
        else slack[y] = min(slack[y], tmp);
    }
    return 0;
}

int KM()
{
    memset(mapping,0,sizeof(mapping));
    memset(ly,0,sizeof(ly));
    for(int i=1;i<=Nx;++i)
    {
        lx[i] = -INF;
        for(int j=1;j<=Ny;++j)
            lx[i] = max(lx[i], mapp[i][j]);
    }
    for(int x=1;x<=Nx;++x)
    {
        for(int i=1;i<=Ny;++i)  slack[i] = INF;
        while(1)
        {
            memset(mkx,0,sizeof(mkx));
            memset(mky,0,sizeof(mky));
            if(dfs(x))  break;
            int d = INF;
            for(int i=1;i<=Ny;++i)
                if(!mky[i])
                    d = min(d,slack[i]);
            for(int i=1;i<=Nx;++i)
                if(mkx[i])
                    lx[i] -= d;
            for(int i=1;i<=Ny;++i)
            {
                if(mky[i])  ly[i]+=d;
                else    slack[i]-=d;
            }
        }
    }
    int res = 0;
    for(int i=1;i<=Ny;++i)
        if(mapping[i]!=-1)
            res += mapp[mapping[i]][i];
    return res;
}

int main()
{
    //freopen("input","r",stdin);
    //freopen("output","w+",stdout);
    while(scanf("%d",&N)!=EOF)
    {
        for(int i=1;i<=N;++i)
            for(int j=1;j<=N;++j)
                scanf("%d",&mapp[i][j]);
        Nx = Ny = N;
        printf("%d\n",KM());
    }
    return 0;
}

// Maximal Clique   [POJ2989]
int mapp[MAXN][MAXN];
int N, M;
int ans;
int some[MAXN][MAXN];
int all[MAXN][MAXN];
int none[MAXN][MAXN];

void bk_dfs(int d, int all_n, int some_n, int none_n)
{
    if(!some_n&&!none_n)    ans++;
    if(ans>1000)    return;
    // choose a pivot vertex
    int u = some[d][1];
    REP(i,1,some_n)
    {
        int v = some[d][i];
        // pivoting optimization
        if(mapp[u][v])  continue;
        REP(j,1,all_n)  all[d+1][j] = all[d][j];
        all[d+1][all_n+1] = v;
        int tsn=0, tnn=0;
        REP(j,1,some_n)
            if(mapp[v][some[d][j]])
                some[d+1][++tsn]=some[d][j];
        REP(j,1,none_n)
            if(mapp[v][none[d][j]])
                none[d+1][++tnn]=none[d][j];
        bk_dfs(d+1,all_n+1,tsn,tnn);
        some[d][i] = 0;
        none[d][++none_n] = v;
    }
}

void BronKerbosch()
{
    ans = 0;
    REP(i,1,N)  some[0][i] = i;
    bk_dfs(0,0,N,0);
}

int main()
{
    //freopen("test.in","r",stdin);
    //freopen("test.out","w+",stdin);
    while(scanf("%d%d",&N,&M)!=EOF)
    {
        memset(mapp,0,sizeof(mapp));

        int u,v;
        REP(i,1,M)
        {
            scanf("%d%d",&u,&v);
            mapp[u][v] = mapp[v][u] = 1;
        }
        BronKerbosch();

        if(ans>1000)    printf("Too many maximal sets of friends.\n");
        else    printf("%d\n",ans);
    }
    return 0;
}
