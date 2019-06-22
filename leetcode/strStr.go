// 28. Implement strStr()
// Easy
//
// Implement strStr().
//
// Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
//
// Example 1:
//
// Input: haystack = "hello", needle = "ll"
// Output: 2
//
// Example 2:
//
// Input: haystack = "aaaaa", needle = "bba"
// Output: -1
//
// Clarification:
//
// What should we return when needle is an empty string? This is a great question to ask during an interview.
//
// For the purpose of this problem, we will return 0 when needle is an empty string. This is consistent to C's strstr() and Java's indexOf().

package main

import (
    "fmt"
)

func strStr(haystack string, needle string) int {
    if needle == "" {return 0}
    for i := 0 ; i < len(haystack) - len(needle) + 1 ; i++ {
        found := true
        for needle_idx := 0 ; needle_idx < len(needle) && found ; needle_idx++ {
            if haystack[i + needle_idx] != needle[needle_idx] { found = false }
        }
        if found { return i }
    }
    return -1
}

func main() {
    table := [] struct {
        input string
        needle string
        expected int
    } {
        { "hello", "ll", 2},
        { "aaaaa", "bba", -1 },
        { "aaaaa", "", 0 },
        { "a ", "a", 0 },
        { "a", "a", 0 },
    }
    var errors int = 0
    for _, test_case := range table {
        result := strStr(test_case.input, test_case.needle)
        if result != test_case.expected {
           errors++;
           fmt.Printf("expected(%s, %s) was incorrect, got: %d, wanted: %d.\n",
               test_case.input, test_case.needle, result, test_case.expected)
        }
    }

    fmt.Printf("Unit tests %d falures over %d tests\n", errors, len(table))
}
