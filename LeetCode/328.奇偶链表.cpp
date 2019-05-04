/*
 * @lc app=leetcode.cn id=328 lang=cpp
 *
 * [328] 奇偶链表
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
    ListNode* oddEvenList(ListNode* head) {
        if(head==NULL)  return head;
        ListNode* p = head;
        ListNode* odd = head;
        ListNode* even_head = NULL;
        ListNode* even = NULL;
        if(p->next!=NULL)    
        {
            even = p->next;
            even_head = even;
            p = p->next;
        }
        int pos = 3;
        while(p->next!=NULL)
        {
            if(pos&1)   
            {
                odd->next = p->next;
                odd = odd->next;
            }
            else    
            {
                even->next = p->next;
                even = even->next;
            }
            p = p->next;
            pos++;
        }
        
        odd->next = even_head;
        if(even!=NULL)  even->next = NULL;
        return head;
    }
};

