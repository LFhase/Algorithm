
// floyd algorithm

int mapp[MAXN][MAXN];
int dis[MAXN][MAXN];
int N;

void floyd()
{
    for(int i=1;i<=N;++i)
        for(int j=1;j<=N;++j)
            if(mapp[i][j])  dis[i][j]=mapp[i][j];
            else    dis[i][j] = INF;
    int i,j,k;
    for (k=1; k<=N; k++)
        for(i=1; i<=N; i++)
            for (j=1; j<=N; j++)
                dis[i][j]=min( dis[i][j],dis[i][k]+dis[k][j] );

}



// dj linked-table

vector<pair<int,int> > mapp[MAXN];
int dis[MAXN];
int N;

struct node{
    int id;
    int dis;
    node(int a=0,int b=0):id(a),dis(b) {}
};


bool operator< (const node& a, const node& b)
{
    if(a.dis == b.dis)  return a.id<b.id;
    else        return a.dis > b.dis;
}
priority_queue<node> whyareyousostrong;

void dijkstra(int s)
{
    for(int i=1;i<=N;++i)    dis[i] = INF;
    node temp;
    temp.id = s;
    temp.dis = 0;
    dis[s] =  0;
    whyareyousostrong.push(temp);
    while(!whyareyousostrong.empty())
    {
        temp = whyareyousostrong.top(); whyareyousostrong.pop();
        if(dis[temp.id]<temp.dis)  continue;
        for(int i=0;i<mapp[temp.id].size();++i)
        {
            pair<int,int>  v = mapp[temp.id][i];
            if(dis[temp.id]+v.second<dis[v.first]||dis[v.first]==INF)
            {
                dis[v.first] = dis[temp.id]+v.second;
                whyareyousostrong.push(node(v.first,dis[v.first]));
            }
        }
    }
}


// dj-linked-matrix


int mapp[MAXN][MAXN];
int dis[MAXN];
int visit[MAXN];
int N;

void dijkstra(int s)
{
    int i,j;
    int u;
    int minn;
    for (i=1; i<=N; i++)
    {
        visit[i]=0;
        dis[i] = mapp[s][i];
    }
    visit[s] = 1;
    for (i=1; i<=N; i++)
    {
        minn=INF;
        u = -1;
        for (j=1; j<=N; j++)
        {
            if (visit[j]==0&&dis[j]<minn)
            {
                u = j;
                minn = dis[j];
            }
        }
        if (u==-1)	break;
        visit[u] = 1;
        for (j=1; j<=N; j++)
        {
			if(visit[j]==0&&dis[u]+mapp[u][j]<dis[j])	
				dis[j] = dis[u]+mapp[u][j];
            
        }
    }
}


// linked* dijkstra
int dis[MAXN];
int head[MAXN];
int curedgeno;
int N, M;

struct Edge{
    int u, v, w;
    int next;
    Edge(int u=0, int v=0, int w=0, int next=-1): u(u), v(v), w(w), next(next) {}
}edge[MAXN];

void init()
{
    memset(head,-1,sizeof(head));
    curedgeno = 0;
}

void add_edge(int u, int v, int w)
{
    ++curedgeno;
    edge[curedgeno] = Edge(u,v,w);
    edge[curedgeno].next = head[u];
    head[u] = curedgeno;
}

struct node{
    int id;
    int dis;
    node(int a=0,int b=0):id(a),dis(b) {}
};


bool operator< (const node& a, const node& b)
{
    if(a.dis == b.dis)  return a.id<b.id;
    else        return a.dis > b.dis;
}
priority_queue<node> whyareyousostrong;

