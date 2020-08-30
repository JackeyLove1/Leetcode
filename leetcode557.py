def reverseWords(s: str) -> str:
    sl = s.split(" ")
    res = ""
    for strs in sl:
        res += strs[::-1] + " "
    return res.rstrip()


if __name__ == "__main__":
    s = "Let's take LeetCode contest"
    print(reverseWords(s))
