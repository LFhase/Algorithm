
// KMP Algorithm
int fail[MAXN];
char str[MAXN];
char pattern[MAXN];

void get_fail(char* str)
{
    int i, j;
    fail[0] = -1 ;
    int len = strlen(str);
    i = 0, j = -1;
    while(i<len)
    {
        if(j==-1||str[i] == str[j])    fail[++i] = ++j;
        else    j = fail[j];
    }
}


int kmp()
{
    get_fail(pattern);
    int i, j;
    int cnt = 0;
    int lens = strlen(str);
    int lenp = strlen(pattern);
    i = j =0;
    while(i<lens&&j<lenp)
    {
        if(j==-1||str[i]==pattern[j])
        {
            i++;
            j++;
        }
        else    j = fail[j];
    }
    if(j==lenp) return i-lenp+1;
    else    return -1;
}



// Manacher
char str[MAXN*2], st[MAXN];
int RL[MAXN*2];

int manacher()
{
    memset(RL,0,sizeof(RL));
    int maxr = 0, maxlen = 0;
    int len = strlen(str);
    int pos = 1;
    for(int i=1; i<len-1; ++i)
    {
        if(i<=maxr) RL[i] = min(RL[(pos<<1)-i],maxr-i+1);
        else    RL[i] = 1;
        while(i>=RL[i]&&i+RL[i]<len&&str[i-RL[i]]==str[i+RL[i]])
        {
            RL[i] ++;
        }
        if(RL[i]+i-1>maxr)
        {
            maxr = RL[i]+i-1;
            pos = i;
        }
        maxlen = max(maxlen,RL[i]);
    }
    return maxlen - 1;
}

int main()
{
    //FSIO;
    //freopen("input","r",stdin);
    //freopen("output","w+",stdout);
    while(scanf("%s",st)!=EOF)
    {
        int len = strlen(st);
        for(int i=0; i<len; ++i)
        {
            str[i*2+1] = st[i];
            str[i*2] = '#';
        }
        str[len*2] = '#';
        str[len*2+1] = 0;
        //printf("%s\n",str);
        printf("%d\n",manacher());
        /*for(int i=0; i<strlen(str); ++i)
            cout<<RL[i]<<" ";
        cout<<endl;*/
    }
    return 0;
}   






struct Trie
{
    int next[MAXN][26],fail[MAXN],end[MAXN];
    int root,L;
    int newnode()
    {
        for (int i=0;i<26;i++)
            next[L][i]=-1;
        end[L++]=0;
        return L-1;
    }
    void init()
    {
        L=0;
        root=newnode();
    }
    void insert(char *buf)
    {
        int len=strlen(buf);
        int now=root;
        for (int i=0;i<len;i++)
        {
            if (next[now][buf[i]-'a']==-1)
                next[now][buf[i]-'a']=newnode();
            now=next[now][buf[i]-'a'];
        }
        end[now]++;
    }
    void build ()
    {
        queue<int >Q;
        fail[root]=root;
        for (int i=0;i<26;i++)
            if (next[root][i]==-1)
                next[root][i]=root;
            else
            {
                fail[next[root][i]]=root;
                Q.push(next[root][i]);
            }
        while (!Q.empty())
        {
            int now=Q.front();
            Q.pop();
            for (int i=0;i<26;i++)
                if (next[now][i]==-1)
                    next[now][i]=next[fail[now]][i];
                else
                {
                    fail[next[now][i]]=next[fail[now]][i];
                    Q.push(next[now][i]);
                }
        }
    }
    int query(char *buf)
    {
        int len=strlen(buf);
        int now=root;
        int res=0;
        for (int i=0;i<len;i++)
        {
            now=next[now][buf[i]-'a'];
            int temp=now;
            while (temp!=root)
            {
                res+=end[temp];
                end[temp]=0;
                temp=fail[temp];
            }
        }
        return res;
    }
};


// AC automation bless me~

