class Solution {
public:
    int countValidWords(string sentence) {
        int n = sentence.length();
        int l = 0, r = 0;
        int ret = 0;
        string_view slice(sentence);
        while (true) {
            while (l < n && sentence[l] == ' ') {
                l++;
            }
            if (l >= n) {
                break;
            }
            r = l + 1;
            while (r < n && sentence[r] != ' ') {
                r++;
            }
            if (isValid(slice.substr(l, r - l))) { // 判断根据空格分解出来的 token 是否有效
                ret++;
            }
            l = r + 1;
        }
        return ret;
    }

    bool isValid(const string_view &word) {
        int n = word.length();
        bool has_hyphens = false;
        for (int i = 0; i < n; i++) {
            if (word[i] >= '0' && word[i] <= '9') {
                return false;
            } else if (word[i] == '-') {
                if (has_hyphens == true || i == 0 || i == n - 1 || !islower(word[i - 1]) || !islower(word[i + 1])) {
                    return false;
                }
                has_hyphens = true;
            } else if (word[i] == '!' || word[i] == '.' || word[i] == ',') {
                if (i != n - 1) {
                    return false;
                }
            }
        }
        return true;
    }
};

