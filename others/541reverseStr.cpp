string reverseStr(string s, int k) {
    int i = 0;
    while (i<s.size()){
        if(i+k>s.size())
            reverse(s.begin()+1, s.end());
        else
            reverse(s.begin()+i, s.begin()+1+k);
        i += 2*k;
    }
    return s;
}