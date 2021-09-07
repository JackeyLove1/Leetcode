#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

inline ListNode *makeList(vector<int> &nums) {
    auto dummy = new ListNode(-1);
    auto curr = dummy;
    for (auto &num : nums) {
        curr->next = new ListNode(num);
        curr = curr->next;
    }
    return dummy->next;
}

class SolutionReverse {
public:
    ListNode *reverseList1(ListNode *head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode *prev = nullptr;
        auto curr = head;
        while (curr) {
            auto next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }

    ListNode *reverseList(ListNode *head) {
        if (head == nullptr || head->next == nullptr) return head;
        auto newhead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return newhead;
    }
};

// LC61
class SolutionRotate {
public:
    ListNode *rotateRight(ListNode *head, int k) {
        if (k == 0 || head == nullptr || head->next == nullptr) return head;
        int n = 1;
        auto iter = head;
        while (iter->next) {
            iter = iter->next;
            ++n;
        }
        int add = n - k % n;
        if (add == n) {
            return head;
        }
        iter->next = head;
        while (add--) {
            iter = iter->next;
        }
        auto ret = iter->next;
        iter->next = nullptr;
        return ret;
    }
};

// LC141,142
class SolutionDetectCycle {
public:
    ListNode *detectCycle(ListNode *head) {
        if (head == nullptr || head->next == nullptr) return nullptr;
        auto fast = head, slow = head;
        while (fast) {
            slow = slow->next, fast = fast->next;
            if (!fast || !fast->next) return nullptr;
            fast = fast->next;
            if (fast == slow) break;
        }
        slow = head;
        while (slow != fast) {
            slow = slow->next, fast = fast->next;
        }
        return slow;
    }
};

// LC 21
class SolutionMerge2List {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        auto dummy = new ListNode(-1);
        auto curr = dummy;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                curr->next = l1;
                curr = curr->next, l1 = l1->next;
            } else {
                curr->next = l2;
                curr = curr->next, l2 = l2->next;
            }
        }
        curr->next = l1 == nullptr ? l2 : l1;
        return dummy->next;
    }
};

// LC23
class SolutionMergeKLists {
public:
    ListNode *merge(ListNode *l1, ListNode *l2) {
        auto dummy = new ListNode(-1);
        auto curr = dummy;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                curr->next = l1;
                l1 = l1->next, curr = curr->next;
            } else {
                curr->next = l2;
                l2 = l2->next, curr = curr->next;
            }
        }
        curr->next = l1 == nullptr ? l2 : l1;
        return dummy->next;
    }

    ListNode *mergeKLists1(vector<ListNode *> &lists) {
        if (lists.empty()) return nullptr;
        auto ret = lists[0];
        for (int i = 1; i < lists.size(); ++i) {
            ret = merge(ret, lists[i]);
        }
        return ret;
    }

    struct Status {
        int val;
        ListNode *ptr;

        bool operator<(const Status &rhs) const {
            return val > rhs.val;
        }
    };

    priority_queue<Status> q;

    ListNode *mergeKLists(vector<ListNode *> &lists) {
        for (auto node: lists) {
            if (node) q.push({node->val, node});
        }
        auto dummy = new ListNode(-1);
        auto curr = dummy;
        while (!q.empty()) {
            auto f = q.top();
            q.pop();
            curr->next = f.ptr;
            curr = curr->next;
            if (f.ptr->next) q.push({f.ptr->next->val, f.ptr->next});
        }
        return dummy->next;
    }
};

