#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

#if 0
class Solution {
        void enlarge_range(const char *s, uint32_t &offset,
                uint32_t &size) {

                while (offset && s[offset+size] &&
                        s[offset-1] == '(' and s[offset+size] == ')')
                {
                        size += 2;
                        offset--;

                }
                printf("enlarge_range('%s', %u, %u)\n", s, offset, size);

                /* merge forwards and backwards */

        }
        void add_new_valid_range(const char *s, uint32_t offset,
                list<uint32_t> &sizes, list<uint32_t> &offsets)
        {
                uint32_t size = 2;
                enlarge_range(s, offset, size);
                sizes.push_back(size);
                offsets.push_back(offset);
        }
public:
        int longestValidParentheses(string str)
        {
                list<uint32_t> sizes, offsets;
                uint32_t longest = 0, nb_valids = 0, tmp;

                if (str.length() < 2) return 0;

                const char *s = str.c_str();
                int offset = 0;
                while(s[offset+1])
                {
                        if (s[offset] == '(' and s[offset+1] == ')')
                        add_new_valid_range(s, offset, sizes, offsets);
                        offset++;
                }
                nb_valids = sizes.size();
                printf("Found %d ranges in '%s':\n", nb_valids, s);
                list<uint32_t>::iterator io = offsets.begin();
                for (list<uint32_t>::iterator is = sizes.begin(); is != sizes.end(); is++) {
                        printf("Range: offset %u, size %u\n", *io, *is);
                        if (io != offsets.end()) io++;
                }

                /* Not a single pair found */
                if (!nb_valids) return 0;

                do {
                        uint32_t size = sizes.front();sizes.pop_front();
                        uint32_t offset = offsets.front();offsets.pop_front();
                        tmp = size;
                        printf("Check if we can merge range at offset %d, size %d with range at offset %d, size %d\n",
                                offset, size, offsets.front(), sizes.front());
                        while (offsets.size() && offset+size == offsets.front())
                        {
                                size += sizes.front();
                                sizes.pop_front();
                                offsets.pop_front();
                                printf("Check if we can merge range at offset %d, size %d with range at offset %d, size %d\n",
                                        offset, size, offsets.front(), sizes.front());
                        }
                        enlarge_range(s, offset, size);
                        longest = longest < size ? size : longest;
                        if (size > tmp)
                        {
                                /* moved the boundaries, check them again... */
                                offsets.push_front(offset);
                                sizes.push_front(size);
                        }
                }  while (offsets.size());
                return longest;
        }
};
#endif

#if 1
class Solution {
        void enlarge_range(const char *s,
                list<uint32_t> &sizes, list<uint32_t> &offsets,
                list<uint32_t>::iterator &selfs, list<uint32_t>::iterator &selfo) {

                list<uint32_t>::iterator io, is;
                uint32_t size = *selfs;
                uint32_t offset =*selfo;
                uint32_t size0 = size-1; /* ok here since min size is 2 */

                // printf("new range('%s', %u, %u)\n", s, offset, size);
                while (size0 != size) {

                        /* enlarge the current range with surrounding parentheses */
                        while (offset && s[offset+size] &&
                                s[offset-1] == '(' and s[offset+size] == ')')
                        {
                                size += 2;
                                offset--;

                        }
                        size0 = size;
                        // printf("enlarge_surrounding('%s', %u, %u)\n",
                        //                 s, offset, size);
#if 0
                        /* merge forward */
                        io = selfo;
                        is = selfs;
                        if (io != offsets.end()) {
                                io++;
                                is++;
                                while (io != offsets.end() &&
                                                offset + size == *io) {
                                        size += *is;
                                        offsets.erase(io);
                                        offsets.erase(is);
                                }
                        }
                        printf("merge_forward('%s', %u, %u)\n",
                                        s, offset, size);
#endif

                        /* merge backwards */
                        io = selfo;
                        is = selfs;
                        if (io != offsets.begin()) {
                                io--;
                                is--;
                                // printf("merge_forwards('%s', %u, %u) check with %d, %d\n",
                                //                 s, offset, size, *io, *is);
                                while (*io + *is == offset) {
                                        size += *is;
                                        offset = *io;
                                        offsets.erase(io);
                                        sizes.erase(is);
                                        io = selfo;
                                        is = selfs;
                                        if (io != offsets.begin()) {
                                                io--;
                                                is--;
                                        }
                                }
                        }
                        // printf("merge_backwards('%s', %u, %u)\n",
                        //                 s, offset, size);
                }
                /* Commit the new size and offset */
                *selfo = offset;
                *selfs = size;
        }
public:
        int longestValidParentheses(string str)
        {
                list<uint32_t> sizes, offsets;
                uint32_t longest = 0, slen = str.length();

                if (slen < 2) return 0;

                const char *s = str.c_str();
                uint32_t offset = 0;
                while(s[offset+1])
                {
                        if (s[offset] == '(' and s[offset+1] == ')') {
                                sizes.push_back(2);
                                offsets.push_back(offset);
                                enlarge_range(s, sizes, offsets,
                                        --sizes.end(), --offsets.end());
                                offset = offsets.back() + sizes.back();
                                longest = longest < sizes.back() ? sizes.back() : longest;
                                if (offset == slen) break;
                        }
                        else offset++;
                }
                return longest;
        }
};
#endif

int run_test_case(void *s_, TestCase *tc) {
    UNUSED(s_);
    string _s = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    int result = s.longestValidParentheses(_s);

    if (result == expected) return 0;

    printf("longestValidParentheses( '%s' ) returned %d but expected %d\n",
        _s.c_str(), result, expected);
    assert(continue_on_failure);
    return 1;
}

int main(int argc, char **argv) {
    int tests_ran = 0;
    const char *tc_id = NULL;

    if (argc < 2 || argc > 3)
    {
        cerr << "Usage: " << argv[0] << " <json test file> [test case index or name]" << endl;
        cerr << "Where: [test case index or name] specifies which test to run (all by default)" <<
            endl;
        return -1;
    }

    UnitTests uts(NULL, &run_test_case, argv[1]);

    if (argc == 3) tc_id = argv[2];

    int errors_count = uts.run_test_cases(tc_id, tests_ran);
    if (errors_count == 0)
        cout << "All " << tests_ran << " test(s) succeeded!!!" << endl;
    else
        cout << errors_count << " test(s) failed over a total of " << tests_ran << endl;

    return errors_count;
}
