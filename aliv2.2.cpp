// 给定一个长度为100万的整数数组（元素为0-100的整数），
// 请设计一个方法，能够找出是否存在连续X个元素中超过Y%的元素值都大于Z。
// XYZ为输入参数。例如 X = 4， Y=50， Z = 70 ，则 71，73，69，88满足要求。


#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

const int N = 1e6 + 100;
int n;
int x, y, z;
int nums[N];
int f[N];
int main(){
  cin >> n;
  cin >> x >> y >> z;
  for(int i = 1; i <= n; ++i){
    cin >> nums[i];
  }
  
  // f[i] 代表有连续f[i]个数字大于z
  int target = int(x * y / 100);
  for(int i = 1; i <= n; i++){
    if(nums[i] > z) {
      f[i] = f[i-1]+1;
      if (f[i] >= target){ // 表示存在，从后往前寻找答案
        for(int j = i - target + 1; j <= i; j++){
          cout << nums[j] << " ";
        }
        return 0;
      }
    }
  }
  
  cout << "不存在" << endl;
  return 0;
}


// 设计一个算法，计算出根号2的值，精度要求小数点后10000位
#include <iostream>
#include <vector>
#include <algorithm>

// 大数相加
vector<int> add(vector<int>& a, vector<int>& b){
  	vector<int> c;
    if(a.size()<b.size()) return add(b,a);
    int t=0;//进位
    for(int i=0;i<a.size();i++)//a.size() >= b.size()
    {
        if(i<a.size()) t+=a[i];
        if(i<b.size()) t+=b[i];
        c.push_back(t%10);
        t/=10;//更新进位
    }
  	if(t) c.push_back(t);
    return c;
}

// vector<int> multiply(vector<int>& a, vector<int>& b);
// 比较vetor是否达到了要求
bool cmp(vector<int>& a, 2){
  return a[0] >= 2;
}

// double计算（不符合要求）
double solve(double eps){
	double l = 0, r = 1.5;
  	while(r - l >= eps){
      double mid = (l + r) / 2;
      if (mid * mid  > 2) r = mid;
      else l = mid;
    }
  	return l;
}

// 将数组乘数组
vector<int> mul(vector<int> &a, vector<int> &b) {
    vector<int> c(a.size() + b.size(), 0); // 初始化为 0
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < b.size(); j++){
          c[i + j] += a[i] * b[j];
        }
    int t = 0;
    for (int i = 0; i < c.size(); i++) { 
        t += c[i];
        c[i] = t % 10;
        t /= 10;
    }
    while (c.size() > 1 && c.back() == 0) c.pop_back(); //去掉前导0
    return c;
}

// 给vecotr增添元素, 使用二分法在0-9之间寻找
void cal(vector<int>& a){
  int l = 0, r = 9;
  while(l < r){
    int mid = l + r >> 1;
    auto b = a;
    b.push_back(mid);
    auto tmp = multiply(b, b);
    if(cmp(tmp, 2))r = mid;
    else l = mid + 1;
  }
  a.push_back(l);
}


vector<int> solve(){
  // 第一位是整数位，后面的是小数位
  vector<int> a = {1};
  while(a.size() < 1e4){
    cal(a);
  }
  return a;
}