inline void print(ListNode *head) {
    auto p = head;
    while (p) {
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;
}

// LC 92
class SolutionReverseBetween {
public:
    void reverseList(ListNode *head) {
        ListNode *prev = nullptr;
        auto curr = head;
        while (curr != nullptr) {
            auto next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
    }

    ListNode *reverseBetween(ListNode *head, int left, int right) {
        auto dummy = new ListNode(-1, head);
        auto prev = dummy;
        // move left - 1 steps
        for (int i = 0; i < left - 1; i++) {
            prev = prev->next;
        }
        auto leftNode = prev->next;
        auto rightNode = prev;
        // move right - left + 1 step
        for (int i = 0; i < right - left + 1; i++) {
            rightNode = rightNode->next;
        }
        auto curr = rightNode->next;
        // cut
        prev->next = nullptr;
        rightNode->next = nullptr;
        reverseList(leftNode);
        // link
        prev->next = rightNode;
        leftNode->next = curr;
        return dummy->next;
    }
};

// LC143
class SolutionReorder {
public:
    inline void print(ListNode *head) {
        auto p = head;
        while (p) {
            cout << p->val << " ";
            p = p->next;
        }
        cout << endl;
    }

    ListNode *reverse(ListNode *head) {
        ListNode *prev = nullptr;
        auto curr = head;
        while (curr) {
            auto next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }

    void reorderList(ListNode *head) {
        if (head == nullptr || head->next == nullptr) return;
        int n = 0;
        auto curr = head;
        while (curr) {
            ++n;
            curr = curr->next;
        }
        auto dummy = new ListNode(-1, head);
        curr = dummy;
        int m = n / 2;
        while (m--) {
            curr = curr->next;
        }
        auto l2 = curr->next;
        curr->next = nullptr;
        l2 = reverse(l2);
        auto l1 = head;
        curr = dummy;
        // print(l1);
        // print(l2);
        while (l1 && l2) {
            curr->next = l1;
            l1 = l1->next;
            curr = curr->next;
            curr->next = l2;
            l2 = l2->next;
            curr = curr->next;
        }
        curr->next = l1 ? l1 : l2;
        head = dummy->next;
    }

};

// LC2
class SolutionAddTwoNumbers {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        auto dummy = new ListNode(-1);
        auto curr = dummy;
        int carry = 0;
        while (l1 || l2) {
            int x = l1 == nullptr ? 0 : l1->val;
            int y = l2 == nullptr ? 0 : l2->val;
            if (l1) l1 = l1->next;
            if (l2) l2 = l2->next;
            int sum = x + y + carry;
            carry = sum / 10;
            curr->next = new ListNode(sum % 10);
            curr = curr->next;
        }
        if (carry) curr->next = new ListNode(carry);
        return dummy->next;
    }
};


// LC19
class SolutionRemoveFromEnd {
public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        auto dummy = new ListNode(-1, head);
        auto slow = dummy, fast = dummy;
        for (int i = 0; i < n; i++) {
            fast = fast->next;
        }
        while (fast->next) {
            slow = slow->next;
            fast = fast->next;
        }
        slow->next = slow->next->next;
        return dummy->next;
    }
};

// LC24
class SolutionSwapPairs {
public:
    ListNode *swapPairs(ListNode *head) {
        auto dummy = new ListNode(-1, head);
        auto curr = dummy;
        while (curr->next != nullptr && curr->next->next != nullptr) {
            auto node1 = curr->next, node2 = curr->next->next;
            curr->next = node2;
            node1->next = node2->next;
            node2->next = node1;
            curr = node1;
        }
        return dummy->next;
    }
};


ListNode *removeNthFromEnd(ListNode *head, int n) {
    auto dummy = new ListNode(-1, head);
    auto slow = dummy, fast = dummy;
    for (int i = 0; i < n; i++) {
        fast = fast->next;
    }
    while (fast->next) {
        slow = slow->next;
        fast = fast->next;
    }
    slow->next = slow->next->next;
    return dummy->next;
}

ListNode *swapPairs(ListNode *head) {
    auto dummy = new ListNode(-1, head);
    auto curr = dummy;
    while (curr->next != nullptr && curr->next->next != nullptr) {
        auto node1 = curr->next, node2 = curr->next->next;
        curr->next = node2;
        node1->next = node2->next;
        node2->next = node1;
        curr = node1;
    }
    return dummy->next;
}


// LC83
class SolutionDeleteDuplicates {
public:
    ListNode *deleteDuplicates(ListNode *head) {
        if (head == nullptr || head->next == nullptr) return head;
        auto curr = head;
        while (curr->next) {
            if (curr->val == curr->next->val) {
                curr->next = curr->next->next;
            } else {
                curr = curr->next;
            }
        }
        return head;
    }
};

class SolutionDeleteDup2 {
public:
    ListNode *deleteDuplicates(ListNode *head) {
        auto dummy = new ListNode(-1, head);
        auto cur = dummy;
        while (cur->next && cur->next->next) {
            if (cur->next->val == cur->next->next->val) {
                int x = cur->next->val;
                while (cur->next && cur->next->val == x) {
                    cur->next = cur->next->next;
                }
            } else {
                cur = cur->next;
            }
        }
        return dummy->next;
    }
};

// LC328
class SolutionOddEven {
public:
    ListNode *oddEvenList(ListNode *head) {
        if (head == nullptr) return nullptr;
        auto evenHead = head->next;
        auto odd = head;
        auto even = evenHead;
        while (even && even->next) {
            odd->next = even->next;
            odd = odd->next;
            even->next = odd->next;
            even = even->next;
        }
        odd->next = evenHead;
        return head;
    }
};

ListNode *oddEvenList(ListNode *head) {
    if (head == nullptr) return nullptr;
    auto evenHead = head->next;
    auto odd = head;
    auto even = evenHead;
    while (even && even->next) {
        odd->next = even->next;
        odd = odd->next;
        even->next = odd->next;
        even = even->next;
    }
    odd->next = evenHead;
    return head;
}

ListNode *partition(ListNode *head, int x) {
    auto less = new ListNode(-1), great = new ListNode(-1);
    auto greatHead = great, lessHead = less;
    while (head != nullptr) {
        if (head->val < x) {
            less->next = head;
            less = less->next;
        } else {
            great->next = head;
            great = great->next;
        }
        head = head->next;
    }
    great->next = nullptr;
    less->next = greatHead->next;
    return lessHead->next;
}

// LC84
class Solution84 {
public:
    ListNode *partition(ListNode *head, int x) {
        auto less = new ListNode(-1);
        auto great = new ListNode(-1);
        auto greatHead = great, lessHead = less;
        while (head != nullptr) {
            if (head->val < x) {
                less->next = head;
                less = less->next;
            } else {
                great->next = head;
                great = great->next;
            }
            head = head->next;
        }
        great->next = nullptr;
        less->next = greatHead->next;
        return lessHead->next;
    }
};

// LC02.01
class Solution0201 {
public:
    ListNode *removeDuplicateNodes(ListNode *head) {
        if (head == nullptr || head->next == nullptr) return head;
        unordered_set<int> s;
        auto pos = head;
        s.insert(pos->val);
        while (pos->next) {
            auto curr = pos->next;
            if (s.count(curr->val)) {
                pos->next = pos->next->next;
            } else {
                s.insert(curr->val);
                pos = pos->next;
            }
        }
        pos->next = nullptr;
        return head;
    }
};

ListNode *removeDuplicateNodes(ListNode *head) {
    if (head == nullptr || head->next == nullptr) return head;
    unordered_set<int> s;
    auto pos = head;
    s.insert(pos->val);
    while (pos->next) {
        auto curr = pos->next;
        if (s.count(curr->val)) {
            pos->next = pos->next->next;
        } else {
            s.insert(curr->val);
            pos = pos->next;
        }
    }
    pos->next = nullptr;
    return head;
}

// LC203
class SolutionRemoveElements {
public:
    ListNode *removeElements(ListNode *head, int val) {
        if (head == nullptr) return head;
        auto dummy = new ListNode(-1, head);
        auto prev = dummy, curr = dummy->next;
        while (curr) {
            if (curr->val == val) {
                prev->next = curr->next;
                curr->next = nullptr;
                curr = prev->next;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
        return dummy->next;
    }
};

ListNode *removeElements(ListNode *head, int val) {
    if (head == nullptr) return head;
    auto dummy = new ListNode(-1, head);
    auto prev = dummy, curr = dummy->next;
    while (curr) {
        if (curr->val == val) {
            prev->next = curr->next;
            curr->next = nullptr;
            curr = prev->next;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    return dummy->next;
}

// LC0205
class SolutionAddTwoNumbers0205 {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        auto dummy = new ListNode(-1);
        auto curr = dummy;
        int carry = 0;
        while (l1 || l2) {
            int x = l1 == nullptr ? 0 : l1->val;
            int y = l2 == nullptr ? 0 : l2->val;
            if (l1) l1 = l1->next;
            if (l2) l2 = l2->next;
            int sum = x + y + carry;
            curr->next = new ListNode(sum % 10);
            curr = curr->next;
            carry = sum / 10;
        }
        if (carry) curr->next = new ListNode(carry);
        return dummy->next;
    }
};

// LC24
class SolutionSwapPairs2 {
public:
    ListNode *swapPairs(ListNode *head) {
        if (head == nullptr || head->next == nullptr) return head;
        auto dummy = new ListNode(-1, head);
        auto curr = dummy;
        while (curr->next && curr->next->next) {
            auto n1 = curr->next, n2 = curr->next->next;
            n1->next = n2->next;
            curr->next = n2;
            n2->next = n1;
            curr = n1;
        }
        return dummy->next;
    }
};

ListNode *swapPairs1(ListNode *head) {
    if (head == nullptr || head->next == nullptr) return head;
    auto dummy = new ListNode(-1, head);
    auto curr = dummy;
    while (curr->next && curr->next->next) {
        auto n1 = curr->next, n2 = curr->next->next;
        n1->next = n2->next;
        curr->next = n2;
        n2->next = n1;
        curr = n1;
    }
    return dummy->next;
}

// LC206
class SolutionReverse2 {
public:
    ListNode *reverseList(ListNode *head) {
        ListNode *prev = nullptr;
        auto curr = head;
        while (curr) {
            auto next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
};

// LC25
class SolutionReverseK {
public:
    using PLL = pair<ListNode *, ListNode *>;

    PLL reverse2(ListNode *head, ListNode *tail) {
        tail->next = nullptr;
        ListNode *prev = nullptr;
        auto curr = head;
        while (curr) {
            auto next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head->next = nullptr;
        return {tail, head};
    }

    ListNode *reverseKGroup(ListNode *head, int k) {
        auto dummy = new ListNode(-1, head);
        auto curr = dummy;
        while (curr != nullptr) {
            auto l = curr->next, r = curr;
            for (int i = 0; i < k; ++i) {
                r = r->next;
                if (r == nullptr) return dummy->next;
            }
            auto next = r->next;
            // cout << "l:" << l->val << " r: " << r->val << endl;
            auto[lnew, rnew] = reverse2(l, r);
            // cout << "lnew: ";
            // print(lnew);
            curr->next = lnew;
            rnew->next = next;
            curr = rnew;
            // print(dummy->next);
        }
        return dummy->next;
    }
};

using PLL = pair<ListNode *, ListNode *>;

PLL reverse2(ListNode *head, ListNode *tail) {
    tail->next = nullptr;
    ListNode *prev = nullptr;
    auto curr = head;
    while (curr) {
        auto next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head->next = nullptr;
    return {tail, head};
}

ListNode *reverseKGroup(ListNode *head, int k) {
    auto dummy = new ListNode(-1, head);
    auto curr = dummy;
    while (curr != nullptr) {
        auto l = curr->next, r = curr;
        for (int i = 0; i < k; ++i) {
            r = r->next;
            if (r == nullptr) return dummy->next;
        }
        auto next = r->next;
        // cout << "l:" << l->val << " r: " << r->val << endl;
        auto[lnew, rnew] = reverse2(l, r);
        // cout << "lnew: ";
        // print(lnew);
        curr->next = lnew;
        rnew->next = next;
        curr = rnew;
        // print(dummy->next);
    }
    return dummy->next;
}

class SolutionDeleteDup1 {
public:
    ListNode *deleteDuplicates(ListNode *head) {
        auto dummy = new ListNode(-1, head);
        auto curr = dummy;
        while (curr->next && curr->next->next) {
            int x = curr->next->val;
            if (curr->next->next->val == x) {
                while (curr->next && curr->next->val == x) {
                    curr->next = curr->next->next;
                }
            } else {
                curr = curr->next;
            }
        }
        return dummy->next;
    }
};

ListNode *deleteDuplicates2(ListNode *head) {
    auto dummy = new ListNode(-1, head);
    auto curr = dummy;
    while (curr->next && curr->next->next) {
        int x = curr->next->val;
        if (curr->next->next->val == x) {
            while (curr->next && curr->next->val == x) {
                curr->next = curr->next->next;
            }
        } else {
            curr = curr->next;
        }
    }
    return dummy->next;
}

// LC148
class Solution148Play {
public:
    struct Node {
        ListNode *node;
        int val;

        // explicit Node(ListNode *_node) : node(_node), val(_node->val) {}

        // explicit Node(ListNode *_node, int _val) : node(_node), val(_val) {}

        bool operator<(const Node &rhs) const {
            return val > rhs.val;
        }
    };

    ListNode *sortList(ListNode *head) {
        priority_queue<Node> q;
        auto dummy = new ListNode(-1);
        auto curr = dummy;
        while (head) {
            q.push({head, head->val});
            head = head->next;
        }
        while (!q.empty()) {
            auto t = q.top();
            q.pop();
            curr->next = t.node;
            curr = curr->next;
        }
        return dummy->next;
    }
};

class SolutionMergeSort {
public:
    ListNode *findMiddleNode(ListNode *head) {
        if (head == nullptr || head->next == nullptr) return head;
        auto slow = head;
        auto fast = head->next->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    ListNode *mergeTwoList(ListNode *l1, ListNode *l2) {
        auto dummy = new ListNode(-1);
        auto curr = dummy;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                curr->next = l1;
                l1 = l1->next;
            } else {
                curr->next = l2;
                l2 = l2->next;
            }
            curr = curr->next;
        }
        curr->next = l1 == nullptr ? l2 : l1;
        return dummy->next;
    }

    ListNode *sortList(ListNode *head) {
        if (head == nullptr || head->next == nullptr) return head;
        auto mid = findMiddleNode(head);
        auto rightHead = mid->next;
        mid->next = nullptr;

        auto left = sortList(head);
        auto right = sortList(rightHead);

        return mergeTwoList(left, right);
    }
};

// LC106
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// LC146
struct DLNode {
    DLNode *prev;
    DLNode *next;
    int key, value;

    DLNode() : key(-1), value(-1), prev(nullptr), next(nullptr) {}

    DLNode(int _key, int _value) : key(_key), value(_value), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    DLNode *head;
    DLNode *tail;
    unordered_map<int, DLNode *> cache;
    int size;
    int capacity;
public:
    LRUCache(int _capacity) : size(0), capacity(_capacity) {
        head = new DLNode();
        tail = new DLNode();
        head->next = tail;
        tail->prev = head;
    }

    void addToFront(DLNode *node) {
        auto next = head->next;
        head->next = node;
        node->next = next;
        next->prev = node;
        node->prev = head;
    }

    void removeNode(DLNode *node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->prev = nullptr;
        node->next = nullptr;
    }

    void moveTofront(DLNode *node) {
        removeNode(node);
        addToFront(node);
    }

    DLNode *removeTail() {
        auto node = tail->prev;
        removeNode(node);
        return node;
    }

    int get(int key) {
        if (cache.count(key)) {
            auto node = cache[key];
            moveTofront(node);
            return node->value;
        } else {
            return -1;
        }
    }

    void put(int key, int value) {
        if (cache.count(key)) {
            auto node = cache[key];
            node->value = value;
            moveTofront(node);
            return;
        }
        auto newNode = new DLNode(key, value);
        cache[key] = newNode;
        addToFront(newNode);
        if (++size > capacity) {
            auto oldNode = removeTail();
            --size;
            cache.erase(oldNode->key);
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

// LC106
class Solution106 {
public:
    unordered_map<int, int> cache;
    int pos;

    TreeNode *build(int left, int right, vector<int> &inorder, vector<int> &postorder) {
        if (left > right) return nullptr;
        auto rootVal = postorder[pos];
        int idx = cache[rootVal];
        auto root = new TreeNode(rootVal);
        --pos;
        root->right = build(idx + 1, right, inorder, postorder);
        root->left = build(left, idx - 1, inorder, postorder);
        return root;
    }

    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        pos = postorder.size() - 1;
        for (int i = 0; i < inorder.size(); ++i) {
            cache[inorder[i]] = i;
        }
        auto root = build(0, pos, inorder, postorder);
        return root;
    }
};


// LC1367
class Solution1367 {
public:
    bool solve(ListNode *head, TreeNode *root) {
        if (head == nullptr) return true;
        if (root == nullptr || head->val != root->val) return false;
        return solve(head->next, root->left) || solve(head->next, root->right);
    }

    bool isSubPath(ListNode *head, TreeNode *root) {
        if (root == nullptr) return false;
        auto h1 = head, h2 = head;
        return solve(head, root) || isSubPath(h1, root->left)
               || isSubPath(h2, root->right);
    }
};

// LC 912
class Solution912 {
public:
    void qsort(vector<int> &nums, int l, int r) {
        if (l >= r) return;
        int x = nums[l + r >> 1];
        int i = l - 1, j = r + 1;
        while (i < j) {
            do ++i; while (nums[i] < x);
            do --j; while (nums[j] > x);
            if (i < j) swap(nums[i], nums[j]);
        }
        qsort(nums, l, j), qsort(nums, j + 1, r);
    }

    vector<int> sortArray(vector<int> &nums) {
        qsort(nums, 0, nums.size() - 1);
        return nums;
    }
};


// LC153
class Solution153 {
public:
    int findMin(vector<int> &nums) {
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            int mid = l + r >> 1;
            if (nums[r] > nums[mid]) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return nums[l];
    }
};

// LC4
class Solution {
public:
    int getKthElement(const vector<int> &nums1, const vector<int> &nums2, int k) {
        /* 主要思路：要找到第 k (k>1) 小的元素，那么就取 pivot1 = nums1[k/2-1] 和 pivot2 = nums2[k/2-1] 进行比较
         * 这里的 "/" 表示整除
         * nums1 中小于等于 pivot1 的元素有 nums1[0 .. k/2-2] 共计 k/2-1 个
         * nums2 中小于等于 pivot2 的元素有 nums2[0 .. k/2-2] 共计 k/2-1 个
         * 取 pivot = min(pivot1, pivot2)，两个数组中小于等于 pivot 的元素共计不会超过 (k/2-1) + (k/2-1) <= k-2 个
         * 这样 pivot 本身最大也只能是第 k-1 小的元素
         * 如果 pivot = pivot1，那么 nums1[0 .. k/2-1] 都不可能是第 k 小的元素。把这些元素全部 "删除"，剩下的作为新的 nums1 数组
         * 如果 pivot = pivot2，那么 nums2[0 .. k/2-1] 都不可能是第 k 小的元素。把这些元素全部 "删除"，剩下的作为新的 nums2 数组
         * 由于我们 "删除" 了一些元素（这些元素都比第 k 小的元素要小），因此需要修改 k 的值，减去删除的数的个数
         */

        int m = nums1.size();
        int n = nums2.size();
        int index1 = 0, index2 = 0;

        while (true) {
            // 边界情况
            if (index1 == m) {
                return nums2[index2 + k - 1];
            }
            if (index2 == n) {
                return nums1[index1 + k - 1];
            }
            if (k == 1) {
                return min(nums1[index1], nums2[index2]);
            }

            // 正常情况
            int newIndex1 = min(index1 + k / 2 - 1, m - 1);
            int newIndex2 = min(index2 + k / 2 - 1, n - 1);
            int pivot1 = nums1[newIndex1];
            int pivot2 = nums2[newIndex2];
            if (pivot1 <= pivot2) {
                k -= newIndex1 - index1 + 1;
                index1 = newIndex1 + 1;
            } else {
                k -= newIndex2 - index2 + 1;
                index2 = newIndex2 + 1;
            }
        }
    }

    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
        int totalLength = nums1.size() + nums2.size();
        if (totalLength % 2 == 1) {
            return getKthElement(nums1, nums2, (totalLength + 1) / 2);
        } else {
            return (getKthElement(nums1, nums2, totalLength / 2) + getKthElement(nums1, nums2, totalLength / 2 + 1)) /
                   2.0;
        }
    }
};

int main() {
    vector<int> nums = {1, 2, 3, 3, 4, 4, 5};
    auto head = makeList(nums);
    print(head);

}