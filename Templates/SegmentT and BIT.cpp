//  2-d BIT
vector<int> data[MAXN];


void Add(int x, int y, int z) {
    for (int i = x; i <= N; i += i & -i)
        for (int j = y; j <= M; j += j & -j)
            data[i][j] += z;
}
int Sum(int x, int y) {
    int ans = 0;
    for (int i = x; i; i -= i & -i)
        for (int j = y; j; j -= j & -j)
            ans += data[i][j];
    return ans;
}


// 1-d BIT prefix sum
int tree[MAXN];
int N;

#define lowbit(x) (x&(-x))

void update(int pos, int val)
{
    while(pos <= N)
    {
        tree[pos] += val;
        pos += lowbit(pos);
    }
}

int query(int pos)
{
    int res = 0;
    while(pos > 0)
    {
        res += tree[pos];
        pos -= lowbit(pos);
    }
    return res;
}

// 1-d BIT max value O(logN*logN)
int tree[MAXN];

#define lowbit(x) (x&(-x))

void update(int pos, int val)
{
    while(pos <= N)
    {
        tree[pos] = dp[pos];
        for(int i=1;i<lowbit(pos);i<<=1)
            tree[pos] = max(tree[pos],tree[pos-i]);
        pos += lowbit(pos);
    }
}

int query(int l, int r)
{
    int ans = 0;
    while(r>=l)
    {
        ans = max(ans,dp[r]);
        if(l==r)    break;
        for(--r;r-l>=lowbit(r);r-=lowbit(r))
            ans = max(ans,tree[r]);
    }
    return ans;
}


//  1-d BIT
// range query and range update
int N, Q;
ll sum1[MAXN];
ll sum2[MAXN];


void add(ll p, ll x)
{
    for(int i = p; i <= N; i += i & -i)
        sum1[i] += x, sum2[i] += x * p;
}
void range_add(ll l, ll r, ll x)
{
    add(l, x), add(r + 1, -x);
}
ll query(ll p)
{
    ll res = 0;
    for(int i = p; i; i -= i & -i)
        res += (p + 1) * sum1[i] - sum2[i];
    return res;
}

ll range_query(ll l, ll r)
{
    return query(r) - query(l - 1);
}



// segment tree 
// max value
int n, dat[MAXN<<2|1];

void update(int pos, int num, int l, int r, int rt)
{
    if(l==r)
    {
        dat[rt] = num;
        return;
    }
    int m = (l+r)>>1;
    if(pos<=m)  update(pos,num,l,m,rt<<1);
    else    update(pos,num,m+1,r,rt<<1|1);
    dat[rt] = max(dat[rt<<1],dat[rt<<1|1]);
}

int query(int l, int r, int ql, int qr, int rt)
{
    if(l>=ql && r<=qr)  return dat[rt];
    int m = (l+r)>>1;
    int maxn = -1;
    if(ql<=m)    maxn=max(maxn,query(l,m,ql,qr,rt<<1));
    if(qr>m)    maxn=max(maxn,query(m+1,r,ql,qr,rt<<1|1));
    return maxn;
}

