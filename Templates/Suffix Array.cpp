
// Suffix Array O(NlogN)
// AC Automaton ~
int t1[MAXN], t2[MAXN], c[MAXN];
bool cmp(int* r, int a, int b, int l)
{
    return r[a] == r[b] && r[a+l]==r[b+l];
}

int str[MAXN];
int sa[MAXN];
int rk[MAXN];
int height[MAXN];


void DA(int N, int M)
{
    N++;
    int i, j, p;
    int* x = t1;
    int* y = t2;
    for(i=0;i<M;++i)    c[i] = 0;
    for(i=0;i<N;++i)    c[x[i]=str[i]]++;
    for(i=1;i<M;++i)    c[i] += c[i-1];
    for(i=N-1;i>=0;--i) sa[--c[x[i]]] = i;
    for(j=1;j<=N;j<<=1)
    {
        p = 0;
        for(i=N-j;i<N;++i)  y[p++] = i;
        for(i=0;i<N;++i)
            if(sa[i]>=j)
                y[p++] = sa[i] - j;
        for(i=0;i<M;++i)    c[i] = 0;
        for(i=0;i<N;++i)    c[x[y[i]]]++;
        for(i=1;i<M;++i)    c[i] += c[i-1];
        for(i=N-1;i>=0;--i) sa[--c[x[y[i]]]] = y[i];
        swap(x,y);
        p = 1;
        x[sa[0]] = 0;
        for(i=1;i<N;++i)    x[sa[i]] = cmp(y,sa[i-1],sa[i],j)?p-1:p++;
        if(p>=N)    break;
        M = p;
    }
    int k = 0;
    N--;
    for(i=0;i<=N;++i)   rk[sa[i]] = i;
    for(i=0;i<N;++i)
    {
        if(k)   k--;
        j = sa[rk[i]-1];
        while(str[i+k]==str[j+k])   k++;
        height[rk[i]] = k;
    }
}

int RMQ[MAXN];
int mm[MAXN];
int best[20][MAXN];

void initRMQ(int N)
{
    mm[0] = -1;
    for(int i=1;i<=N;++i)
    {
        mm[i] = ((i&(i-1))==0)?mm[i-1]+1:mm[i-1];
        best[0][i] = i;
    }
    for(int j=1;j<=mm[N];++j)
        for(int i=1;i+(1<<j)-1<=N;++i)
        {
            int a = best[i-1][j];
            int b = best[i-1][j+(1<<(i-1))];
            if(RMQ[a]<RMQ[b])   best[i][j]=a;
            else    best[i][j]=b;
        }
}

int askRMQ(int a, int b)
{
    int t;
    t = mm[b-a+1];
    b -= (1<<t)-1;
    a = best[t][a];
    b = best[t][b];
    return RMQ[a]<RMQ[b]?a:b;
}

int lcp(int a, int b)
{
    a = rk[a];
    b = rk[b];
    if(a>b) swap(a,b);
    return height[askRMQ(a+1,b)];
}

char sss[MAXN];


int main()
{
    //freopen("input","r",stdin);
    //freopen("output","w+",stdout);
    while(scanf(" %s",sss)!=EOF)
    {
        int len = strlen(sss);
        int N = len<<1|1;
        for(int i=0;i<len;++i)
        {
            str[i] = sss[i];
            str[len+i] = sss[i];
        }
        str[N] = 0;
        DA(N,128);
        for(int i=1;i<=N;++i)
        {
            //cout<<sa[i]<<endl;
            //printf("%s\n",sss+sa[i]);
            if(sa[i]>=len)  continue;
            int pos = sa[i];
            if(pos==0)  pos = len-1;
            else    pos--;
            printf("%c",sss[pos]);
        }
        printf("\n");

    }
    return 0;
}


// Suffix Automaton

// AC Automaton ~

const int MAXN = 1000005;
const int MOD = 1e9+7;
const int INF = 1e9+7;

int _;

using namespace std;

queue<int> togo;
int deg[MAXN<<1];

const int CHAR = 26;

struct SAM_Node
{
    SAM_Node *fa,*next[CHAR];
    int len;
    int id,pos;
    ll endpos;
    SAM_Node() {}
    SAM_Node(int _len)
    {
        endpos=0;
        fa = 0;
        len = _len;
        memset(next,0,sizeof(next));
    }
};
SAM_Node SAM_node[MAXN*2], *SAM_root, *SAM_last;
int SAM_size;
SAM_Node *newSAM_Node(int len)
{
    SAM_node[SAM_size] = SAM_Node(len);
    SAM_node[SAM_size].id = SAM_size;
    return &SAM_node[SAM_size++];
}
SAM_Node *newSAM_Node(SAM_Node *p)
{
    SAM_node[SAM_size] = *p;
    SAM_node[SAM_size].id = SAM_size;
    SAM_node[SAM_size].endpos = 0;
    return &SAM_node[SAM_size++];
}
void SAM_init()
{
    SAM_size = 0;
    SAM_root = SAM_last = newSAM_Node(0);
    SAM_node[0].pos = 0;
}
void SAM_add(int x,int len)
{
    SAM_Node *p = SAM_last, *np = newSAM_Node(p->len+1);
    deg[np->id] = 0;
    np->endpos = 1LL;
    np->pos = len;
    SAM_last = np;
    for(; p && !p->next[x]; p = p->fa)
        p->next[x] = np;
    if(!p)
    {
        np->fa = SAM_root;
        deg[SAM_root->id]++;
        return;
    }
    SAM_Node *q = p->next[x];
    if(q->len == p->len + 1)
    {
        np->fa = q;
        deg[q->id]++;
        return;
    }
    SAM_Node *nq = newSAM_Node(q);
    nq->len = p->len + 1;
    deg[nq->id] = 2;
    q->fa = nq;
    np->fa = nq;
    for(; p && p->next[x] == q; p = p->fa)
        p->next[x] = nq;
}
void SAM_build(char *s)
{
    SAM_init();
    int len = strlen(s);
    for(int i = 0; i < len; i++)
        SAM_add(s[i] - 'a',i+1);
}


char sss[MAXN];
ll ans[MAXN];


int main()
{
    //freopen("test.in","r",stdin);
    //freopen("test.out","w+",stdout);
    while(scanf(" %s",sss)!=EOF)
    {
        SAM_build(sss);
        REP(i,1,SAM_size-1)
        if(deg[i]==0)
            togo.push(i);
        while(!togo.empty())
        {
            int top = togo.front();
            togo.pop();
            if(SAM_node[top].fa==0)   continue;
            deg[(*SAM_node[top].fa).id]--;
            (*SAM_node[top].fa).endpos += SAM_node[top].endpos;
            if(deg[(*SAM_node[top].fa).id]==0)  togo.push((*SAM_node[top].fa).id);
        }
        memset(ans,0,sizeof(ans));
        REP(i,1,SAM_size-1)
        {
            int len = SAM_node[i].len;
            ans[len] = max(ans[len],SAM_node[i].endpos);
        }
        int len = strlen(sss);
        IREP(i,len-1,1) ans[i] = max(ans[i],ans[i+1]);
        REP(i,1,len)    printf("%lld\n",ans[i]);
    }
    return 0;
}
