class Solution {
public:
    vector<vector<string>> res;
    void backtrack(string s,vector<string>&path,int pre){
        string temp;
        if(pre>=s.size()){     //判断结束条件
            res.push_back(path);
            return;
        }
        for(int i=pre;i<s.size();i++){
            bool flag=true;
            temp=s.substr(pre, i-pre+1); //用临时变量存取分割所得的字符串
            int wide=temp.size();
            for(int j=0;j<wide;j++){        //判断是否为回文
                if(temp[j]!=temp[wide-1-j]){
                    flag=false;
                    break;
                }
            }
            if(flag==false) continue;
            path.push_back(temp);
            backtrack(s,path,i+1);
            path.pop_back();    //还原

        }
    }
    vector<vector<string>> partition(string s) {
        vector<string> path;
        backtrack(s,path,0);
        return res;
    }
};
