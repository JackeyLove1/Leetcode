#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <utility>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <atomic>
#include <thread>

#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

inline int count(int state) {
    return __builtin_popcount(state);
}

class TopVotedCandidate {
private:
    struct node {
        int person, vote;

        explicit node(int person_, int vote_) : person(person_), vote(vote_) {}

        bool operator<(const node &rhs) const {
            return vote < rhs.vote;
        }
    };

private:
    using PII = pair<int, int>;
    map<int, int> votes;
    map<int, int> time_leader;
    priority_queue<node> heap;
    int latest_person;
public:
    TopVotedCandidate(const vector<int> &persons, const vector<int> &times) {
        const int sz = persons.size();
        for (int i = 0; i < sz; ++i) {
            latest_person = persons[i];
            votes[persons[i]]++;
            heap.emplace(latest_person, votes[latest_person]);
            auto t = heap.top();
            // cout <<" top: " << t.person <<" : " << t.vote << endl;
            if (t.vote == votes[latest_person]){
                time_leader[times[i]] = latest_person;
            }else{
                time_leader[times[i]] = t.person;
            }
            // cout <<"times: " << times[i]<<" leader: " << time_leader[times[i]]<< endl;
        }
    }

    int q(int t) {
        auto it = time_leader.upper_bound(t);
        if (it == time_leader.end() || it->first != t) {
            --it;
        }
        // cout << "it.fisrt: " << it->first << " it.second: "<< it->second<<endl;
        return it->second;
    }
};

/**
 * Your TopVotedCandidate object will be instantiated and called as such:
 * TopVotedCandidate* obj = new TopVotedCandidate(persons, times);
 * int param_1 = obj->q(t);
 */

int main() {
    vector<int> times = {0, 5, 10, 15, 20, 25, 30};
    vector<int> persons = {0, 1, 1, 0, 0, 1, 0};
    TopVotedCandidate s(persons, times);
    cout << s.q(3) << " " << 0 << endl;
    cout << s.q(12) << " " << 1 << endl;
    cout << s.q(25) << " " << 1 << endl;
    cout << s.q(15) << " " << 0 << endl;
    cout << s.q(24) << " " << 0 << endl;
    cout << s.q(8) << " " << 1 << endl;
}