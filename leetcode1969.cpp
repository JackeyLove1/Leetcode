class Solution {
public:
    int minNonZeroProduct(int p) {
        //和不变，一个+2……n 一个-2……n，不会超过2^p-1，最多的1
        const int mod = 1000000007;
        long long res = 1;
        long long num = pow(2, p - 1);
        num --;
        
        long long maxNum = pow(2, p);
        maxNum--;
        
        res *= maxNum;
        res %= mod;
        
        long long a = (maxNum - 1) % mod;
        res *= qpow(a, num);
        res %= mod;
        
        return (int)res;
    }
    
    long long qpow(long long a, long long n){
        const int mod = 1000000007;
        long long ans = 1;
        while(n){
            if(n&1) {
                ans *= a;
                ans %= mod;
            }
            a *= a;
            a %= mod;
            n >>= 1; 
        }
        return ans;
    }
};