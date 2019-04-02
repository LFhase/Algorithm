const int MAXN = 20005;
const int MOD = 1e9+7;
const int INF = 1e9+7;

int _;

using namespace std;

vector<int> mapp[MAXN];
int dfn[MAXN];
int low[MAXN];
int mk[MAXN];
int sccno[MAXN];
stack<int> togo;
int curdepth;
int scc_cnt;
int N, M;

void dfs(int u)
{
    dfn[u] = low[u] = ++curdepth;
    togo.push(u);
    mk[u] = 1;
    for(int i=0;i<mapp[u].size();++i)
    {
        int v = mapp[u][i];
        if(!dfn[v])
        {
            dfs(v);
            low[u] = min(low[u],low[v]);
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
        }while(tmp!=u);
    }
}

void tarjan()
{
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(mk,0,sizeof(mk));
    curdepth = 0;
    scc_cnt = 0;
    memset(sccno,0,sizeof(sccno));
    while(!togo.empty())    togo.pop();
    for(int i=1;i<=N;++i)
    {
        if(!dfn[i]) dfs(i);
    }
}

int in0[MAXN], out0[MAXN];

int main()
{
    //freopen("input","r",stdin);
    //freopen("output","w+",stdout);
    while(scanf("%d%d",&N,&M)!=EOF)
    {
        for(int i=1;i<=N;++i)   mapp[i].clear();
        int u, v;
        for(int i=1;i<=M;++i)
        {
            scanf("%d%d",&u,&v);
            mapp[u].pb(v);
        }
        tarjan();
        for(int i=1;i<=scc_cnt;++i) in0[i]=out0[i]=1;
        for(int i=1;i<=N;++i)
        {
            for(int j=0;j<mapp[i].size();++j)
                if(sccno[i]!=sccno[mapp[i][j]])
                    in0[sccno[mapp[i][j]]]=out0[sccno[i]]=0;
        }
        int cntIn = 0;
        int cntOut = 0;
        for(int i=1;i<=scc_cnt;++i)
        {
            if(in0[i])  cntIn++;
            if(out0[i]) cntOut++;
        }
        int ans = max(cntIn,cntOut);
        if(scc_cnt==1)  ans = 0;
        printf("%d\n",ans);
    }
    return 0;
}


// linked edge ds

struct Edge{
    int u, v;
    int next;
    Edge(int u=0, int v=0, int next=-1): u(u), v(v), next(next) {}
}edge[MAXN<<2];


int head[MAXN], newhead[MAXN];
int curedgeno;
int N, M;
int S, T;
int artifact[MAXN<<2];


void init()
{
    memset(artifact,0,sizeof(artifact));
    memset(head,-1,sizeof(head));
    memset(newhead,-1,sizeof(newhead));
    curedgeno = 0;
}

void add_edge(int u, int v, int flag, int* head)
{
    ++curedgeno;
    int test = curedgeno;
    artifact[curedgeno] = flag;
    edge[curedgeno] = Edge(u,v);
    edge[curedgeno].next = head[u];
    head[u] = curedgeno;
}


int low[MAXN], dfn[MAXN], mk[MAXN];
int bccno[MAXN], iscut[MAXN];

int curdepth;
int bcc_cnt;
stack<int> togo;

void tarjanfs(int u, int fa)
{
    low[u] = dfn[u] = ++curdepth;
    int flag = 0;
    togo.push(u);
    mk[u] = 1;
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        int v = edge[i].v;
        if(v==fa&&!flag)
        {
            flag = 1;
            continue;
        }

        if(!dfn[v])
        {
            tarjanfs(v,u);
            low[u] = min(low[u], low[v]);
        }
        else if(mk[u])
        {
            low[u] = min(low[u],dfn[v]);
        }
    }

    if(dfn[u]==low[u])
    {
        bcc_cnt++;
        int tmp;
        do
        {
            tmp = togo.top();
            bccno[tmp] = bcc_cnt;
            togo.pop();
            mk[tmp] = 0;
        }while(tmp!=u);
    }
}

void tarjan()
{
    memset(low,0,sizeof(low));
    memset(dfn,0,sizeof(dfn));
    memset(bccno,0,sizeof(bccno));
    memset(iscut,0,sizeof(iscut));
    bcc_cnt = curdepth = 0;
    while(!togo.empty())    togo.pop();
    for(int i=1;i<=N;++i)
    {
        if(!dfn[i]) tarjanfs(i, -1);
    }
}


