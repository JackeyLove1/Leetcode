def qSort(nums, l, r):
    if l >= r:
        return
    i = l - 1
    j = r + 1
    x = nums[(l + r) // 2]
    while i < j:
        i += 1
        while nums[i] < x:
            i += 1
        j -= 1
        while nums[j] > x:
            j -= 1
        if i < j:
            nums[i], nums[j] = nums[j], nums[i]
    qSort(nums, l, j)
    qSort(nums, j + 1, r)


def mergeSort(nums, l, r):
    if l >= r:
        return
    mid = (l + r) // 2
    mergeSort(nums, l, mid)
    mergeSort(nums, mid + 1, r)
    tmp = []
    i, j = l, mid + 1
    while i <= mid and j <= r:
        if nums[i] < nums[j]:
            tmp.append(nums[i])
            i += 1
        else:
            tmp.append(nums[j])
            j += 1
    while i <= mid:
        tmp.append(nums[i])
        i += 1
    while j <= r:
        tmp.append(nums[j])
        j += 1
    k = 0
    for i in range(l, r + 1):
        nums[i] = tmp[k]
        k += 1


def main():
    n = int(input())
    nums = list(map(int, input().split()))
    mergeSort(nums, 0, n - 1)
    for num in nums:
        print(num, end=" ")
    print()


if __name__ == "__main__":
    main()
