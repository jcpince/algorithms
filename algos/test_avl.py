import unittest
import logging
from bst_avl import AVLNode

logging.basicConfig(level=logging.DEBUG,
    format='%(funcName)s:%(lineno)d -- %(message)s')

class TestStringMethods(unittest.TestCase):
    def build_avl0(self) -> AVLNode:
        root = AVLNode(5, "root")
        print("insert node7")
        root.insert(AVLNode(7, "node7"))
        print("insert node6")
        root.insert(AVLNode(6, "node6"))
        print("insert node8")
        root.insert(AVLNode(8, "node8"))
        print("insert node4")
        root.insert(AVLNode(4, "node4"))
        print("insert node3")
        root.insert(AVLNode(3, "node3"))
        return root

    def test_create_node(self):
        root = self.build_avl0()
        logging.debug("AVL root: %s" % str(root.to_list()))

if __name__ == "__main__":
    run_unit_test()
