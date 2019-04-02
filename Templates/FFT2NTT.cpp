
struct Complex
{
    double real, image;
    Complex(double _real, double _image)
    {
        real = _real;
        image = _image;
    }
    Complex(){}
};

Complex operator + (const Complex &c1, const Complex &c2)
{
    return Complex(c1.real + c2.real, c1.image + c2.image);
}

Complex operator - (const Complex &c1, const Complex &c2)
{
    return Complex(c1.real - c2.real, c1.image - c2.image);
}

Complex operator * (const Complex &c1, const Complex &c2)
{
    return Complex(c1.real*c2.real - c1.image*c2.image, c1.real*c2.image + c1.image*c2.real);
}

int rev(int id, int len)
{
    int ret = 0;
    for(int i = 0; (1 << i) < len; i++)
    {
        ret <<= 1;
        if(id & (1 << i)) ret |= 1;
    }
    return ret;
}

Complex A[MAXN];
void IterativeFFT(Complex* a, int len, int DFT)
{
    for(int i = 0; i < len; i++)
        A[rev(i, len)] = a[i];
    for(int s = 1; (1 << s) <= len; s++)
    {
        int m = (1 << s);
        Complex wm = Complex(cos(DFT*2*PI/m), sin(DFT*2*PI/m));
        for(int k = 0; k < len; k += m)
        {
            Complex w = Complex(1, 0);
            for(int j = 0; j < (m >> 1); j++)
            {
                Complex t = w*A[k + j + (m >> 1)];
                Complex u = A[k + j];
                A[k + j] = u + t;
                A[k + j + (m >> 1)] = u - t;
                w = w*wm;
            }
        }
    }
    if(DFT == -1)
        for(int i = 0; i < len; i++) A[i].real /= len, A[i].image /= len;
    for(int i=0;i<len;++i)  a[i]=A[i];
}

Complex aa[MAXN];
Complex bb[MAXN];
char buf[MAXN];
int ans[MAXN];

int main()
{
    //freopen("test.in","r+",stdin);
    //freopen("test.out","w+",stdout);
    while(scanf(" %s",buf)!=EOF)
    {
        int lena, lenb;
        int len = strlen(buf);  lena = len;
        REP(i,0,len-1)  aa[i] = Complex(buf[len-1-i]-'0',0);


        scanf(" %s",buf);
        len = strlen(buf);  lenb = len;
        REP(i,0,len-1)  bb[i] = Complex(buf[len-1-i]-'0',0);

        len = 1;
        while(len<max(lena,lenb)*2LL)
            len*=2;

        REP(i,lena,len) aa[i]=Complex(0,0);
        REP(i,lenb,len) bb[i]=Complex(0,0);

        IterativeFFT(aa,len,1);
        IterativeFFT(bb,len,1);

        REP(i,0,len-1) aa[i]=aa[i]*bb[i];
        IterativeFFT(aa,len,-1);
        memset(ans,0,sizeof(ans));
        REP(i,0,len-1)
        {
            ans[i] += (aa[i].real+0.5);
            ans[i+1] += ans[i]/10;
            ans[i]%=10;
        }

        while(len>=0&&ans[len]==0)    len--;
        if(len<0)
        {
            printf("0\n");
            continue;
        }
        IREP(i,len,0) printf("%c",ans[i] +'0');

        printf("\n");
    }
    return 0;
}



const int mod = 998244353;
const int G = 3;
ll wn[20];
ll Pow(ll a, ll n, ll mod)
{
    ll t = 1;
    for (; n; n >>= 1, a = (a * a % mod))
        if (n & 1) t = (t * a % mod);
    return t;
}
void getwn()
{   
    for (int i = 0; i < 20; i++)
        wn[i] = Pow(G, (mod - 1) / (1 << i), mod);
}
void change(ll y[], int len)
{
    for (int i = 1, j = len / 2; i < len - 1; i++)
    {
        if (i < j) swap(y[i], y[j]);
        int k = len / 2;
        while (j >= k) j -= k, k /= 2;
        if (j < k) j += k;
    }
}
void ntt(ll y[], int len, int on)
{
    change(y, len);
    for (int h = 2, id = 1; h <= len; h <<= 1, id++)
    {
        for (int j = 0; j < len; j += h)
        {
            ll w = 1;
            for (int k = j; k < j + h / 2; k++)
            {
                ll u = y[k] % mod;
                ll t = w * (y[k + h / 2] % mod) % mod;
                y[k] = (u + t) % mod;
                y[k + h / 2] = ((u - t) % mod + mod) % mod; 
                w = w * wn[id] % mod;
            }
        }
    }
    if (on == -1)
    {
        ll inv = Pow(len, mod - 2, mod);
        for (int i = 1; i < len / 2; i++)
            swap(y[i], y[len - i]);
        for (int i = 0; i < len; i++)
            y[i] = y[i] * inv % mod;
    }
}