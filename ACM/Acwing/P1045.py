if __name__ == "__main__":
    n = int(input())
    res = str(2 ** n - 1)
    print(len(res))
    while len(res) < 500:
        res = "0" + res
    res = res[len(res) - 500:]
    for i in range(10):
        print(res[50 * i:50 * (i + 1)])
