#! /usr/bin/python3
from listnode import ListNode

class Solution:
    def mergeTwoLists(self, l1: ListNode, l2: ListNode) -> ListNode:
        if l1 is None: return l2
        if l2 is None: return l1
        if l1.val < l2.val:
            lres = l1
            lnext = l2
        else:
            lres = l2
            lnext = l1
        lres.next = self.mergeTwoLists(lres.next, lnext)
        return lres

def check_solution():
    s = Solution()
    list1 = ListNode(1)
    list1.append(2)
    list1.append(3)
    list1.append(4)
    list2 = ListNode(1)
    list2.append(2)
    list2.append(3)
    list2.append(4)
    print("list1 = %s" % str(list1))
    print("list2 = %s" % str(list2))
    lres = s.mergeTwoLists(list1, list2)
    print("list1 + list2 = %s" % str(lres))

check_solution()
