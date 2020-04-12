#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class MinStack {
        struct stack_elt {
                struct stack_elt *next;
                int val;
                int minval;
                stack_elt(int val) : next(NULL), val(val), minval(0) {}
        };
        struct stack_elt *_top;

public:
        /** initialize your data structure here. */
        MinStack() {
                //printf("%s: reset it all\n", __func__);
                _top = NULL;
        }
        ~MinStack() {
                struct stack_elt *tmp = _top;
                while(tmp) {
                        struct stack_elt *bk = tmp->next;
                        //printf("%s: delete %p\n", __func__, (void*)tmp);
                        delete tmp;
                        tmp = bk;
                }
        }

        void push(int x) {
                struct stack_elt *newtop = new stack_elt(x);
                //printf("%s: newtop is %p\n", __func__, (void*)newtop);
                newtop->next = _top;
                newtop->minval = _top ? (_top->minval < x ? _top->minval : x) : x;
                _top = newtop;
        }

        void pop() {
                if (!_top) return;
                struct stack_elt *oldtop = _top;
                _top = _top->next;
                //printf("%s: pop %p\n", __func__, (void*)oldtop);
                delete(oldtop);
        }

        int top() {
                return _top->val;
        }

        int getMin() {
                assert(_top);
                return _top->minval;
        }
};

int run_test_case(void *_s, TestCase *tc) {
        UNUSED(_s);
        vector<string> ops = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["ops"];
        vector<vector<int>> args = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["args"];
        vector<vector<int>> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        MinStack *s = NULL;
        vector<vector<int>> result;
        int idx = 0;
        for (string op : ops) {
                vector<int> op_args = args[idx++];
                if (op == "MinStack") {
                        if (s) delete s;
                        s = new MinStack();
                        result.push_back({});
                } else if (op == "push") {
                        s->push(op_args[0]);
                        result.push_back({});
                } else if (op == "pop") {
                        s->pop();
                        result.push_back({});
                } else if (op == "top") {
                        int v = s->top();
                        result.push_back({v});
                } else if (op == "getMin") {
                        int v = s->getMin();
                        result.push_back({v});
                } else {
                        printf("Unknown op %s\n", op.c_str());
                        abort();
                }
        }
        if (s) delete s;

        if (result == expected) return 0;

        printf("findTarget(%s, %s) returned %s but expected %s\n",
                array2str(ops).c_str(), array2str(args).c_str(),
                array2str(result).c_str(), array2str(expected).c_str());
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
