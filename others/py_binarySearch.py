# binary_search
def binary_search(list, target):
    low, high = 0, len(list) - 1
    while low <= high:
        mid = (low + high) // 2
        guess = list[mid]
        if guess == target:
            return mid
        elif guess < target:
            low = mid + 1
        else:
            high = mid - 1
    return None


def main():
    my_list = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    print(binary_search(my_list, 0))
    print(binary_search(my_list, 10))
    print(binary_search(my_list, 5))


if __name__ == "__main__":
    main()
