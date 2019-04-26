/*
 * @lc app=leetcode.cn id=166 lang=cpp
 *
 * [166] 分数到小数
 */
class Solution {
public:
    string fractionToDecimal(int numerator1, int denominator1) {
        if(denominator1==0)    return "NaN";
        else if(numerator1==0)    return to_string(0);
        
        
        long long numerator = numerator1;
        long long denominator = denominator1;
        map<int,int> pos_mk;
        int cycle_flag = 0;
        int neg_flag = (numerator<0)^(denominator<0);
        numerator = abs(numerator);
        denominator = abs(denominator);
        vector<int> res;
        string ans = "";
        ans += to_string(numerator/denominator);
        numerator%=denominator;
        int pos = 1;
        
        
        while(numerator){
            if(pos_mk[numerator]!=0){
                cycle_flag = pos_mk[numerator];
                break;
            }else{
                pos_mk[numerator] = pos;
            }
            numerator*=10;
            if(numerator<denominator){
                res.push_back(0);
            }else{
                res.push_back(numerator/denominator);
                numerator%=denominator;
            }
            pos++;
        }
        
        if(pos>1)  ans.push_back('.');
        for(int i=0;i<pos-1;++i){
            if(i==cycle_flag-1) ans.push_back('(');
            ans += to_string(res[i]);
        }
        if(cycle_flag!=0){
            ans.push_back(')');
        }
        if(neg_flag!=0) ans = "-"+ans;
        return ans;
    }
};

