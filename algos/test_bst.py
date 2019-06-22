import unittest
import logging
from bst import BST, BSTNode

logging.basicConfig(level=logging.DEBUG,
    format='%(funcName)s:%(lineno)d -- %(message)s')

class TestStringMethods(unittest.TestCase):
    def build_bst0(self) -> BST:
        bst = BST()
        bst.insert_node(0, "root")
        bst.insert_node(1, "node1")
        bst.insert_node(2, "node2")
        bst.insert_node(3, "node3")
        self.assertTrue(bst.root.right.value == 1)
        self.assertTrue(bst.root.left == None)
        self.assertTrue(bst.root.right.right.value == 2)
        self.assertTrue(bst.root.right.left == None)
        self.assertTrue(bst.root.right.right.right.value == 3)
        self.assertTrue(bst.root.right.right.right.left == None)
        self.assertTrue(bst.root.right.right.right.right == None)
        return bst

    def build_bst1(self) -> BST:
        bst = BST()
        bst.insert_node(5, "root")
        bst.insert_node(1, "node1")
        bst.insert_node(2, "node2")
        bst.insert_node(7, "node7")
        bst.insert_node(6, "node6")
        bst.insert_node(10, "node10")
        self.assertTrue(bst.root.value == 5)
        self.assertTrue(bst.root.left.value == 1)
        self.assertTrue(bst.root.left.right.value == 2)
        self.assertTrue(bst.root.right.value == 7)
        self.assertTrue(bst.root.right.left.value == 6)
        self.assertTrue(bst.root.right.right.value == 10)
        return bst

    def test_create_node(self):
        root = BSTNode(0, None)
        self.assertTrue(root.left == None)
        self.assertTrue(root.right == None)
        self.assertTrue(root.value == 0)
        self.assertTrue(root.ref == None)

        node1 = BSTNode(1, root)
        self.assertTrue(node1.left == None)
        self.assertTrue(node1.right == None)
        self.assertTrue(node1.value == 1)
        self.assertTrue(node1.ref == root)

        root.right = node1
        logging.debug("BST root: %s" % str(root.to_list()))
        logging.debug("BST node1: %s" % str(node1.to_list()))

    def test_insert_node(self):
        bst = self.build_bst0()
        logging.debug("BST root: %s" % str(bst.root.to_list()))
        logging.debug("BST root.right: %s" % str(bst.root.right.to_list()))

        bst = self.build_bst1()
        logging.debug("BST root: %s" % str(bst.root.to_list()))
        logging.debug("BST root.right: %s" % str(bst.root.right.to_list()))
        logging.debug("BST root.left: %s" % str(bst.root.left.to_list()))

    def test_search_node(self):
        bst = self.build_bst0()
        node = bst.search(2)
        self.assertTrue(node.value == 2)
        notfound = bst.search(17)
        self.assertTrue(notfound == None)
        notfound = bst.search(3)
        self.assertTrue(notfound.value == 3)
        notfound = bst.search(4)
        self.assertTrue(notfound == None)

    def test_smallest_node(self):
        bst = self.build_bst1()
        node1 = bst.root.left
        node7 = bst.root.right
        node6 = node7.left
        smallest = bst.smallest()
        self.assertTrue(smallest == 1)
        smallest = node7.smallest()
        self.assertTrue(smallest.value == 6)

    def test_delete_node(self):
        bst = BST()
        bst.insert_node(50, "node50")
        bst.insert_node(30, "node30")
        bst.insert_node(20, "node20")
        bst.insert_node(40, "node40")
        bst.insert_node(70, "node70")
        bst.insert_node(60, "node60")
        bst.insert_node(80, "node80")
        smallest = bst.smallest()
        self.assertTrue(smallest == 20)
        logging.debug("BST root: %s" % str(bst.to_list()))
        bst.delete_node(30)
        logging.debug("BST root: %s" % str(bst.to_list()))
        self.assertTrue(bst.root.left.value == 40)
        self.assertTrue(bst.root.left.left.value == 20)
        logging.debug("BST root: %s" % str(bst.to_list()))
        bst.delete_node(100)
        bst.delete_node(70)
        logging.debug("BST root: %s" % str(bst.to_list()))
        self.assertTrue(bst.root.right.value == 80)
        self.assertTrue(bst.root.right.left.value == 60)
        bst.delete_node(50)
        logging.debug("BST root: %s" % str(bst.to_list()))
        self.assertTrue(bst.root.value == 60)
        self.assertTrue(bst.root.left.value == 40)
        self.assertTrue(bst.root.right.value == 80)

    def test_delete_node2(self):
        bst = BST()
        bst.insert_node(50, "node50")
        bst.insert_node(30, "node30")
        bst.insert_node(20, "node20")
        bst.insert_node(40, "node40")
        bst.insert_node(70, "node70")
        bst.insert_node(60, "node60")
        bst.insert_node(80, "node80")
        smallest = bst.smallest()
        self.assertTrue(smallest == 20)
        logging.debug("BST root: %s" % str(bst.to_list()))
        bst.delete_node(30)
        self.assertTrue(bst.root.left.value == 40)
        self.assertTrue(bst.root.left.left.value == 20)
        logging.debug("BST root: %s" % str(bst.to_list()))
        bst.delete_node(70)
        logging.debug("BST root: %s" % str(bst.to_list()))

if __name__ == "__main__":
    run_unit_test()
