class BSTNode:
    pass

class BSTNode:
    def __init__(self, value: int, ref: object):
        self.right = None
        self.left = None
        self.value = value
        self.ref = ref

    def __str__(self):
        return "(%d - %s)" % (self.value, self.ref)

    def to_list(self):
        l = list()
        l.append(str(self))
        #print("Append value(%d)" % self.value)
        if self.left:
            #print("Append (%d).left(%d)" % (self.value, self.left.value))
            l.append(self.left.to_list())
        else: l.append(None)
        if self.right:
            #print("Append (%d).right(%d)" % (self.value, self.right.value))
            l.append(self.right.to_list())
        else: l.append(None)
        return l

    def insert(self, node: BSTNode) -> bool:
        if node.value == self.value:
            return False
        if node.value > self.value:
            if self.right is None:
                self.right = node
            else: return self.right.insert(node)
        else:
            if self.left is None:
                self.left = node
            else: return self.left.insert(node)
        return True

    def delete(root: BSTNode, value: int) -> BSTNode:
        if root is None:
            return None
        if root.value > value:
            root.left = BSTNode.delete(root.left, value)
            return root
        elif root.value < value:
            root.right = BSTNode.delete(root.right, value)
            return root

        # Found it!
        if root.right is None:
            return root.left

        smallest = root.right.smallest()
        root.value = smallest.value
        root.ref = smallest.ref
        root.right = BSTNode.delete(root.right, smallest.value)
        return root

    def search(self, value: int) -> BSTNode:
        if self.value > value:
            if self.left is None:
                return None
            return self.left.search(value)
        elif self.value < value:
            if self.right is None:
                return None
            return self.right.search(value)
        return self


    def smallest(self) -> BSTNode:
        # O(h) with h height of the tree or subtree
        # (which can be n if the tree is all left or right)
        if self.left is None:
            return self
        return self.left.smallest()


class BST:
    def __init__(self):
        self.root = None

    def insert_node(self, value: int, ref: object) -> None:
        # O(h) with h height of the tree
        if self.root is None:
            self.root = BSTNode(value, ref)
        else:
            self.root.insert(BSTNode(value, ref))

    def delete_node(self, value: int) -> None:
        if self.root is None:
            return
        BSTNode.delete(self.root, value)

    def search(self, value: int) -> BSTNode:
        if self.root is None:
            return None
        return self.root.search(value)

    def smallest(self) -> int:
        if self.root is None:
            return None
        return self.root.smallest().value

    def to_list(self):
        return self.root.to_list()
