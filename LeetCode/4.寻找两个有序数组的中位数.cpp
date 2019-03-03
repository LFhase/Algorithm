/*
 * @lc app=leetcode.cn id=4 lang=cpp
 *
 * [4] 寻找两个有序数组的中位数
 *
 * https://leetcode-cn.com/problems/median-of-two-sorted-arrays/description/
 *
 * algorithms
 * Hard (33.46%)
 * Total Accepted:    35.9K
 * Total Submissions: 107.2K
 * Testcase Example:  '[1,3]\n[2]'
 *
 * 给定两个大小为 m 和 n 的有序数组 nums1 和 nums2。
 * 
 * 请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。
 * 
 * 你可以假设 nums1 和 nums2 不会同时为空。
 * 
 * 示例 1:
 * 
 * nums1 = [1, 3]
 * nums2 = [2]
 * 
 * 则中位数是 2.0
 * 
 * 
 * 示例 2:
 * 
 * nums1 = [1, 2]
 * nums2 = [3, 4]
 * 
 * 则中位数是 (2 + 3)/2 = 2.5
 * 
 * 
 */
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        
        if((m+n)%2) return find_kth_number(nums1,0,nums2,0,(m+n)/2+1);
        else return (find_kth_number(nums1,0,nums2,0,(m+n)/2)+find_kth_number(nums1,0,nums2,0,(m+n)/2+1))/2.0;
    }

    double find_kth_number(vector<int>& nums1, int st1, vector<int>& nums2, int st2, int k)
    {
        if(st1>=nums1.size())   return nums2[st2 + k-1];
        if(st2>=nums2.size())   return nums1[st1 + k-1];
        
        if(k==1)    return min(nums1[st1],nums2[st2]);

        int num1 = 1e9+7;
        int num2 = 1e9+7;
        if(k/2-1+st1<nums1.size()) num1 = nums1[st1 + k/2-1];
        if(k/2-1+st2<nums2.size()) num2 = nums2[st2 + k/2-1];

        if(num1<num2)   return find_kth_number(nums1,st1+k/2,nums2,st2,k-k/2);
        else return find_kth_number(nums1,st1,nums2,st2+k/2,k-k/2);
    }
};

