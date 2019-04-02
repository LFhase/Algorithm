

// DFS O(NM)
// get the lex minimal answer
int head[MAXN];
int curedgeno;

struct Edge{
    int u, v;
    int next;
    Edge(int u=0, int v=0, int next=-1): u(u), v(v), next(next) {}
}edge[MAXN<<3];

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

bool vis[MAXN];
int S[MAXN], top;

bool dfs(int u)
{
    if(vis[u^1])    return 0;
    if(vis[u])  return 1;
    vis[u] = 1;
    S[top++] = u;
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        if(!dfs(edge[i].v)) return 0;
    }
    return 1;
}

bool two_sat(int N)
{
    memset(vis,0,sizeof(vis));
    for(int i=0;i<N;i+=2)
    {
        if(vis[i]||vis[i^1])    continue;
        top = 0;
        if(!dfs(i))
        {
            while(top)  vis[S[--top]] = 0;
            if(!dfs(i^1))   return 0;
        }
    }
    return 1;
}

int main()
{
    //freopen("SPO.in","r",stdin);
    //freopen("SPO.out","w+",stdout);
    int N, M;
    while(scanf("%d%d",&N,&M)!=EOF)
    {
        init();
        int u, v;
        for(int i=1;i<=M;++i)
        {
            scanf("%d%d",&u,&v);
            u--, v--;
            add_edge(u,v^1);
            add_edge(v,u^1);
        }
        if(two_sat(N<<1))
        {
            for(int i=0;i<(N<<1);++i)
                if(vis[i])
                    printf("%d\n",i+1);
        }
        else    printf("NIE\n");
    }
    return 0;
}


// 2-SAT  Tarjan
// AC automation bless me~
int head[MAXN];
int curedgeno;

struct Edge{
    int u, v;
    int next;
    Edge(int u=0, int v=0, int next=-1): u(u), v(v), next(next) {}
}edge[1000005];

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


int low[MAXN], dfn[MAXN], mk[MAXN];
int sccno[MAXN], num[MAXN];

int curdepth;
int scc_cnt;
stack<int> togo;

void tarjanfs(int u, int fa)
{
    low[u] = dfn[u] = ++curdepth;
    togo.push(u);
    mk[u] = 1;
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        int v = edge[i].v;

        if(!dfn[v])
        {
            tarjanfs(v,u);
            low[u] = min(low[u], low[v]);
        }
        else if(mk[v])
        {
            low[u] = min(low[u],dfn[v]);
        }
    }

    if(dfn[u]==low[u])
    {
        scc_cnt++;
        int tmp;
        do
        {
            tmp = togo.top();
            sccno[tmp] = scc_cnt;
            togo.pop();
            mk[tmp] = 0;
            num[scc_cnt]++;
        }while(tmp!=u);
    }
}

int tarjan(int N)
{
    memset(low,0,sizeof(low));
    memset(dfn,0,sizeof(dfn));
    memset(sccno,0,sizeof(sccno));
    memset(num,0,sizeof(num));
    scc_cnt = curdepth = 0;
    while(!togo.empty())    togo.pop();
    for(int i=0;i<N;++i)
    {
        if(!dfn[i]) tarjanfs(i, -1);
    }
    for(int i=0;i<N;i+=2)
        if(sccno[i]==sccno[i^1])    return 0;
    return 1;
}

queue<int> q1;
vector<vector<int> > dag;
char color[MAXN];
int indeg[MAXN];
int cf[MAXN];

void solve(int N)
{
    dag.assign(scc_cnt+1,vector<int>());
    memset(indeg,0,sizeof(indeg));
    memset(color,0,sizeof(color));
    for(int u=0;u<N;++u)
        for(int i=head[u];i!=-1;i=edge[i].next)
        {
            int v = edge[i].v;
            if(sccno[u]!=sccno[v])
            {
                dag[sccno[v]].pb(sccno[u]);
                indeg[sccno[u]]++;
            }
        }
    for(int i=0;i<N;i+=2)
    {
        cf[sccno[i]] = sccno[i^1];
        cf[sccno[i^1]] = sccno[i];
    }
    while(!q1.empty())  q1.pop();
    for(int i=1;i<=scc_cnt;++i)
        if(indeg[i]==0) q1.push(i);
    while(!q1.empty())
    {
        int u = q1.front();
        q1.pop();
        if(color[u]==0)
        {
            color[u] = 'R';
            color[cf[u]] = 'B';
        }
        int sz = dag[u].size();
        for(int i=0;i<sz;++i)
        {
            indeg[dag[u][i]]--;
            if(indeg[dag[u][i]]==0) q1.push(dag[u][i]);
        }
    }
}

int change(char s[])
{
    int ret = 0;
    int i = 0;
    while(s[i]>='0'&&s[i]<='9')
    {
        ret *= 10;
        ret += s[i]-'0';
        ++i;
    }
    if(s[i]=='w')   return 2*ret;
    else    return 2*ret+1;
}

int main()
{
    //freopen("test.in","r",stdin);
    //freopen("test.out","w+",stdout);
    int N, M;
    char s1[10], s2[10];
    while(scanf("%d%d",&N,&M)!=EOF)
    {
        if(N==0&&M==0)  break;
        init();
        int u, v;
        for(int i=1;i<=M;++i)
        {
            scanf(" %s %s",s1,s2);
            u = change(s1);
            v = change(s2);
            add_edge(u^1,v);
            add_edge(v^1,u);

        }
        add_edge(1,0);
        if(tarjan(N*2))
        {
            solve(N*2);
            for(int i=1;i<N;++i)
            {
                if(color[sccno[2*i]]=='R')  printf("%dw",i);
                else    printf("%dh",i);
                if(i<N-1)   printf(" ");
                else    printf("\n");
            }
        }
        else    printf("bad luck\n");
    }
    return 0;
}
