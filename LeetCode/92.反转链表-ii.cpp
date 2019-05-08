/*
 * @lc app=leetcode.cn id=92 lang=cpp
 *
 * [92] 反转链表 II
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if(m==n)    return head;
        ListNode* posm_1 = NULL;
        ListNode* posm = NULL;
        ListNode* cur = head;
        int pos = 1;
        while(cur!=NULL&&pos<m-1)
        {
            cur = cur->next;
            pos++;
        }
        if(m==1)    posm_1 = NULL;
        else    posm_1 = cur;
        ListNode* last = cur;
        while(cur!=NULL&&pos<=n)
        {
            if(pos==m)  posm = cur;
            pos++;
            ListNode* tmp = cur->next;
            cur->next = last;
            last = cur;
            cur = tmp;
            
        }
        if(m==1)    head = last; 
        else    posm_1->next = last;
        posm ->next = cur;
        return head;
    }
};