void build(int l, int r, int rt)
{
    if(l==r)
    {
        scanf("%d",dat+rt);
        return;
    }
    int m = (l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    dat[rt] = max(dat[rt<<1],dat[rt<<1|1]);
}




// segment tree
// range update and query, lazy sign

ll dat[MAXN<<2];
ll mk[MAXN<<2];   // for add
ll mk_2[MAXN<<2]; // for multiply
ll mod;

void updadd( int rt, int m)
{
    if(mk_2[rt]==0&&mk[rt]==1)    return;
    mk[rt<<1] = mk[rt<<1]*mk[rt]%mod;
    mk[rt<<1|1] = mk[rt<<1|1]*mk[rt]%mod;
    dat[rt<<1]  = dat[rt<<1] *mk[rt]%mod;
    dat[rt<<1|1] = dat[rt<<1|1]*mk[rt]%mod;
    mk_2[rt<<1] = mk_2[rt<<1]*mk[rt]%mod;
    mk_2[rt<<1|1] = mk_2[rt<<1|1]*mk[rt]%mod;
    mk[rt] = 1;


    mk_2[rt<<1] = (mk_2[rt<<1]+mk_2[rt])%mod;
    mk_2[rt<<1|1] = (mk_2[rt<<1|1]+mk_2[rt])%mod;
    dat[rt<<1]  = (dat[rt<<1]+mk_2[rt]*(m-(m>>1))%mod)%mod;
    dat[rt<<1|1] = (dat[rt<<1|1]+mk_2[rt]*(m>>1)%mod)%mod;
    mk_2[rt] = 0;


}

// flag: 0 add, 1 multiply
void update(int flag,int ql, int qr,  ll num, int l, int r, int rt)
{
    if(l>=ql && qr>=r)
    {
        if(flag)    mk[rt] = mk[rt]*num%mod, mk_2[rt] = mk_2[rt]*num%mod, dat[rt] = dat[rt]*num%mod;
        else    mk_2[rt] = (mk_2[rt]+num)%mod, dat[rt] = (dat[rt]+(ll)(r-l+1)*num)%mod;
        return;
    }
    updadd( rt, r-l+1);
    int m = (l+r)>>1;
    if(ql<=m)  update(flag,ql,qr,num,l,m,rt<<1);
    if(qr>m)    update(flag,ql,qr,num, m+1,r,rt<<1|1);
    dat[rt] = (dat[rt<<1] + dat[rt<<1|1])%mod;
}

ll query(int ql, int qr, int l, int r, int rt)
{
    if(l>=ql && r<=qr)  return dat[rt];
    updadd(rt, r-l+1);
    int m = (l+r)>>1;
    ll res = 0;
    if(ql<=m)    res = (res+query(ql,qr,l,m,rt<<1))%mod;
    if(qr>m)    res = (res+query(ql,qr,m+1,r,rt<<1|1))%mod;
    return res;
}

void build(int l, int r, int rt)
{
    mk[rt]=1LL;
    mk_2[rt]=0LL;
    if(l==r)
    {
        scanf("%lld",dat+rt);
        return;
    }
    int m = (l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    dat[rt] = (dat[rt<<1]+dat[rt<<1|1])%mod;
}


void print(int l, int r, int rt)
{
    if(l==r)
    {
        printf("%d %lld\n",r,dat[rt]);
        return;
    }
    int m = (l+r)>>1;
    print(l,m,rt<<1);
    print(m+1,r,rt<<1|1);
}

int main()
{
    //freopen("input","r",stdin);
    //freopen("output","w+",stdout);
    int N;
    while(scanf("%d%lld",&N,&mod)!=EOF)
    {
        build(1,N,1);
        int Q;
        scanf("%d",&Q);
        int opt, l, r;
        ll x;
        while(Q--)
        {
            //print(1,N,1);
            scanf("%d%d%d",&opt,&l,&r);
            if(opt==1)
            {
                scanf("%lld",&x);
                update(1,l,r,x,1,N,1);
            }
            else if(opt==2)
            {
                scanf("%lld",&x);
                update(0,l,r,x,1,N,1);
            }
            else
            {
                printf("%lld\n",query(l,r,1,N,1));
            }
        }
    }
    return 0;
}


// Persisent Segment Tree [POJ2104]
int N, M;
int num[MAXN];
int hashx[MAXN];

void gomapping()
{
    for(int i=1;i<=N;++i)   hashx[i] = num[i];
    sort(hashx+1,hashx+1+N);
    M = unique(hashx+1,hashx+1+N) - hashx-1;

    /*for(int i=1;i<=N;++i)
        num[i] = lower_bound(hashx+1,hashx+1+M,num[i]) - hashx;
    */
}

int gohash(int x)
{
    return lower_bound(hashx+1,hashx+1+M,x)-hashx;
}

int T[MAXN], lson[MAXN<<5], rson[MAXN<<5], c[MAXN<<5];
int tot;

int build(int l, int r)
{
    int root = tot++;
    c[root] = 0;
    if(l!=r)
    {
        int mid=(l+r)>>1;
        lson[root] = build(l,mid);
        rson[root] = build(mid+1,r);
    }
    return root;
}

int update(int root, int pos, int val)
{
    int newroot = tot++;
    int tmp = newroot;
    c[newroot] = c[root] + val;
    int l = 1, r = M;
    while(l<r)
    {
        int mid = (l+r)>>1;
        if(pos<=mid)
        {
            lson[newroot] = tot++;
            rson[newroot] = rson[root];
            newroot = lson[newroot];
            root = lson[root];
            r = mid;
        }
        else
        {
            rson[newroot] = tot++;
            lson[newroot] = lson[root];
            newroot = rson[newroot];
            root = rson[root];
            l = mid+1;
        }
        c[newroot] = c[root] + val;
    }
    return tmp;
}

int query(int left_root, int right_root, int k)
{
    int l=1, r=M;
    while(l<r)
    {
        int mid = (l+r)>>1;
        if(c[lson[left_root]]-c[lson[right_root]]>=k)
        {
            r = mid;
            left_root = lson[left_root];
            right_root = lson[right_root];
        }
        else
        {
            l = mid + 1;
            k -= c[lson[left_root]]-c[lson[right_root]];
            left_root = rson[left_root];
            right_root = rson[right_root];
        }
    }
    return l;
}

int main()
{
    //freopen("test.in","r",stdin);
    //freopen("test.out","w+",stdin);
    int Q;
    while(scanf("%d%d",&N,&Q)!=EOF)
    {
        tot = 0;
        REP(i,1,N)  scanf("%d",num+i);
        gomapping();

        T[N+1] = build(1,M);
        IREP(i,N,1)
        T[i] = update(T[i+1],gohash(num[i]),1);

        while(Q--)
        {
            int l, r, k;
            scanf("%d%d%d",&l,&r,&k);
            printf("%d\n",hashx[query(T[l],T[r+1],k)]);
        }
    }
    return 0;
}


// May be clearer

int T[MAXN], lson[MAXN<<5], rson[MAXN<<5], cnt[MAXN<<5];
int tot;


int build(int l, int r)
{
    int root = ++tot;
    cnt[root] = 0;
    if(l!=r)
    {
        int mid=(l+r)>>1;
        lson[root] = build(l,mid);
        rson[root] = build(mid+1,r);
    }
    return root;
}

void update(int& root, int pre, int x, int val, int l, int r)
{
    root = ++tot;
    lson[root] = lson[pre];
    rson[root] = rson[pre];
    cnt[root] = cnt[pre] + val;
    if(l==r)    return;
    int mid = (l+r)>>1;
    if(x<=mid)  update(lson[root],lson[pre],x,val,l,mid);
    else    update(rson[root],rson[pre],x,val,mid+1,r);
}

int query_kth(int lrt, int rrt, int k, int l, int r)
{
    if(l==r)    return l;
    int mid = (l+r)>>1;
    int res = cnt[lson[rrt]]-cnt[lson[lrt]];
    if(res>=k)  return query_kth(lson[lrt],lson[rrt],k,l,mid);
    else    return query_kth(rson[lrt],rson[rrt],k-res,mid+1,r);
}

int query_xth(int lrt, int rrt, int x, int l, int r)
{
    if(l==r)    return 0;
    if(cnt[lrt]==cnt[rrt])  return 0;
    int mid = (l+r)>>1;
    int res = cnt[lson[rrt]]-cnt[lson[lrt]];
    if(mid>=x)  return query_xth(lson[lrt],lson[rrt],x,l,mid);
    else    return res+query_xth(rson[lrt],rson[rrt],x,mid+1,r);
}



 

// Cut the Tree
// Segment Update: Bitwise Not, Add, Multiply
// Segment Query: Sum

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

int dep[MAXN], fa[MAXN], size[MAXN];
int son[MAXN], top[MAXN];
int pos[MAXN], rpos[MAXN];  //position in seg tree
int cursz;



void find_heavy_edge(int u, int ffa, int depth)
{
    fa[u] = ffa;
    dep[u] = depth;
    size[u] = 1;
    int maxsize = 0;
    for(int i=head[u];~i;i=edge[i].next)
    {
        int v =edge[i].v;
        if(v!=ffa)
        {
            find_heavy_edge(v,u,depth+1);
            size[u] += size[v];
            if(size[v]>maxsize)
            {
                maxsize = size[v];
                son[u] = v;
            }
        }
    }
}


void connect_heavy_edge(int u, int ffa)
{
    pos[u] = ++cursz;
    rpos[cursz] = u;
    top[u] = ffa;
    if(son[u]==-1)   return;
    connect_heavy_edge(son[u],ffa);
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        int v = edge[i].v;
        if(v!=fa[u]&&son[u]!=v)
            connect_heavy_edge(v,v);
    }
}


void cut_tree(int root)
{
    memset(size,0,sizeof(size));
    memset(son,-1,sizeof(son));
    cursz = 0;
    find_heavy_edge(root,0,0);
    connect_heavy_edge(root,root);
}

int weight[MAXN];
int N, Q;
char opt[25];
ull summ[MAXN<<2];
ull mk_add[MAXN<<2];
ull mk_mul[MAXN<<2];
const ull go = (ull)18446744073709551615;

void push_up(int x)
{
    summ[x] = summ[x<<1]+summ[x<<1|1];
}

void push_down(int l, int r, int rt)
{
    if(mk_add[rt]==0&&mk_mul[rt]==1)    return;
    mk_add[rt<<1] = mk_add[rt<<1]*mk_mul[rt] + mk_add[rt];
    mk_add[rt<<1|1] = mk_add[rt<<1|1]*mk_mul[rt] + mk_add[rt];
    mk_mul[rt<<1] = mk_mul[rt]*mk_mul[rt<<1];
    mk_mul[rt<<1|1] = mk_mul[rt]*mk_mul[rt<<1|1];

    int mid = (r+l)>>1;
    summ[rt<<1] = summ[rt<<1]*mk_mul[rt] + mk_add[rt]*(ull)(mid-l+1);
    summ[rt<<1|1] = summ[rt<<1|1]*mk_mul[rt] + mk_add[rt]*(ull)(r-mid);

    mk_add[rt] = 0;
    mk_mul[rt] = 1;
}

void build(int l, int r, int rt)
{
    mk_add[rt] = 0;
    mk_mul[rt] = 1;
    if(l==r)
    {
        summ[rt] = 0;
        //cout<<rt<<" "<<weight[rpos[l]]<<endl;
        return;
    }
    int m = (l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    push_up(rt);
}

// flag: 0 add, 1 multiply, 2 bitwise not
void update(int flag,int ql, int qr,  ull num, int l, int r, int rt)
{
    if(l>=ql && qr>=r)
    {
        if(flag==1)
        {
            summ[rt] *= num;
            mk_add[rt] *= num;
            mk_mul[rt] *= num;
        }
        else if(flag==0)
        {
            summ[rt] = summ[rt] + (ull)(r-l+1)*num;
            mk_add[rt] += num;
        }
        else
        {
            summ[rt] = summ[rt]*go + (ull)go*(r-l+1);
            mk_add[rt] = mk_add[rt]*go + go;
            mk_mul[rt] *= go;
        }
        return;
    }
    push_down(l,r,rt);
    int m = (l+r)>>1;
    if(ql<=m)  update(flag,ql,qr,num,l,m,rt<<1);
    if(qr>m)    update(flag,ql,qr,num, m+1,r,rt<<1|1);
    push_up(rt);
}



ull query_sum(int ql, int qr, int l, int r, int rt)
{
    if(l>=ql&&r<=qr)    return summ[rt];
    push_down(l,r,rt);
    int mid = (l+r)>>1;
    ull res = 0;
    if(ql<=mid) res+=query_sum(ql,qr,l,mid,rt<<1);
    if(qr>mid)  res+=query_sum(ql,qr,mid+1,r,rt<<1|1);
    return res;
}

ull find_sum(int u, int v)
{
    int f1 = top[u], f2 = top[v];
    ull res = 0;
    while(f1!=f2)
    {
        if(dep[f1]<dep[f2])
        {
            swap(f1,f2);
            swap(u,v);
        }
        res += query_sum(pos[f1],pos[u],1,cursz,1);
        u = fa[f1];
        f1 = top[u];
    }
    if(dep[u]>dep[v])   swap(u,v);
    return res + query_sum(pos[u],pos[v],1,cursz,1);
}

void update_path(int u, int v, ull c, int flag)
{
    //cout<<c<<endl;
    int f1 = top[u], f2 = top[v];
    while(f1!=f2)
    {
        if(dep[f1]<dep[f2])
        {
            swap(f1,f2);
            swap(u,v);
        }
        update(flag,pos[f1],pos[u],c,1,cursz,1);
        u = fa[f1];
        f1 = top[u];
    }
    if(dep[u]>dep[v])   swap(u,v);
    update(flag,pos[u],pos[v],c,1,cursz,1);
}

void print(int l, int r, int rt)
{
    if(l==r)
    {
        printf("%d %llu\n",rpos[r],summ[rt]);
        return;
    }
    int m = (l+r)>>1;
    print(l,m,rt<<1);
    print(m+1,r,rt<<1|1);
}

int main()
{
    //freopen("test.in","r",stdin);
    //freopen("test.out","w+",stdout);
    while(scanf("%d",&N)!=EOF)
    {
        init();
        int op, u, v;
        ull x;
        REP(i,2,N)
        {
            scanf("%d",&v);
            add_edge(i,v);
            add_edge(v,i);
        }
        cut_tree(1);
        build(1,cursz,1);
        scanf("%d",&Q);
        while(Q--)
        {
            scanf("%d",&op);
            if(op==1)
            {
                scanf("%d%d%llu",&u,&v,&x);
                update_path(u,v,x,1);
            }
            else if(op==2)
            {
                scanf("%d%d%llu",&u,&v,&x);
                update_path(u,v,x,0);
            }
            else if(op==3)
            {
                scanf("%d%d",&u,&v);
                update_path(u,v,x,2);
            }
            else
            {
                scanf("%d%d",&u,&v);
                printf("%llu\n",find_sum(u,v));
            }
            //print(1,cursz,1);
        }
    }
    return 0;
}
