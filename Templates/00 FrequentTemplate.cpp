
// linked table store way
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


// DSU
struct DSU
{
    int fa[MAXN], sz[MAXN];
    int n;
    void init(int n)
    {
        this->n = n;
        for(int i=1;i<=n;i++)
        {
            fa[i]=i;
            sz[i]=1;
        }
    }
    int find(int x)
    {
        return fa[x]==x ? x : fa[x]=find(fa[x]);
    }
    void merge(int x,int y)
    {
        x=find(x),y=find(y);
        if(x!=y)
        {
            fa[x]=y;
            sz[y]+=sz[x];
        }
    }
    int count_p()
    {
        int res = 0;
        for(int i=1;i<=n;++i)
            if(find(i)==i)  res++;
        return res;
    }
    ll rua()
    {
        ll res = 0;
        for(int i=1;i<=n;++i)
            if(find(i)==i)  res+=sz[i]-1;
        return res;
    }
}dsu;


// reverse mul
ll inv[MAXN];

void inverse(int n, int p)
{
    inv[1] = 1;
    for (int i=2; i<=n; ++i)
    {
        inv[i] = (ll) (p - p / i) * inv[p%i] % p;
    }
}




// Discretization
int hashx[MAXN], hashy[MAXN];

void gomapping()
{

    for(int i=1;i<=N;++i)
    {
        hashx[i] = points[i].x;
        hashy[i] = points[i].y;
    }
    sort(hashx+1,hashx+1+N);
    sort(hashy+1,hashy+1+N);
    int cntx = unique(hashx+1,hashx+1+N) - hashx;
    int cnty = unique(hashy+1,hashy+1+N) - hashy;
    for(int i=1;i<=N;++i)
    {
        points[i].x = lower_bound(hashx+1,hashx+1+cntx,points[i].x) - hashx;
        points[i].y = lower_bound(hashy+1,hashy+1+cnty,points[i].y) - hashy;
    }
   // for(int i=1;i<=N;++i)   points[i].show();
}


ll gcd(ll a, ll b)
{
    if(a<b) swap(a,b);
    while(b)
    {
        ll tmp = a%b;
        a = b;
        b = tmp;
    }
    return a;
}


ll powermod(ll n,ll k, ll MOD)
{
    ll ans=1;
    while(k)
    {
        if(k&1)
        {
            ans=((ans%MOD)*(n%MOD))%MOD;
        }
        n=((n%MOD)*(n%MOD))%MOD;
        k>>=1;
    }
    return ans;
}
