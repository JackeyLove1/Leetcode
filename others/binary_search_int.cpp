#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// binary search, the array is sorted from low to high
// not found return -1
int binarySearch(int A[], int n, const int &target) {
    if (n == 0) return -1;
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (A[mid] == target)
            return mid;
        else if (A[mid] > target)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}


// Test function
int main() {
    int A[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    cout<<binarySearch(A, 10, 0)<<endl;
    cout<<binarySearch(A, 10, 9)<<endl;
    cout<<binarySearch(A, 10, 6)<<endl;
    cout<<binarySearch(A, 10, 10)<<endl;
    return 0;
}