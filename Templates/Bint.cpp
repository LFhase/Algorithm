struct Bint{
    int num[5005],sz;
    Bint(){
        memset(num,0,sizeof(num));
        sz=0;
    }
    Bint operator*(const Bint &x){
        Bint t;
        for(int i=0;i<sz;i++){
            for(int j=0;j<x.sz;j++){
                t.num[i+j]+=num[i]*x.num[j];
                t.num[i+j+1]+=t.num[i+j]/P;
                t.num[i+j]%=P;
            }
        }
        int SZ=sz+x.sz-1;
        if(t.num[SZ])SZ++;
        t.sz=SZ;
        return t;
    }
    Bint operator/(const int &x){
        Bint t;
        for(int i=0;i<sz;i++)t.num[i]=num[i];
        t.sz=sz;
        int an=0;
        for(int i=sz-1;i>=0;i--)
            if(i)t.num[i-1]+=(t.num[i]%x)*P;
        for(int i=sz-1;i>=0;i--)
            t.num[i]/=x;
        while(!t.num[t.sz-1]&&t.sz>1)t.sz--;
        return t;
    }
    bool operator>(const Bint &x)const{
        if(sz>x.sz)return 1;
        else if(sz<x.sz)return 0;
        for(int i=sz-1;i>=0;i--){
            if(num[i]>x.num[i])return 1;
            else if(num[i]<x.num[i])return 0;
        }return 0;
    }
    void Print(){
        printf("%d",num[sz-1]);
        for(int i=sz-2;i>=0;i--)printf("%04d",num[i]);
        puts("");
    }//事实证明，这个十分好用
}