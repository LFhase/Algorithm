




// WeSolve Game
int a, b;
while(cin>>a>>b)
{
    if(a>b) swap(a,b);
    int temp=((b-a)*(1+sqrt(5))/2);
    if(a==temp)    cout<<0<<endl;
    else    cout<<1<<endl;
}


// SG Function 
vector<int> step;
vector<char> ans;
int sg[MAXN];
int M;

int sgg(int index)
{
    if(sg[index]!=-1)    return sg[index];
    int mk[MAXN];
    memset(mk,0,sizeof(mk));
    for(int i=0;i<step.size();++i)
        if(index>=step[i])
            mk[sgg(index-step[i])] = 1;
    int res = 0;
    for(int i=0;;i++)
        if(!mk[i])
        {
            res = i;
            break;
        }
    return sg[index] = res;
}

int main()
{
    while(scanf("%d",&M)!=EOF&&M)
    {
        step.clear();
        ans.clear();
        int tmp;
        memset(sg,-1,sizeof(sg));
        for(int i=1;i<=M;++i)
        {
            scanf("%d",&tmp);
            step.push_back(tmp);
        }
        sg[0] = 0;
        for(int i=1;i<MAXN;++i)
        {
            sgg(i);
            //cout<<i<<" "<<sg[i]<<endl;
        }
        int N;  scanf("%d",&N);
        while(N--)
        {
            int hnum;  scanf("%d",&hnum);
            int res = 0;
            for(int i=1;i<=hnum;++i)
            {
                scanf("%d",&tmp);
                res = res ^ sg[tmp];
            }
            if(res) ans.push_back('W');
            else    ans.push_back('L');
        }
        for(int i=0;i<ans.size();++i)
            printf("%c",ans[i]);
        printf("\n");
    }
    return 0;
}