int cnt[1<<11];
int dp[30][105][1<<11];
int N, M, K;

const int demension = 26;

struct Trie
{
    int next[MAXN][demension],fail[MAXN];
    int end[MAXN];
    int root,L;
    int newnode()
    {
        for (int i=0; i<demension; i++)
            next[L][i]=-1;
        end[L++]=0;
        return L-1;
    }
    void init()
    {
        L=0;
        root=newnode();
    }
    int change(char c)
    {
        return c-'a';
    }
    void insert(char *buf, int id)
    {
        int len=strlen(buf);
        int now=root;
        for (int i=0; i<len; i++)
        {
            if (next[now][change(buf[i])]==-1)
                next[now][change(buf[i])]=newnode();
            now=next[now][change(buf[i])];
        }
        end[now] |= (1<<id);
    }
    void build ()
    {
        queue<int >Q;
        fail[root]=root;
        for (int i=0; i<demension; i++)
            if (next[root][i]==-1)
                next[root][i]=root;
            else
            {
                fail[next[root][i]]=root;
                Q.push(next[root][i]);
            }
        while (!Q.empty())
        {
            int now=Q.front();
            if(end[fail[now]])  end[now]|=end[fail[now]];
            Q.pop();
            for (int i=0; i<demension; i++)
                if (next[now][i]==-1)
                    next[now][i]=next[fail[now]][i];
                else
                {
                    fail[next[now][i]]=next[fail[now]][i];
                    Q.push(next[now][i]);
                }
        }
    }
    void solve()
    {
        memset(dp,0,sizeof(dp));
        dp[0][0][0] = 1;
        for(int i=0;i<N;++i)
            for(int j=0;j<L;++j)
                for(int l=0;l<(1<<M);++l)
                if(dp[i][j][l])
                for(int k=0;k<demension;++k)
                {
                    int son = next[j][k];
                    int tmp = l|end[son];
                    dp[i+1][son][tmp] += dp[i][j][l];
                    dp[i+1][son][tmp]%=MOD;
                }
        int ans = 0;
        for(int l=0;l<(1<<M);++l)
        {
            if(cnt[l]<K)    continue;
            for(int i=0;i<L;++i)
                ans = (ans+dp[N][i][l])%MOD;
        }
        printf("%d\n",ans);
    }
};


Trie AC;
char str[105];



int main()
{
    //freopen("input","r",stdin);
    //freopen("output","w+",stdout);
    for(int i=0;i<(1<<11);++i)
    {
        cnt[i] = 0;
        for(int j=0;j<11;++j)
            if(1&(i>>j))    cnt[i]++;
    }
    while(~scanf("%d%d%d",&N,&M,&K)&&(N||M||K))
    {
        AC.init();
        for(int i=0;i<M;++i)
        {
            scanf(" %s",str);
            AC.insert(str,i);
        }
        AC.build();
        AC.solve();
    }
    return 0;
}



// Plalindrome  Automaton

char str[MAXN];
int now,cur,tot,last;
int fail[MAXN],cnt[MAXN],len[MAXN];
int ch[MAXN][26];
int val[MAXN];


int newnode(int x)
{
    len[tot] = x;
    return tot++;
}

int get_fail(int x, int n)
{
    while(str[n-len[x]-1]!=str[n]) x=fail[x];
    return x;
}

void init()
{
    memset(ch,0,sizeof(ch));
    str[0] = -1;
    fail[0]=1;
    last=0;
    newnode(0);
    newnode(-1);
}

void build_PAM(char* str)
{
    init();
    int curch;
    for(int i=1; str[i]; ++i)
    {
        curch = str[i]-'0';
        cur = get_fail(last,i);
        if (!ch[cur][curch])
        {
            now=newnode(len[cur]+2);
            fail[now]=ch[get_fail(fail[cur],i)][curch];
            ch[cur][curch]=now;
        }
        cnt[last=ch[cur][curch]]++;
        val[last] = curch;
    }
}
