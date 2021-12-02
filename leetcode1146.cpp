//
// Created by Jacky on 2021/12/1.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>
#include <unordered_map>
#include <map>

using namespace std;

class SnapshotArray {
private:
    using seq_ = int;
    using index_ = int;
    using value_ = int;
    using entry_ = pair<seq_, value_>;
    // vec_[index] -> entry_ {seq_, value_}
    vector<vector<entry_>> vec_;
    int snap_count_;
public:
    SnapshotArray(int length) : snap_count_(0) {
        vec_.resize(length + 1);
    }

    void set(int index, int val) {
        vec_[index].emplace_back(snap_count_, val);
    }

    int snap() {
        return snap_count_++;
    }

    int get(int index, int snap_id) {
        auto &indexVector = vec_[index];
        if (indexVector.empty()) {
            return 0;
        }
        for (auto iter = indexVector.rbegin(); iter != indexVector.rend(); ++iter) {
            // 找到第一个小于等于snap_id的value
            if (iter->first <= snap_id) {
                return iter->second;
            }
        }
        return 0;
    }
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */

int main(){
    auto s = SnapshotArray(3);
    s.set(0, 5);
    cout << s.snap() << endl;
}