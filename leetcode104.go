type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func maxInt(a, b int) int{
	if a > b{
		return a
	}
	return b
}

func maxDepth(root *TreeNode) int {
	if root == nil{
		return 0
	}
	left := maxDepth(root.Left)
	right := maxDepth(root.Right)
	return maxInt(left, right) + 1
}