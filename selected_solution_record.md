# 剑指Offer

> A cool name which is the same as a famous book





### 1. Digit with only one appearance

***tag***：bitset

***statement***：

数组中有一个数仅出现了一次，剩下的出现了两次，求出这个仅出现一次的数

***solution***：

xor

***remark***：





### 2. Next Permutation

***tag***：Algorithm, Leetcode 31

***statement***：

Implement **next permutation**

***solution***：

倒序找出最后一个出现$num_i < num_{i+1}$的点，找出i+1之后最小的数与$num_i$互换

***remark***：





### 3. 开关灯问题

***tag***：Algorithm

***statement***：

关灯问题，有n个人，第i个人会按编号为i, 2i, 3i, ... 的开关，问最后亮着的灯

***solution***：

$O(n\sqrt(n))$ 分解因数

事实上是找完全平方数的个数

***remark***：



### 4. Find the Duplicate Number

***tag***：Algorithm, LeetCode 287

***statement***：

长度为n+1的数组，取值范围是[1,n]，求该数组中重复数字

***solution***：

通过 nums[num[i]] 将数组看作一个链表，可证明数组有环

问题转化为寻找有环链表的入口元素

双指针法：

- 首先判断是否有环，令一个指针每次走两步，另一个每次走一步，如两者相遇则有环；
- 设从head到入口距离为$l_1$，入口到相遇处距离为$l_2$，则可以证明，相遇点经过环再到入口点距离为$l_1$；

同理求上述重复数字即可；

***remark***：

2019 MS 工程院三面=、=跪了



### 5. Merge K Sorted Lists

***tag***：Algorithm, LeetCode 23

***statement***：

Merge *k* sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

***solution***：

用第一个与后面的k-1个合并就好了，复杂度O(k*len)

***remark***：

MS一面=、=我为什么要写堆呢



### 6. Jumping Cows

***tag***：Algorithm, POJ 2181

***statement***：

按顺序取给定序列中子序列，按奇数位加，偶数位减，的原则计算和，求最大和

***solution***：

DP

两个变量分别记录前i个操作偶数次、奇数次最大和，互相转移即可。

***remark***：

有点巧妙