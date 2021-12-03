#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
    int total = 0;
    int j = -1;
    for (int i = 0, sum = 0; i < gas.size(); i++) {
        sum += gas[i] - cost[i];
        total += gas[i] - cost[i];
        if (sum < 0) {
            j = i;
            sum = 0;
        }
    }
    return total >= 0 ? j + 1 : -1;
}

int main() {
    vector<int> gas = {1, 2, 3, 4, 5};
    vector<int> cost = {3, 4, 5, 1, 2};
    cout << canCompleteCircuit(gas, cost) << endl;
    return 0;
}