/*
 * @lc app=leetcode.cn id=215 lang=cpp
 *
 * [215] 数组中的第K个最大元素
 */

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
        if(dat.size()<sz)   dat.push_back(num);
        else    dat[sz-1] = num;
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
        if(pos>sz)  return;
        int lchild = pos<<1;
        int rchild = pos<<1|1;
        if(lchild>sz)   return;
        else if(rchild>sz)
        {
            if(dat[lchild-1]<dat[pos-1])
            {
                swap(dat[lchild-1],dat[pos-1]);
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


class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        Heap heap;
        heap.init();
        int len = nums.size();
        for(int i=0;i<len&&i<k;++i)
        {
            heap.insert(nums[i]);
        }
        for(int i=k;i<len;++i)
        {
            if(nums[i]<=heap.top())  continue;
            else
            {
                heap.pop();
                heap.insert(nums[i]);
            }
        }
        return heap.top();
    }
};

