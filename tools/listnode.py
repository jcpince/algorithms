class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

    def __str__(self):
        l = list()
        cell = self
        while cell.next is not None:
            l.append(cell.val)
            cell = cell.next
        l.append(cell.val)
        return str(l)

    def prepend(self, x):
        new_root = ListNode(x)
        new_root.next = self
        return new_root

    def append(self, x) -> None:
        new_root = ListNode(x)
        cell = self
        while cell.next is not None:
            cell = cell.next
        cell.next = new_root
