class Solution {
public:
    
    map<string,int> analysis(string& formula, int l, int r, map<int,int>& match)
    {
        map<string,int> res;
        if(l>r) return res;
        
        string cur = "";
        string num = "";
        for(int i=l;i<=r;++i)
        {
            if(formula[i]=='(')
            {
                if(cur.length())    
                {
                    if(num.length())    res[cur]+=atoi(num.c_str());
                    else    res[cur]++;
                    num = "";
                    cur = "";
                }

                int num = 1;
                int nxt_match = match[i];
                map<string,int> tmp = analysis(formula,i+1,nxt_match,match);
                string mul_factor = "";
                for(i=nxt_match+1;i<=r;++i)
                    if(formula[i]>='0'&&formula[i]<='9')    mul_factor += formula[i];
                    else    
                    {
                        if(i<=r)    i--;
                        break;
                    }
                if(mul_factor.length()) 
                {
                    num=atoi(mul_factor.c_str());
                }

                
                for(auto u: tmp)
                {
                    res[u.first] += u.second*num;
                }
                
            }
            else if(formula[i]>='0'&&formula[i]<='9')   num += formula[i];
            else if(formula[i]>='a'&&formula[i]<='z')   cur += formula[i];
            else if(formula[i]>='A'&&formula[i]<='Z')  
            {
                if(!cur.length())
                {
                    cur += formula[i];
                    continue;
                }
                if(num.length())    res[cur]+=atoi(num.c_str());
                else    res[cur]++;
                num = "";
                cur = "";
                cur += formula[i];
            }
        }
        
        if(cur.length())    
        {
            if(num.length())    res[cur]+=atoi(num.c_str());
            else    res[cur]++;
            num = "";
            cur = "";
        }
        return res;
    }
    
    string countOfAtoms(string formula) {

        map<int,int> match;
        int len = formula.length();
        stack<int> to_match;
        for(int i=0;i<len;++i)
        {
            if(formula[i]=='(') to_match.push(i);
            else if(formula[i]==')')    
            {
                int tp = to_match.top(); to_match.pop();
                match[tp] = i;
            }
        }
        
        
        map<string,int> res = analysis(formula,0,len-1,match);
        string ans = "";
        for(auto u: res)
            if(u.second>1)  ans += u.first+to_string(u.second);
            else    ans += u.first;
        return ans;
    }
};