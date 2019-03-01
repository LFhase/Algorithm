/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 *
 * https://leetcode-cn.com/problems/two-sum/description/
 *
 * algorithms
 * Easy (44.60%)
 * Total Accepted:    247.9K
 * Total Submissions: 555.8K
 * Testcase Example:  '[2,7,11,15]\n9'
 *
 * 给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
 * 
 * 你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。
 * 
 * 示例:
 * 
 * 给定 nums = [2, 7, 11, 15], target = 9
 * 
 * 因为 nums[0] + nums[1] = 2 + 7 = 9
 * 所以返回 [0, 1]
 * 
 * 
 */
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int,int> mark;
        mark.clear();
        int len = nums.size();
        vector<int> res;
        res.clear();
        for(int i=0;i<len;++i)
        {
            int cur = nums[i];
            if(mark[target-cur]!=0)
            {
                res.push_back(mark[target-cur]-1);
                res.push_back(i);
                break;
            }
            mark[cur] = i+1;
        }
        
        return res;
    }
};

