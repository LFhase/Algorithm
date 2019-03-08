/*
 * @lc app=leetcode.cn id=42 lang=cpp
 *
 * [42] 接雨水
 *
 * https://leetcode-cn.com/problems/trapping-rain-water/description/
 *
 * algorithms
 * Hard (41.75%)
 * Total Accepted:    9.4K
 * Total Submissions: 22.5K
 * Testcase Example:  '[0,1,0,2,1,0,1,3,2,1,2,1]'
 *
 * 给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
 * 
 * 
 * 
 * 上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。 感谢
 * Marcos 贡献此图。
 * 
 * 示例:
 * 
 * 输入: [0,1,0,2,1,0,1,3,2,1,2,1]
 * 输出: 6
 * 
 */
class Solution {
public:
    int trap(vector<int>& height) {
        
        int len = height.size();
        
        if(len==0)  return 0;
        int cur_height = height[0];
        int idx = 0;
        int width = 0;
        int to_decrease = 0;
        int res = 0;
        
        for(int i=1;i<len;++i)
        {
            if(height[i]>=cur_height)
            {
                res += cur_height*width-to_decrease;
                idx = i;
                cur_height = height[i]; 
                to_decrease = 0;
                width = 0;
            }
            else
            {
                width++;
                to_decrease += height[i];
            }
        }
        
        if(idx<len-1&&cur_height!=0)
        {
            int cur_h2 = height[len-1];
            width = 0;
            to_decrease = 0;
            for(int i=len-2;i>=0;--i)
            {
                if(height[i]>=cur_h2)
                {
                    res += cur_h2*width-to_decrease;
                    cur_h2 = height[i]; 
                    to_decrease = 0;
                    width = 0;
                }
                else
                {
                    width++;
                    to_decrease += height[i];
                }
                if(height[i]>=cur_height)   break;
            }
        }
        return res;
    }
};

