


struct Heap
{
    vector<int> dat;
    int sz;

    void init()
    {
        dat.clear();
        sz = 0;
    }

    void insert(int num)
    {
        sz++;
        dat.push_back(num);
        push_up(sz);
    }

    int top()
    {
        if(sz==0)   return -1;
        else
        {
            return dat[0];
        }
    }

    void pop()
    {
        swap(dat[0],dat[sz-1]);
        sz--;
        push_down(1);
    }

    void push_up(int pos)
    {
        if(pos==1)  return;

        int fa = pos>>1;
        if(dat[fa-1]>dat[pos-1])
        {
            swap(dat[fa-1],dat[pos-1]);
            push_up(fa);
        }
    }

    void push_down(int pos)
    {
        int lchild = pos<<1;
        int rchild = pos<<1|1;
        if(lchild>sz)   return;
        else if(rchild>sz)
        {
            if(dat[lchild-1]<dat[pos-1])
            {
                swap(dat[lchild-1],dat[pos-1]);
                push_down(lchild);
            }
        }
        else
        {
            if(dat[lchild-1]<dat[rchild-1]&&dat[lchild-1]<dat[pos-1])
            {
                swap(dat[lchild-1],dat[pos-1]);
                push_down(lchild);
            }
            else if(dat[lchild-1]>=dat[lchild-1]&&dat[rchild-1]<=dat[pos-1])
            {
                swap(dat[rchild-1],dat[pos-1]);
                push_down(rchild);
            }
        }

    }
};