a = int(input())

f1, f2 = 0, 1

if a == 0:
    print(0)
else:
    for _ in range(a):
        f1, f2 = f2, f1 + f2
    print(f2)