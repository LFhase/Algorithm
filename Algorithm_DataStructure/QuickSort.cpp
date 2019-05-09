
int partition(vector<int>& nums, int l, int r, int pos)
{
    int pivot = nums[pos];
    while (l<r)
    {
        while(l<r&&nums[r]>=pivot)  r--;
        while(l<r&&nums[l]<pivot)   l++;
        if(l<r)
        {
            swap(nums[l],nums[r]);
            l++;
            r--;
        }
    }
    return l;
}


int linear_select(vector<int>& nums, int l, int r, int k)
{

}