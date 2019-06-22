#! /usr/bin/python3

# 783. Minimum Distance Between BST Nodes
# Easy
#
# Given a Binary Search Tree (BST) with the root node root, return the minimum difference between the values of any two different nodes in the tree.
#
# Example :
#
# Input: root = [4,2,6,1,3,null,null]
# Output: 1
# Explanation:
# Note that root is a TreeNode object, not an array.
#
# The given tree [4,2,6,1,3,null,null] is represented by the following diagram:
#
#           4
#         /   \
#       2      6
#      / \
#     1   3
#
# while the minimum difference in this tree is 1, it occurs between node 1 and node 2, also between node 3 and node 2.
#
# Note:
#
#     The size of the BST will be between 2 and 100.
#     The BST is always valid, each node's value is an integer, and each node's value is different.


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def minDiffInBST(self, root: TreeNode) -> int:
        l = self.to_list(root)
        l.sort()
        #print(l)
        min_diff = l[1]-l[0]
        for idx in range(1, len(l)-1, 1):
            e0 = l[idx]
            e1 = l[idx+1]
            min_diff = min(min_diff, e1-e0)
        return min_diff

    def to_list(self, root: TreeNode) -> List[int]:
        if root is None: return []
        l = [root.val]
        #if root.right is not None: l.append(root.right.val)
        #if root.left is not None: l.append(root.left.val)
        return l + self.to_list(root.right) + self.to_list(root.left)
