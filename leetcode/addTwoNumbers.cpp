/*
2. Add Two Numbers
Medium

You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example:

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.
*/

#include <iostream>
#include <cassert>
#include <cstring>
#include <vector>

#include "listNode.h"

using namespace std;

class Solution {
public:
    void add_with_carry(int &digit1, int &digit2, int &carry)
    {
        digit1 += digit2 + carry;
        if (digit1 >= 10)
        {
            digit1 -= 10;
            carry = 1;
        } else carry = 0;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *result = l1, *carry_node = l2, *last;
        int carry = 0, zero = 0;

        while (result && l2)
        {
            last = result;
            add_with_carry(result->val, l2->val, carry);
            l2 = l2->next;
            result = result->next;
        }
        if (!carry)
        {
            if (!result)
                last->next = l2;
        }
        else if (l2 || result)
        {
            last->next = l2 ? l2 : result;
            result = last->next;
            while (result && carry)
            {
                last = result;
                add_with_carry(result->val, zero, carry);
                result = result->next;
            }
        }
        if (carry)
        {
            carry_node->val = 1;
            last->next = carry_node;
            carry_node->next = NULL;
        }
        return l1;
    }
};

int get_nb_digits(int num)
{
    int res = 1;
    while (num > 10)
    {
        num /= 10;
        res++;
    }
    return res;
}

void num2list(int num, ListNode *list)
{
    int digit_idx = 0;
    while (num > 10)
    {
        int digit = num % 10;
        list[digit_idx].val = digit;
        if (num > 10)
            list[digit_idx].next = &list[digit_idx+1];
        num /= 10;
        digit_idx++;
    }
    list[digit_idx].val = num;
}

int list2num(ListNode *list)
{
    int num = 0, mult = 1;
    while (list)
    {
        assert(list->val < 10);
        num += list->val * mult;
        mult *= 10;
        list = list->next;
    }
    return num;
}

void test_numbers(int num1, int num2)
{
    Solution s;
    printf("Adds %d and %d:\n", num1, num2);
    ListNode l1[get_nb_digits(num1)];
    ListNode l2[get_nb_digits(num2)];
    num2list(num1, l1);
    l1->dump();
    assert(list2num(l1) == num1);
    num2list(num2, l2);
    l2->dump();
    assert(list2num(l2) == num2);
    ListNode *l = s.addTwoNumbers(l1, l2);
    l->dump();
    assert(list2num(l) == (num1 + num2));
}

int main(int argc, char **argv)
{
    Solution s;
    test_numbers(342, 465);
    test_numbers(0, 1);
    test_numbers(0, 465);
    test_numbers(465, 0);
    test_numbers(465, 4650001);
    test_numbers(465, 5);
    test_numbers(5, 465);
    test_numbers(5, 5);
    test_numbers(995, 5);
    test_numbers(5, 995);

    cout << "All tests succeeded" << endl;
    return 0;
}
