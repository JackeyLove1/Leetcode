class Solution:
    def isValidSerialization(self, preorder: str) -> bool:
        tools = 1
        for nodes in preorder.split(','):
            tools -= 1
            if tools < 0:
                return False
            if nodes != '#':
                tools += 2
        return tools == 0