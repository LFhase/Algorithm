/*
 * @lc app=leetcode.cn id=287 lang=cpp
 *
 * [287] 寻找重复数
 */
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int len = nums.size();
        int fast = nums[nums[0]];
        int slow = nums[0];
        while(1){
            if(fast==slow){
                fast = nums[0];
                slow = nums[slow];
                while(fast!=slow){
                    fast = nums[fast];
                    slow = nums[slow];
                }
                break;
            }
            fast = nums[nums[fast]];
            slow = nums[slow];
        }
        return slow;
    }
};

