from bst import BSTNode

# TO BE CONTINUED

class AVLNode:
    pass

class AVLNode(BSTNode):
    def __init__(self, value: int, ref: object):
        super(AVLNode, self).__init__(value, ref)
        self.height = 0

    def __str__(self):
        return "(%d: %d - %s)" % (self.height, self.value, self.ref)

    def _insert(self, node: AVLNode) -> None:
        if node.value >= self.value:
            self.height += 1
            if self.right is None:
                self.right = node
                return
            branch = self.right
        else:
            self.height -= 1
            if self.left is None:
                self.left = node
                return
            branch = self.left
        return branch._insert(node)

    def insert(self, node: AVLNode) -> None:
        self._insert(node)
        self.balance()

    def adjust_height(self) -> None:
        if self.right:
            if self.left:
                self.height = max(self.right.height, self.left.height) + 1
            else:
                self.height = self.right.height + 1
        else:
            self.height = self.left.height + 1

    def balance(self, started = False, done = False) -> (bool, bool):
        if done: return True, True
        left_height = 0 if (self.left is None) else self.left.height
        right_height = 0 if (self.right is None) else self.right.height
        print("Checks balance for %s (%s(%s) vs %s(%d))" %
            (self.ref, self.left, left_height, self.right, right_height))

        if abs(right_height - left_height) < 2:
            if started:
                return True, True
            else:
                return False, False

        print("Balancing needed")

        return True, False
