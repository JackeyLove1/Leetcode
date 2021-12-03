package main

func maxInt(a, b int) int {
	if a > b{
		return a
	}
	return b
}

func maxSubArray(nums []int) int {
	n := len(nums)
	if n == 0{
		return 0
	}
	if n == 1{
		return nums[0]
	}
	res := nums[0]
	f := make([]int, n+1)
	f[0] = nums[0]
	for idx, num := range nums {
		if idx == 0 {
			continue
		}
		f[idx] = maxInt(nums[idx], f[idx-1] + num)
		res = maxInt(f[idx], res)
	}
	return res
}
