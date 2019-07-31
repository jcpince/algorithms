/*
717. 1-bit and 2-bit Characters
Easy

We have two special characters. The first character can be represented by one bit 0. The second
character can be represented by two bits (10 or 11).

Now given a string represented by several bits. Return whether the last character must be a
one-bit character or not. The given string will always end with a zero.

Example 1:

Input:
bits = [1, 0, 0]
Output: True
Explanation:
The only way to decode it is two-bit character and one-bit character. So the last character is
one-bit character.

Example 2:

Input:
bits = [1, 1, 1, 0]
Output: False
Explanation:
The only way to decode it is two-bit character and two-bit character. So the last character is NOT
one-bit character.

Note:
1 <= len(bits) <= 1000.
bits[i] is always 0 or 1.
*/

#include <bits/stdc++.h>

class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        if (bits.size() < 2) return true;
        int idx = bits.size() - 2;
        if (!bits[idx]) return true;
        int count = 0;
        while (idx >= 0 && bits[idx]) {count++;idx--;}
        return !(count & 0x1);
    }
};
