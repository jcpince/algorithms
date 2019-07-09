/*
https://leetcode.com/problems/implement-queue-using-stacks

232. Implement Queue using Stacks
Easy

Implement the following operations of a queue using stacks.

    push(x) -- Push element x to the back of queue.
    pop() -- Removes the element from in front of queue.
    peek() -- Get the front element.
    empty() -- Return whether the queue is empty.

Example:

MyQueue queue = new MyQueue();

queue.push(1);
queue.push(2);
queue.peek();  // returns 1
queue.pop();   // returns 1
queue.empty(); // returns false

Notes:
    You must use only standard operations of a stack -- which means only push to top, peek/pop from
    top, size, and is empty operations are valid.
    Depending on your language, stack may not be supported natively. You may simulate a stack by
    using a list or deque (double-ended queue), as long as you use only standard operations of a
    stack.
    You may assume that all operations are valid (for example, no pop or peek operations will be
    called on an empty queue).
*/

#include <bits/stdc++.h>
using namespace std;

class MyQueue {
private:
    vector<int> push_stack;
    vector<int> pop_stack;

    void inline refill_popstack() {
        /* copy the push stack into the pop stack in reverse order */
        pop_stack.reserve(push_stack.size());
        for (size_t index = push_stack.size() ; index > 0 ; index--)
            pop_stack.push_back(push_stack[index - 1]);
        push_stack.clear();
    }
public:
    /** Initialize your data structure here. */
    MyQueue() {

    }

    /** Push element x to the back of queue. */
    void push(int x) {
        push_stack.push_back(x);
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        if (pop_stack.empty()) refill_popstack();
        int res = pop_stack.back();
        pop_stack.pop_back();
        return res;
    }

    /** Get the front element. */
    int peek() {
        if (pop_stack.empty()) refill_popstack();
        return pop_stack.back();
    }

    /** Returns whether the queue is empty. */
    bool empty() {
        return pop_stack.empty() and push_stack.empty();
    }
};

int main() {
    MyQueue q;
    q.push(1);
    q.push(2);
    printf("q.peek() -> %d\n", q.peek());
    printf("q.pop() -> %d\n", q.pop());
    printf("q.empty() -> %d\n", q.empty());
    printf("q.pop() -> %d\n", q.pop());
    printf("q.empty() -> %d\n", q.empty());
    return 0;
}
