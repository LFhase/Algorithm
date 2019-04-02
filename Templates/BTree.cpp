// theme: Balanced Tree
// date: 2018-8-8
// ..


// Basic Functions and Definies
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

using namespace std;

#define FSIO  ios::sync_with_stdio(0);cin.tie(0);
#define DEBUG(a)   cout<<"DEBUG: "<<(a)<<endl;
#define ll long long
#define EPS 1e-6
#define pb push_back
#define mp make_pair

const int MAXN = 100005;
const int MOD = 1e9+7;
const int INF = 1e9+7;
ll powmod(ll a,ll b) {ll res=1;a%=MOD;  for(;b;b>>=1){if(b&1)res=res*a%MOD;a=a*a%MOD;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}




// Treap
struct data{
	int l,r;		// to show the location of its children in tr array
	int v;			// the value stored in the node
	int size,rnd,w;	// the size of the sub tree, treap random num, repeat times
}tr[100005];

int size,root,ans;		//total size, root location, answer when querying pro and sub-node
void update(int k)		
{
	tr[k].size=tr[tr[k].l].size+tr[tr[k].r].size+tr[k].w;
}
void rturn(int &k)
{
	int t=tr[k].l;tr[k].l=tr[t].r;tr[t].r=k;
	tr[t].size=tr[k].size;update(k);k=t;
}
void lturn(int &k)
{
	int t=tr[k].r;tr[k].r=tr[t].l;tr[t].l=k;
	tr[t].size=tr[k].size;update(k);k=t;
}
void insert(int &k,int x)
{
	if(k==0)
	{
		size++;k=size;
		tr[k].size=tr[k].w=1;tr[k].v=x;tr[k].rnd=rand();
		return;
	}
	tr[k].size++;
    if(tr[k].v==x)tr[k].w++;	//record the reapted times of value x in the treap
	else if(x>tr[k].v)
	{
		insert(tr[k].r,x);
		if(tr[tr[k].r].rnd<tr[k].rnd)lturn(k); // heap 
	}
	else 
	{
		insert(tr[k].l,x);
		if(tr[tr[k].l].rnd<tr[k].rnd)rturn(k);
	} 
}
void del(int &k,int x)
{
    if(k==0)return; 
	if(tr[k].v==x)
	{
		if(tr[k].w>1)
		{
			tr[k].w--;tr[k].size--;return;	// minus 1 reapted times if >= 2
		}
		if(tr[k].l*tr[k].r==0)k=tr[k].l+tr[k].r;	// one null child
		else if(tr[tr[k].l].rnd<tr[tr[k].r].rnd)
			rturn(k),del(k,x);
		else lturn(k),del(k,x);
	}
	else if(x>tr[k].v)
		tr[k].size--,del(tr[k].r,x);
	else tr[k].size--,del(tr[k].l,x);
}
int query_rank(int k,int x)
{
    if(k==0)return 0;
	if(tr[k].v==x)return tr[tr[k].l].size+1;
	else if(x>tr[k].v)
		return tr[tr[k].l].size+tr[k].w+query_rank(tr[k].r,x);
	else return query_rank(tr[k].l,x);
}
int query_num(int k,int x)
{
    if(k==0)return 0;
	if(x<=tr[tr[k].l].size)
		return query_num(tr[k].l,x);
    else if(x>tr[tr[k].l].size+tr[k].w)
		return query_num(tr[k].r,x-tr[tr[k].l].size-tr[k].w);
    else return tr[k].v;
}
void query_pro(int k,int x)
{
    if(k==0)return;
    if(tr[k].v<x)
	{
		ans=k;query_pro(tr[k].r,x);
	}
    else query_pro(tr[k].l,x);
}
void query_sub(int k,int x)
{
	if(k==0)return;
	if(tr[k].v>x)
	{
		ans=k;query_sub(tr[k].l,x);
	}
	else query_sub(tr[k].r,x);
}

 
// Method Cookbook BZOJ 3224 verified
int main()
{
    //freopen("input","r",stdin);
    //freopen("output","w+",stdout);
    int N;scanf("%d",&N);
    root = 0;
    while(N--)
    {
        int opt;
        int x;
        scanf("%d%d",&opt,&x);
        if(opt==1)  insert(root,x);
        else if(opt==2)  del(root,x);
        else if(opt==3)  printf("%d\n",query_rank(root,x));
        else if(opt==4)  printf("%d\n",query_num(root,x));
        else if(opt==5) { query_pro(root,x); printf("%d\n",tr[ans].v);}
        else if(opt==6) { query_sub(root,x); printf("%d\n",tr[ans].v);}
    }
    return 0;
}


// Low Efficiency Treap based on Vector STL
vector<int> a;
void insert(int x)
{
	a.insert(upper_bound(a.begin(),a.end(),x),x);
	return;
}
void del(int x)
{
	a.erase(lower_bound(a.begin(),a.end(),x));
	return;
}
int find(int x)
{
	return lower_bound(a.begin(),a.end(),x)-a.begin()+1;
}


int main()
{
    //freopen("input","r",stdin);
    //freopen("output","w+",stdout);
    int N;scanf("%d",&N);
    while(N--)
    {
        int opt;
        int x;
        scanf("%d%d",&opt,&x);
        if(opt==1)  insert(x);
        else if(opt==2)  del(x);
        else if(opt==3)  printf("%d\n",find(x));
        else if(opt==4)  printf("%d\n",a[x-1]);
        else if(opt==5)  printf("%d\n",*--lower_bound(a.begin(),a.end(),x));
        else if(opt==6)  printf("%d\n",*upper_bound(a.begin(),a.end(),x));
    }
    return 0;
}


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

using namespace std;

#define FSIO  ios::sync_with_stdio(0);cin.tie(0);
#define DEBUG(a)   cout<<"DEBUG: "<<(a)<<endl;
#define ll long long
#define EPS 1e-6
#define pb push_back
#define mp make_pair

const int MAXN = 1000005;
const int MOD = 1e9+7;
const int INF = 1e9+7;

int _;

// Splay
struct data{
	int left, right;
	int father;
	int value, size;
}tr[MAXN];

int root, size, ans;
void zig(int x)	// right rotate
{
	int p = tr[x].father;
	tr[x].father = tr[p].father;
	if(tr[p].father!=0)
	{
		if(tr[tr[p].father].left==p)
			tr[tr[p].father].left = x;
		else
			tr[tr[p].father].right = x;
	}
	else	root = x;
	tr[p].left = tr[x].right;
	tr[tr[x].right].father = p;
	tr[x].right = p;
	tr[p].father = x;
}

void zag(int x)	// left rotate
{
	int p = tr[x].father;
	tr[x].father = tr[p].father;
	if(tr[p].father!=0)
	{
		if(tr[tr[p].father].left==p)
			tr[tr[p].father].left = x;
		else
			tr[tr[p].father].right = x;
	}
	else	root = x;
	tr[p].right = tr[x].left;
	tr[tr[x].left].father = p;
	tr[x].left = p;
	tr[p].father = x;
}

void Splay(int x, int y)
{
	while(tr[x].father!=y)
	{
		int p = tr[x].father;
        if(tr[p].father==y)
        {
            if(tr[p].left == x) zig(x);
            else    zag(x);
        }
        else
        {
            int g = tr[p].father;
            if(tr[g].left==p)
            {
                if(tr[p].left==x) zig(p), zag(x);
                else        zig(x), zag(x);
            }
            else
            {
                if(tr[p].right==x) zig(p),zig(x);
                else    zag(x), zig(x);
            }
        }
	}
}

void insert(int x)
{
	if(!root)
	{
		root=++size;
		tr[size].value = x;
		tr[size].size = 1;
		return;
	}
	int p = root;
	int z;
	while(p)
	{
		z = p;
		++tr[p].size;
		if(x<tr[p].value) p = tr[p].left;
		else	p = tr[p].right;
	}
	if(tr[z].value>x)	tr[z].left=++size;
	else	tr[z].right=++size;

	tr[size].value = x;
	tr[size].size = 1;
	tr[size].father = z;
	Splay(size,0);
}

int find(int k, int x)	// find the location of the node with value x
{
	if(k==0)	return -1;
	if(tr[k].value == x)	return k;
	else if(tr[k].value>x)	return find(tr[k].left,x);
	else	return find(tr[k].right,x);
}

int query_num(int k,int x)
{
    if(k==0)return 0;
	if(x<=tr[tr[k].left].size)
		return query_num(tr[k].left,x);
    else if(x>tr[tr[k].left].size)
		return query_num(tr[k].right,x-tr[tr[k].left].size);
    else return tr[k].value;
}


int query_rank(int k,int x)
{
    if(k==0)return 0;
	if(tr[k].value==x)return tr[tr[k].left].size+1;
	else if(x>tr[k].value)
		return tr[tr[k].left].size+query_rank(tr[k].right,x);
	else return query_rank(tr[k].left,x);
}

void query_pro(int k,int x)
{
    if(k==0)return;
    if(tr[k].value<x)
	{
		ans=k;
		query_pro(tr[k].right,x);
	}
    else query_pro(tr[k].left,x);
}

void query_sub(int k,int x)
{
	if(k==0)return;
	if(tr[k].value>x)
	{
		ans=k;
		query_sub(tr[k].left,x);
	}
	else query_sub(tr[k].right,x);
}

void del(int x)
{
    int pos = find(root,x);
	if(pos==-1)	return;
	query_pro(root,x);
	int prev = ans;
	query_sub(root,x);
	int next = ans;
	Splay(prev,root);
	Splay(next,prev);
	tr[next].left = 0;
}

void intervalDel(int l, int r)
{
	insert(l);
	insert(r);
	query_pro(root,l);
	int prev = ans;
	query_sub(root,r);
	int next = ans;
	Splay(prev,root);
	Splay(next,prev);
	tr[next].left = 0;
}

int main()
{
    //freopen("input","r",stdin);
    //freopen("output","w+",stdout);
    int N;  scanf("%d",&N);
    while(N--)
    {
        char opt;
        int x, y;
        cin>>opt>>x;
        if(opt=='I')    insert(x);
        else if(opt=='Q')
        {
            query_pro(root,x);
            printf("%d\n",ans);
        }
        else if(opt=='D')
        {
            cin>>y;
            intervalDel(x,y);
        }
    }

    return 0;
}
/*
6
I 1
I 2
I 3
Q 4
D 2 2
Q 2
*/
