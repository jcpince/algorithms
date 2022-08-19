#! /usr/bin/python3

from listnode import ListNode
from typing import Optional

class Solution:
    def merge(self, head0: Optional[ListNode], head1: Optional[ListNode]):
        # shead0 = "%s" % head0
        # shead1 = "%s" % head1
        if head0.val < head1.val:
            head = head0
            head0 = head0.next
        else:
            head = head1
            head1 = head1.next
        current = head
        while head0 and head1:
            if head0.val < head1.val:
                current.next = head0
                head0 = head0.next
            else:
                current.next = head1
                head1 = head1.next
            current = current.next
        if head0:
            current.next = head0
        else:
            current.next = head1
        # print("merge(%s, %s) returns %s" % (shead0, shead1, head))
        return head

    def sort(self, head: Optional[ListNode], len : int):
        # print("calling sort(%s, %d)" % (head, len))
        if len == 1:
            return head

        mid = head
        len0 = len // 2
        len1 = len0 + 1 if len0 * 2 < len else len0
        idx = 0
        while idx < len0:
            pmid = mid
            mid = mid.next
            idx += 1
        pmid.next = None
        # assert(mid)
        # print("calling merge(sort(%s, %d), sort(%s, %d)" % (head, len0, mid, len1))
        return self.merge(self.sort(head, len0), self.sort(mid, len1))

    def sortList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        # print("calling sortList(%s)" % head)
        if head is None or head.next is None:
            return head

        last = head
        mid = head
        len0 = 1
        while last.next and last.next.next:
            mid = mid.next
            last = last.next.next
            len0 += 1
        len1 = len0
        if not last.next:
            len1 -= 1
        
        pmid= mid
        mid = mid.next
        pmid.next = None
        # print("calling merge(sort(%s, %d), sort(%s, %d)" % (head, len0, mid, len1))
        return self.merge(self.sort(head, len0), self.sort(mid, len1))

def check_solution():
    s = Solution()
    head = ListNode(4)
    head.append(1)
    head.append(3)
    head.append(2)
    strhead = "%s" % head
    shead = s.sortList(head)
    print("head(%s) sorted = %s" % (strhead, shead))

    head = ListNode(4)
    head.append(3)
    head.append(2)
    head.append(1)
    head.append(0)
    strhead = "%s" % head
    shead = s.sortList(head)
    print("head(%s) sorted = %s" % (strhead, shead))

check_solution()