void dijkstra(int s)
{
    for(int i=1;i<=N;++i)    dis[i] = INF;
    node temp;
    temp.id = s;
    temp.dis = 0;
    dis[s] =  0;
    whyareyousostrong.push(temp);
    while(!whyareyousostrong.empty())
    {
        temp = whyareyousostrong.top(); whyareyousostrong.pop();
        if(dis[temp.id]<temp.dis)  continue;
        for(int i=head[temp.id];i!=-1;i=edge[i].next)
        {
            Edge& v = edge[i];
            if(dis[temp.id]+v.w<dis[v.v]||dis[v.v]==INF)
            {
                dis[v.v] = dis[temp.id]+v.w;
                whyareyousostrong.push(node(v.v,dis[v.v]));
            }
        }
    }
}



int main()
{
    //freopen("input","r",stdin);
    //freopen("output","w+",stdout);
    int M;
    while(scanf("%d%d",&N,&M)!=EOF)
    {
        init();
        int u, v, w;
        for(int i=1;i<=M;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            add_edge(u,v,w);
        }
        dijkstra(1);
        printf("%d\n",dis[N]);
    }
    return 0;
}


// bellmanford 
struct e{
    int u, v;
    int len;
};
e edge[MAXN];
 
int BellmanFord(int N, int E)
{
    int D[MAXN];
    for(int i=2; i<=N; ++i)  D[i]=1<<20;
    D[1] = 0;
 
    for(int i=1; i<=N-1; ++i)
        for(int j=1; j<=E; ++j)
            if(D[edge[j].v]>D[edge[j].u]+edge[j].len)
                D[edge[j].v] = D[edge[j].u]+edge[j].len;
 
    int flag = 1;       //负环判断
    for(int j=1; j<=E; ++j)
        if(D[edge[j].v]>D[edge[j].u]+edge[j].len)
        {
            flag = 0;
            break;
        }
 
    if(flag)    return D[N];
    else return -1;
}



// spfa-linked-matrix

int mapp[MAXN][MAXN];
int dis[MAXN];
int visit[MAXN];
int N;
void spfa(int s)
{
    int i,now;
    for( i=1;i<=N;i++ )
    {
        dis[i]=INF;
        visit[i] = 0;
    }
    dis[s] = 0;
    queue<int>q;
    q.push(s);
    visit[s] = 1;
    while (!q.empty())
    {
        now = q.front();
        q.pop();
        visit[now] = 0;
		int flag = 1;
        for( i=1;i<=N;i++)
        {
            if (dis[i]>dis[now]+mapp[now][i])
            {
				flag = 0;
                dis[i] = dis[now]+mapp[now][i];
                if (visit[i] == 0)
                {
                    q.push(i);
                    visit[i] = 1;
					
                }
            }
        }
    }

}


// SPFA && SLF
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <stack>
#include <bitset>

using namespace std;

#define FSIO  ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define DEBUG(a)   cout<<"DEBUG: "<<(a)<<endl;
#define ll long long
#define EPS 1e-6
#define pb push_back

const int MAXN = 100005;
const int MOD = 1e9+7;
const int INF = 1e9+7;

int _;

using namespace std;

struct e
{
    int u, v;
    int len;
    e(int a=0, int b=0, int c=0): u(a), v(b), len(c) {}
};
e edge[400005];
vector<int> mapp[MAXN];
int dis[MAXN];
bool visit[MAXN];
int incnt[MAXN];
int N;
deque<int> q;

