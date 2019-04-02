

// MLES theory
ll extend_gcd(ll a, ll b, ll& x, ll& y)
{
    if(a==0&&b==0)  return -1;
    if(b==0)    {x=1;y=0;return a;}
    ll d = extend_gcd(b,a%b,y,x);
    y -= a/b*x;
    return d;
}

ll m[MAXN], a[MAXN];
int N;

bool solve(ll& m0, ll& a0, ll m, ll a)
{
    ll y, x;
    ll g = extend_gcd(m0,m,x,y);
    ll res = a>a0?a-a0:a0-a;
    if(res%g) return 0;
    x *= (a-a0)/g;
    x %= m/g;
    a0 = (x*m0+a0);
    m0 *= m/g;
    a0 %= m0;
    if( a0 < 0 )a0 += m0;

    return 1;
}

bool MLES(ll& m0, ll& a0)
{
    bool flag = 1;
    m0 = 1;
    a0 = 0;
    for(int i=1;i<=N;++i)
        if(!solve(m0,a0,m[i],a[i]))
        {
            flag = 0;
            break;
        }
    return flag;
}

int main()
{
    //freopen("input","r",stdin);
    //freopen("output","w+",stdout);
    while(scanf("%d",&N)!=EOF)
    {
        for(int i=1;i<=N;++i)   scanf("%lld%lld",m+i,a+i);
        ll m, a;
        if(MLES(m,a))   printf("%lld\n",(m+a%m)%m);
        else    printf("-1\n");
    }
    return 0;
}


// matrix quick power
const int demension = 3;

struct Matrix
{
    ll a[demension][demension];
    void init()
    {
        memset(a, 0, sizeof(a));
        for(int i=0;i<demension;++i)
            a[i][i] = 1LL;
    }
    void change()
    {
        ll gg0[demension] = {0LL,1LL,0LL};    memcpy(a[0],gg0,sizeof(ll)*demension);
        ll gg1[demension] = {0LL,0LL,1LL};    memcpy(a[1],gg1,sizeof(ll)*demension);
        ll gg2[demension] = {-12LL,17LL,4LL};    memcpy(a[2],gg2,sizeof(ll)*demension);
    }
    void print()
    {
        for(int i=0;i<demension;++i)
        {
            for(int j=0;j<demension;++j)
                cout<<a[i][j]<<" ";
            cout<<endl;
        }
    }
};

Matrix mul(Matrix a, Matrix b)
{
    Matrix ans;
    for(int i=0; i<demension; ++i)
        for(int j=0; j<demension; ++j)
        {
            ans.a[i][j] = 0;
            for(int k=0; k<demension; ++k)
            {
                ans.a[i][j] = (ans.a[i][j]+a.a[i][k] * b.a[k][j]+MOD)%MOD;
            }
        }
    return ans;
}

Matrix qpow(Matrix a, ll n)
{
    Matrix ans;
    ans.init();
    while(n)
    {
        //ans.print();
        if(n&1LL) ans = mul(ans, a);
        a = mul(a, a);
        n >>= 1LL;
    }
    return ans;
}


// O(N) get Moblus Function
bool check[MAXN];
int prime[MAXN];
int mu[MAXN];
int sum[MAXN];

void Moblus()
{
    memset(check,0,sizeof(check));
    mu[1] = 1;
    int tot = 0;
    for(int i=2;i<MAXN;++i)
    {
        if(!check[i])
        {
            prime[++tot] = i;
            mu[i] = -1;
        }
        for(int j=1;j<=tot;++j)
        {
            if(i*prime[j]>MAXN) break;
            check[i*prime[j]] = 1;
            if(i%prime[j]==0)
            {
                mu[i*prime[j]] = 0;
                break;
            }
            else    mu[i*prime[j]] = -mu[i];
        }
    }
    sum[0] = 0;
    for(int i=1;i<MAXN;++i) sum[i] = sum[i-1]+mu[i];
}

