/*
 * @lc app=leetcode.cn id=2 lang=cpp
 *
 * [2] 两数相加
 *
 * https://leetcode-cn.com/problems/add-two-numbers/description/
 *
 * algorithms
 * Medium (32.77%)
 * Total Accepted:    88.1K
 * Total Submissions: 268.9K
 * Testcase Example:  '[2,4,3]\n[5,6,4]'
 *
 * 给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。
 * 
 * 如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。
 * 
 * 您可以假设除了数字 0 之外，这两个数都不会以 0 开头。
 * 
 * 示例：
 * 
 * 输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
 * 输出：7 -> 0 -> 8
 * 原因：342 + 465 = 807
 * 
 * 
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        
        if(l1==NULL)    return l2;
        else if(l2==NULL)   return l1;
        
        ListNode* res = NULL;
        ListNode* cur = NULL;
        int nxt = 0;

        while(l1!=NULL||l2!=NULL){
            ListNode* tmp = new ListNode(0);
            if(res==NULL) 
            {
                res = tmp;
                cur = tmp;
            }
            else
            {
                cur->next = tmp;
                cur = tmp;
            }

            int num1 = l1==NULL?0:l1->val;
            int num2 = l2==NULL?0:l2->val;
            
            cur->val = (num1+num2+nxt);
            nxt = cur->val/10;
            cur->val %= 10;

            if(l1!=NULL)    l1 = l1->next;
            if(l2!=NULL)   l2 = l2->next;
        }

        if(nxt!=0)
        {
            cur->next =new ListNode(nxt);
        }

        return res;
    }
};

