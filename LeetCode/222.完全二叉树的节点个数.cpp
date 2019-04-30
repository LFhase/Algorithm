/*
 * @lc app=leetcode.cn id=222 lang=cpp
 *
 * [222] 完全二叉树的节点个数
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
    int dfs(TreeNode* u)
    {
        int res = 0;
        if(u==NULL) return res;
        res++;
        if(u->left!=NULL)
        {
            res += dfs(u->left);
        }
        if(u->right!=NULL)
        {
            res += dfs(u->right);
        }
        return res;
    }
    
    int countNodes(TreeNode* root) 
    {
        return dfs(root);
    }
};