// count the number i,j in [1,n],[1,m] with gcd(i,j) = 1
ll solve(int n, int m)
{
    ll ans = 0;
    if(n>m) swap(n,m);
    for(int i=1, j=0;i<=n;i=j+1)
    {
        j = min(n/(n/i),m/(m/i));
        ans = ans + (sum[j]-sum[i-1])*(ll)(m/i)*(ll)(n/i);
    }
    /*for(int i=1;i<=n;++i)
        ans = ans + mu[i]*(ll)(m/i)*(ll)(n/i);*/
    return ans;
}

// count the number [mu[i]=1] in [1,x]
ll cal(ll x)
{
    ll sum=0;
    ll t=sqrt(x);
    for(ll i=1;i<=t;i++)
		sum+=x/(i*i)*mu[i];
    return sum;
}


// Berlekamp Masse
int _,n;
namespace linear_seq {
    const int N=100010;
    ll res[N],base[N],_c[N],_md[N];

    vector<int> Md;
    void mul(ll *a,ll *b,int k) {
        rep(i,0,k+k) _c[i]=0;
        rep(i,0,k) if (a[i]) rep(j,0,k) _c[i+j]=(_c[i+j]+a[i]*b[j])%mod;
        for (int i=k+k-1;i>=k;i--) if (_c[i])
            rep(j,0,SZ(Md)) _c[i-k+Md[j]]=(_c[i-k+Md[j]]-_c[i]*_md[Md[j]])%mod;
        rep(i,0,k) a[i]=_c[i];
    }
    int solve(ll n,VI a,VI b) { // a ϵ�� b ��ֵ b[n+1]=a[0]*b[n]+...
//        printf("%d\n",SZ(b));
        ll ans=0,pnt=0;
        int k=SZ(a);
       // assert(SZ(a)==SZ(b));
        rep(i,0,k) _md[k-1-i]=-a[i];_md[k]=1;
        Md.clear();
        rep(i,0,k) if (_md[i]!=0) Md.push_back(i);
        rep(i,0,k) res[i]=base[i]=0;
        res[0]=1;
        while ((1ll<<pnt)<=n) pnt++;
        for (int p=pnt;p>=0;p--) {
            mul(res,res,k);
            if ((n>>p)&1) {
                for (int i=k-1;i>=0;i--) res[i+1]=res[i];res[0]=0;
                rep(j,0,SZ(Md)) res[Md[j]]=(res[Md[j]]-res[k]*_md[Md[j]])%mod;
            }
        }
        rep(i,0,k) ans=(ans+res[i]*b[i])%mod;
        if (ans<0) ans+=mod;
        return ans;
    }
    VI BM(VI s) {
        VI C(1,1),B(1,1);
        int L=0,m=1,b=1;
        rep(n,0,SZ(s)) {
            ll d=0;
            rep(i,0,L+1) d=(d+(ll)C[i]*s[n-i])%mod;
            if (d==0) ++m;
            else if (2*L<=n) {
                VI T=C;
                ll c=mod-d*powmod(b,mod-2)%mod;
                while (SZ(C)<SZ(B)+m) C.pb(0);
                rep(i,0,SZ(B)) C[i+m]=(C[i+m]+c*B[i])%mod;
                L=n+1-L; B=T; b=d; m=1;
            } else {
                ll c=mod-d*powmod(b,mod-2)%mod;
                while (SZ(C)<SZ(B)+m) C.pb(0);
                rep(i,0,SZ(B)) C[i+m]=(C[i+m]+c*B[i])%mod;
                ++m;
            }
        }
        return C;
    }
    VI temp;
    void init(VI a)
    {
        temp=BM(a);
        temp.erase(temp.begin());
        rep(i,0,SZ(temp))temp[i]=(mod-temp[i])%mod;
    }
    int gao(VI a,ll n) {
        /*
        VI c=BM(a);
        c.erase(c.begin());
        rep(i,0,SZ(c)) c[i]=(mod-c[i])%mod;
        */
        return solve(n,temp,VI(a.begin(),a.begin()+SZ(temp)));
    }
};

int main() {
    int Case=0;
    vector<int> num;
    int p[100] ={1,2,3,5};
    for(int i=0;i<4;i++)
        num.push_back(p[i]);
    linear_seq::init(num);
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        printf("%d\n",linear_seq::gao(num,n-1));
    }
    return 0;
}
