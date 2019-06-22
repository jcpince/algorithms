class BST(object):
    pass

class BSTNode:
    def __init__(self, value: int, ref: object):
        self.right = None
        self.left = None
        self.value = value
        self.ref = ref

    def to_list(self):
        l = list()
        l.append([self.value, self.ref])
        #print("Append value(%d)" % self.value)
        if self.left:
            print("Append (%d).left(%d)" % (self.value, self.left.value))
            l.append(self.left.to_list())
        else: l.append(None)
        if self.right:
            print("Append (%d).right(%d)" % (self.value, self.right.value))
            l.append(self.right.to_list())
        else: l.append(None)
        return l

class BST:
    def __init__(self):
        self.root = None

    def insert_node(self, node: BST) -> None:
        # O(h) with h height of the tree
        if self.root is None:
            self.root = node
            return
        current = self.root
        while(True):
            if node.value >= current.value:
                if current.right:
                    current = current.right
                else:
                    current.right = node
                    break
            else:
                if current.left:
                    current = current.left
                else:
                    current.left = node
                    break

    def delete_node(self, node: BSTNode) -> bool:
        return self.delete_value(node.value)

    def delete_value(self, value: int) -> bool:
        pred, to_delete = self.search_with_pred(value)
        if to_delete is None:
            return False
        # Delete the root
        if pred == None:
            if to_delete.right is None:
                self.root = to_delete.left
                return True

            smallest_pred, smallest = self.smallest_with_pred(None, to_delete.right)
            # if smallest_pred is not None:
            #     print("Root delete -- smallest_pred(%d), smallest(%d)" % (smallest_pred.value, smallest.value))
            # else:
            #     print("Root delete -- smallest_pred(None), smallest(%d)" % (smallest.value))
            if smallest_pred is not None:
                smallest.left = self.root.left
            else:
                smallest.left = self.root.left
            self.root = smallest
            return True

        # print("Removing %d, pred is %d" % (to_delete.value, pred.value))
        # Delete a leaf
        if to_delete.right is None and to_delete.left is None:
            if pred.right == to_delete:
                pred.right = None
            else:
                pred.left = None
            return True

        # Delete a node with a single child
        if to_delete.right is None:
            if pred.right == to_delete:
                pred.right = to_delete.left
            else:
                pred.left = to_delete.left
            return True
        if to_delete.left is None:
            if pred.left == to_delete:
                pred.left = to_delete.right
            else:
                pred.right = to_delete.right
            return True

        # Delete a node with 2 children
        if pred.right == to_delete:
            smallest_pred, smallest = self.smallest_with_pred(pred, to_delete.left)
            # print("smallest_pred(%d), smallest(%d)" % (smallest_pred.value, smallest.value))
            #smallest_pred.right = None
            pred.right = smallest
            smallest.left = to_delete.left if (smallest != to_delete.left) else None
            smallest.right = to_delete.right
        else:
            smallest_pred, smallest = self.smallest_with_pred(pred, to_delete.right)
            # print("smallest_pred(%d), smallest(%d)" % (smallest_pred.value, smallest.value))
            #smallest_pred.left = None
            pred.left = smallest
            smallest.left = to_delete.left
            smallest.right = to_delete.right if (smallest != to_delete.right) else None

        return True

    def search(self, value: int, intermediate_root = None) -> BSTNode:
        _, found = self.search_with_pred(value, intermediate_root)
        return found

    def search_with_pred(self, value: int, intermediate_root = None) -> BSTNode:
        # O(h) with h height of the tree or subtree
        # (which can be n if the tree is all left or right)
        current = intermediate_root
        pred = None
        if current is None:
            current = self.root
        while current is not None:
            if value > current.value:
                pred = current
                current = current.right
            elif value < current.value:
                pred = current
                current = current.left
            else:
                return pred, current
        return None, None

    def smallest(self, intermediate_root = None) -> BSTNode:
        _, smallest = self.smallest_with_pred(None, intermediate_root)
        return smallest

    def smallest_with_pred(self, pred, intermediate_root) -> BSTNode:
        # O(h) with h height of the tree or subtree
        # (which can be n if the tree is all left or right)
        current = intermediate_root
        if current is None:
            current = self.root
        smallest = current
        smallest_pred = pred
        while current is not None:
            if smallest.value > current.value:
                smallest = current
                smallest_pred = pred
            pred = current
            current = current.left
        return smallest_pred, smallest

    def to_list(self, current: BSTNode = None):
        if current is None:
            current = self.root
            if current is None:
                return []
        l = list()
        l.append([current.value, current.ref])
        if current.left:
            l.append(self.to_list(current.left))
        else: l.append(None)
        if current.right:
            l.append(self.to_list(current.right))
        else: l.append(None)
        return l
