vector<int> grayCode(int n) {
    if (n == 0) return {0};
    vector<int> res;
    auto tmp = grayCode(n - 1);
    for (auto num : tmp) {
        res.push_back(num );
    }
    reverse(tmp.begin(), tmp.end());
    for(auto num : tmp){
        res.push_back(num + pow(2, n-1));
    }
    return res;
}

void print(vector<int> &nums) {
    for (auto num : nums) {
        cout << num << "  ";
    }
    cout << endl;
}

int main() {
    vector<int> v = grayCode(2);
    print(v);
    vector<int> v2 = grayCode(3);
    print(v2);
}