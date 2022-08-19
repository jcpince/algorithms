# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

    def append(self, val):
        last = self
        while last.next:
            last = last.next
        last.next = ListNode(val=val)

    def __str__(self):
        l = []
        n = self
        while n:
            l.append(n.val)
            n = n.next
        return str(l)
