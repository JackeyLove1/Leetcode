def repeatedSubstringPattern(s: str) -> bool:
    k = len(s) // 2
    for i in range(1, k + 1):
        if s[0:i] * (len(s) // i) == s:
            return True
    return False

if __name__ == "__main__":
    print(repeatedSubstringPattern("abab"))
    print(repeatedSubstringPattern("aba"))
    print(repeatedSubstringPattern("abcabcabcabc"))