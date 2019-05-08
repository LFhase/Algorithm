/*
 * @lc app=leetcode.cn id=654 lang=cpp
 *
 * [654] 最大二叉树
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* do_construct(vector<int>& nums, int l, int r)
    {
        if(l>r) return NULL;
        if(l==r)  
        {
            TreeNode* res;
            res = new TreeNode(nums[l]);
            return res;
        }
        TreeNode* res;
        int pos = l;
        for(int i=l;i<=r;++i)
        {
            if(nums[i]>nums[pos])   pos = i;
        }
        res = new TreeNode(nums[pos]);
        res->left = do_construct(nums,l,pos-1);
        res->right = do_construct(nums,pos+1,r);
        return res;
    }
    
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return do_construct(nums,0,nums.size()-1);
    }
};

