/*
 * @lc app=leetcode.cn id=142 lang=cpp
 *
 * [142] 环形链表 II
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
    ListNode *detectCycle(ListNode *head) {
        if(head==NULL)  return NULL;
        ListNode* fp;
        ListNode* sp;
        fp = NULL;
        sp = NULL;
        int flag = 0;
        while(1){
            if(fp==sp&&fp!=NULL){
                flag = 1;
                break;
            }
                
            if(fp==NULL)    fp = head;
            else if(fp->next!=NULL)  fp = fp->next;
            else{
                flag = -1;
                break;
            }
            if(fp->next!=NULL)  fp = fp->next;
            else{
                flag = -1;
                break;
            }
            
            if(sp==NULL)    sp = head;
            else if(sp->next!=NULL)  sp = sp->next;
            else{
                flag = -1;
                break;
            }
        }
        
        if(flag==-1)    return NULL;
        fp = head;
        sp = sp->next;
        while(1){
            if(fp==sp)  break;
            fp = fp->next;
            sp = sp->next;
        }
        return fp;
    }
};