int main()
{
    //freopen("input","r",stdin);
    //freopen("output","w+",stdout);
    while(scanf("%d%d",&N,&M)!=EOF)
    {
        init();
        int u, v, s;
        for(int i=1;i<=M;++i)
        {
            scanf("%d%d%d",&u,&v,&s);
            add_edge(u,v,s, head);
            add_edge(v,u,s, head);
        }
        scanf("%d%d",&S,&T);
        tarjan();
        /*for(int i=1;i<=N;++i)
            cout<<bccno[i]<<" ";
        cout<<endl;*/
        memset(exdis,0,sizeof(exdis));

        for(int i=1;i<=2*M;++i)
        {
            int u = bccno[edge[i].u];
            int v = bccno[edge[i].v];
            int w = artifact[i];
            if(w&&(u==v))   exdis[u] = 1;
            if(u==v)    continue;
            add_edge(u,v,w,newhead);
        }
        spfa();
       /* for(int i=1;i<=bcc_cnt;++i)
            cout<<dis[i]<<" ";
        cout<<endl;*/
        if(dis[bccno[T]])    printf("YES\n");
        else    printf("NO\n");

    }
    return 0;
}



// 缩点 + 最长链

struct Edge{
    int u, v;
    int next;
    Edge(int u=0, int v=0, int next=-1): u(u), v(v), next(next) {}
}edge[MAXN<<2];


int head[MAXN], newhead[MAXN];
int curedgeno;
int N, M;
int S, T;


void init()
{
    memset(head,-1,sizeof(head));
    memset(newhead,-1,sizeof(newhead));
    curedgeno = 0;
}

void add_edge(int u, int v, int* head)
{
    ++curedgeno;
    edge[curedgeno] = Edge(u,v);
    edge[curedgeno].next = head[u];
    head[u] = curedgeno;
}


int low[MAXN], dfn[MAXN], mk[MAXN];
int bccno[MAXN], iscut[MAXN];

int curdepth;
int bcc_cnt;
stack<int> togo;

void tarjanfs(int u, int fa)
{
    low[u] = dfn[u] = ++curdepth;
    int flag = 0;
    togo.push(u);
    mk[u] = 1;
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        int v = edge[i].v;
        if(v==fa&&!flag)
        {
            flag = 1;
            continue;
        }

        if(!dfn[v])
        {
            tarjanfs(v,u);
            low[u] = min(low[u], low[v]);
        }
        else if(mk[u])
        {
            low[u] = min(low[u],dfn[v]);
        }
    }

    if(dfn[u]==low[u])
    {
        bcc_cnt++;
        int tmp;
        do
        {
            tmp = togo.top();
            bccno[tmp] = bcc_cnt;
            togo.pop();
            mk[tmp] = 0;
        }while(tmp!=u);
    }
}

void tarjan()
{
    memset(low,0,sizeof(low));
    memset(dfn,0,sizeof(dfn));
    memset(bccno,0,sizeof(bccno));
    memset(iscut,0,sizeof(iscut));
    bcc_cnt = curdepth = 0;
    while(!togo.empty())    togo.pop();
    for(int i=1;i<=N;++i)
    {
        if(!dfn[i]) tarjanfs(i, -1);
    }
}

int incnt[MAXN];
int vis[MAXN];
int cnt_max;

int rua(int u, int fa, int step)
{
    vis[u] = 1;
    int maxn = 0;
    int smaxn = 0;
    for(int i=newhead[u];i!=-1;i=edge[i].next)
    {
        int v = edge[i].v;
        if(!vis[v]&&fa!=v)
        {
            int rt = rua(v,u,step);
            if(rt>maxn) smaxn = maxn, maxn=rt;
            else if(rt>smaxn)   smaxn = rt;
        }
    }
    cnt_max = max(cnt_max,max(maxn+smaxn+1,step+1+maxn));
    return maxn+1;
}

int main()
{
    //freopen("input","r",stdin);
    //freopen("output","w+",stdout);
    cin>>_;
    while(_--)
    {
        init();
        scanf("%d%d",&N,&M);
        int u, v;
        for(int i=1;i<=M;++i)
        {
            scanf("%d%d",&u,&v);
            add_edge(u,v,head);
            add_edge(v,u,head);
        }
        tarjan();
        memset(incnt,0,sizeof(incnt));
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=2*M;++i)
        {
            //Edge e = edge[i];
            int u = bccno[edge[i].u];
            int v = bccno[edge[i].v];
            //cout<<u<<" "<<v<<endl;
            if(u==v)    continue;
            add_edge(u,v,newhead);
            incnt[v]++;
        }
        /*for(int i=1;i<=N;++i)
            cout<<bccno[i]<<" ";
        cout<<endl;*/
        cnt_max = 0;
        for(int i=1;i<=bcc_cnt;++i)
        {
            if(incnt[i]==1)
            {
                rua(i, -1, 0);
                break;
            }
        }
        //cout<<bcc_cnt<<endl;
        //cout<<cnt_max<<endl;
        if(bcc_cnt==1)  cnt_max = 1;
        printf("%d\n",bcc_cnt-cnt_max);
    }
    return 0;
}
