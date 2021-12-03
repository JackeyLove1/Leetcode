from typing import List


def dfs(grid: List[List[str]], x: int, y: int):
    if x < 0 or y < 0 or x >= len(grid) or y >= len(grid[0]):
        return
    if grid[x][y] == "0":
        return
    grid[x][y] = "0"
    dfs(grid, x + 1, y)
    dfs(grid, x, y + 1)
    dfs(grid, x - 1, y)
    dfs(grid, x, y - 1)


def numIslands(grid: List[List[str]]) -> int:
    # print(grid)
    cnt = 0
    if len(grid) == 0 or len(grid[0]) == 0:
        return cnt
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            if grid[i][j] == "1":
                cnt += 1
                dfs(grid, i, j)
                #print(grid)
    return cnt


if __name__ == "__main__":
    grid = [
        ["1", "1", "0", "0", "0"],
        ["1", "1", "0", "0", "0"],
        ["0", "0", "1", "0", "0"],
        ["0", "0", "0", "1", "1"]
    ]
    print(numIslands(grid))
    grid2 = [
        ['1', '1', '1', '1', '0'],
        ['1', '1', '0', '1', '0'],
        ['1', '1', '0', '0', '0'],
        ['0', '0', '0', '0', '0']
    ]
    print(numIslands(grid2))