ll spfa(int start)
{
    memset(visit,0,sizeof(visit));
    memset(dis,0,sizeof(dis));
    memset(incnt,0,sizeof(incnt));

    q.push_front(start);
    visit[start] = 1;
    int flag = 1;
    int now, i, len;
    while (!q.empty())
    {
        now = q.front();
        q.pop_front();
        visit[now] = 0;
        len = mapp[now].size();
        for(i=0; i<len; ++i)
        {
            e tmp = edge[mapp[now][i]];
            if (dis[tmp.v]>dis[now]+tmp.len)
            {
                dis[tmp.v] = dis[now]+tmp.len;
                if (!visit[tmp.v])
                {
                    incnt[tmp.v]++;
                    if(incnt[tmp.v]>N)
                    {
                        flag = 0;
                        break;
                    }
                    // SLF
                    if(!q.empty()&&dis[tmp.v]>dis[q.front()])   q.push_back(tmp.v);
                    else    q.push_front(tmp.v);
                    //q.push(tmp.v);
                    visit[tmp.v] = 1;
                }
            }
        }
        if(!flag)   break;
    }

    if(flag)
    {
        ll res = 0LL;
        for(i=2; i<=N; ++i)
        {
            res += (ll)dis[i];
            //cout<<dis[i]<<" ";
        }
        //cout<<endl;
        return -1LL*res;
    }
    else return -1LL;
}
void read(int &x)
{
    char ch = getchar();
    x = 0;
    for (; ch < '0' || ch > '9'; ch = getchar());
    for (; ch >='0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
}
int main()
{
    //freopen("input","r",stdin);
    //freopen("output","w+",stdout);
    int  M;
    read(N);
    read(M);

    int opt, u, v;
    int cur = 0;
    for(int i=1; i<=M; ++i)
    {
        read(opt);
        read(u);
        read(v);
        u++, v++;
        if(opt==1)
        {
            edge[++cur]=e(u,v,0);
            mapp[u].pb(cur);
            edge[++cur]=e(v,u,0);
            mapp[v].pb(cur);
        }
        else if(opt==2)
        {
            edge[++cur]=e(u,v,-1);
            mapp[u].pb(cur);
        }
        else if(opt==3)
        {
            edge[++cur]=e(v,u,0);
            mapp[v].pb(cur);
        }
        else if(opt==4)
        {
            edge[++cur]=e(v,u,-1);
            mapp[v].pb(cur);
        }
        else
        {
            edge[++cur]=e(u,v,0);
            mapp[u].pb(cur);
        }
    }
    N++;

    for(int i=2;i<=N;++i)
    {
        edge[++cur] = e(1,i,-1);
        mapp[1].pb(cur);
    }
    ll rt = spfa(1);
    printf("%lld\n",rt);

    return 0;
}




// prim linked-matrix

int mapp[MAXN][MAXN];
int low_cost[MAXN];
int pre[MAXN];
int N, M;


// -1 to show no answer
int prim()
{
    int i, j, k;
    int sum = 0;
    int minn;
    for(i = 2; i <= N; ++ i)
    {
        low_cost[i] = mapp[1][i];
        pre[i] = 0;
    }
    for(i = 2; i <=N; ++ i)
    {
        minn = INF;
        k = -1;
        for(j = 2; j <=N; ++ j)
        {
            if(low_cost[j]&&low_cost[j] < minn)
            {
                k = j;
                minn = low_cost[j];
            }
        }
        if(k==-1)   return -1;
        sum += low_cost[k];
        low_cost[k] = 0;
        for(j = 2; j <=N; ++ j)
        {
            if(mapp[k][j] < low_cost[j] && low_cost[j])
            {
                low_cost[j] = mapp[k][j];
                pre[j] = k;
            }
        }
    }
    return sum;
}



// kruskal linked-matrix
// -1 to show no answer
int father[100005];
int N, M;

void init( )
{
    int i;
    for(i=1;i<=N;i++)
        father[i]=i;
}

int find(int x)
{
    while(father[x]!=x)
        x=father[x];
    return x;
}

void merge(int a,int b)
{
    int temp_a,temp_b;
    temp_a=find(a);
    temp_b=find(b);
    if(temp_a<temp_b)   swap(temp_a,temp_b);
    if(temp_a!=temp_b)
        father[temp_a]=temp_b;
}

struct edge
{
    int u,v;
    int cost;
    edge(int a=0,int b=0,int c=0):u(a), v(b), cost(c) {}
}edges[500005];

bool operator<(const edge& a, const edge& b)
{
    return a.cost < b.cost;
}

int kruskal()
{
    sort(edges+1,edges+1+M);
    init();
    int res = 0;
    edge temp;
    int cnt = 0;
    for(int i=1;i<=M;++i)
    {
        temp = edges[i];
        if(find(temp.u)!=find(temp.v))
        {
            merge(temp.u,temp.v);
            res += temp.cost;
            cnt++;
        }
    }
    if(cnt<N-1) return -1;
    return res;
}





// K-th Shortest Path
const int MAXN = 1005;
const int MOD = 1e9+7 ;
const int INF = 1e9+7;

int _;

using namespace std;

int head[MAXN];
int curedgeno;

struct Edge
{
    int u, v;
    int w;
    int next;
    Edge(int u=0, int v=0, int next=-1): u(u), v(v), next(next) {}
} edge[100010<<2];

int rhead[MAXN];

void init()
{
    memset(head,-1,sizeof(head));
    memset(rhead,-1,sizeof(rhead));
    curedgeno = 0;
}

void add_edge(int u, int v, int w, int* head)
{
    ++curedgeno;
    edge[curedgeno] = Edge(u,v);
    edge[curedgeno].w = w;
    edge[curedgeno].next = head[u];
    head[u] = curedgeno;
}

int dis[MAXN];
bool visit[MAXN];
deque<int> q;

void spfa(int start)
{
    memset(visit,0,sizeof(visit));

    q.push_front(start);
    dis[start] = 0;
    visit[start] = 1;
    int now, i;
    while (!q.empty())
    {
        now = q.front();
        q.pop_front();
        visit[now] = 0;
        for(i=rhead[now]; i!=-1; i=edge[i].next)
        {
            Edge& tmp = edge[i];
            if (dis[tmp.v]>dis[now]+tmp.w)
            {
                dis[tmp.v] = dis[now]+tmp.w;
                if (!visit[tmp.v])
                {
                    // SLF
                    if(!q.empty()&&dis[tmp.v]>dis[q.front()])   q.push_back(tmp.v);
                    else    q.push_front(tmp.v);
                    //q.push(tmp.v);
                    visit[tmp.v] = 1;
                }
            }
        }
    }
}

struct node
{
    int f, g, v;
    node() {}
    node(int a, int b, int c) : f(a), g(b), v(c) {}

    bool operator < (const node& x) const
    {
        return x.f < f;
    }
};

int inq[MAXN];

int k_shortest(int st, int ed, int k)
{
    priority_queue<node> Q;
    if(dis[st] == INF)  return -1;
    int v, w;
    memset(inq,0,sizeof(inq));
    Q.push(node(dis[st], 0, st));

    while(!Q.empty())
    {
        node cur = Q.top();
        Q.pop();
        inq[cur.v] ++;
        if(inq[ed] == k)    return cur.f;
        if(inq[cur.v] > k)  continue;

        for(int i = head[cur.v]; i != -1; i = edge[i].next)
        {
            v = edge[i].v;
            w = edge[i].w;
            node New(dis[v] + cur.g + w, cur.g + w, v);
            Q.push(New);
        }
    }

    return -1;
}

int main()
{
    //freopen("test.in","r",stdin);
    //freopen("test.in","w+",stdout);
    int N, M;
    while(scanf("%d%d",&N,&M)!=EOF)
    {
        init();
        int u, v, w;
        int s, t, k, li;
        scanf("%d%d%d%d",&s,&t,&k,&li);
        REP(i,1,M)
        {
            scanf("%d%d%d",&u,&v,&w);
            add_edge(u,v,w,head);
            add_edge(v,u,w,rhead);
        }
        REP(i,1,N)  dis[i] = INF;
        spfa(t);
        if(s==t)    k++;
        int rt = k_shortest(s,t,k);
        if(rt!=-1&&rt<=li)	printf("yareyaredawa\n");
        else		printf("Whitesnake!\n");
    }
    return 0;
}
