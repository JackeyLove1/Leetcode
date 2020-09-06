class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution:
    def isFather(self, root, child):
        if root == None:
            return False
        if root.val == child.val:
            return True
        return self.isFather(root.right, child) or self.isFather(root.left, child)

    def isCommonFather(self, root, p, q):
        if self.isFather(root, p) and self.isFather(root, q):
            return True
        return False

    def commonFather(self, root, p, q, res):
        if root == None:
            return
        if self.isCommonFather(root, p, q):
            res = root
        self.commonFather(root.left, p, q, res)
        self.commonFather(root.right, p, q, res)

    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        res = TreeNode(-1)
        self.commonFather(root, p, q, res)
        return res
