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
    TreeNode* rua(TreeNode* node)
    {
        if(node==NULL)  return NULL;
        if(node->left==NULL&&node->right==NULL) return node;
        else if(node->left==NULL)
        {
            return rua(node->right);
        }
        else 
        {
            TreeNode* ed = rua(node->left);
            ed->right = node->right;
            if(node->right!=NULL) 
            {
                ed = rua(node->right);
            }
            node->right = node->left;
            node->left = NULL;
            return ed;
        }
       
    }
    
    void flatten(TreeNode* root) {
        rua(root);
    }
};