/*
 * @lc app=leetcode.cn id=23 lang=cpp
 *
 * [23] 合并K个排序链表
 *
 * https://leetcode-cn.com/problems/merge-k-sorted-lists/description/
 *
 * algorithms
 * Hard (43.76%)
 * Total Accepted:    15.2K
 * Total Submissions: 34.8K
 * Testcase Example:  '[[1,4,5],[1,3,4],[2,6]]'
 *
 * 合并 k 个排序链表，返回合并后的排序链表。请分析和描述算法的复杂度。
 * 
 * 示例:
 * 
 * 输入:
 * [
 * 1->4->5,
 * 1->3->4,
 * 2->6
 * ]
 * 输出: 1->1->2->3->4->4->5->6
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* res = new ListNode(INT_MIN);
        vector<int> tot;
        int len_1 = lists.size();
        for(int i=0;i<len_1;++i)
        {
            ListNode* cur = lists[i];
            while(cur!=NULL)
            {
                tot.push_back(cur->val);
                cur = cur->next;
            }
        }
        sort(tot.begin(),tot.end());
        ListNode* cur = res;
        for(int u: tot)
        {
            cur->next = new ListNode(u);
            cur = cur->next;
        }
        res = res->next;
        return res;
    }
};

