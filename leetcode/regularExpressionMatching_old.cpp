/*
10. Regular Expression Matching
Hard

Given an input string (s) and a pattern (p), implement regular expression
matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

Note:

	s could be empty and contains only lowercase letters a-z.
	p could be empty and contains only lowercase letters a-z, and
		characters like . or *.

Example 1:

Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".

Example 2:

Input:
s = "aa"
p = "a*"
Output: true
Explanation: '*' means zero or more of the preceding element, 'a'. Therefore,
by repeating 'a' once, it becomes "aa".

Example 3:

Input:
s = "ab"
p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".

Example 4:

Input:
s = "aab"
p = "c*a*b"
Output: true
Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore,
it matches "aab".

Example 5:

Input:
s = "mississippi"
p = "mis*is*p*."
Output: false

*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

#define UNDEFCHAR	((char)-1)
#define EOSCHAR		((char)-2)
#define charisset(c)	(c != UNDEFCHAR)

static int global_index = 0;

typedef struct fsm_state {
	char stay_char;
	char move_char;
	int _index;
	struct fsm_state *next;
	char name[32];

	fsm_state(bool final = false) {
		stay_char = move_char = UNDEFCHAR;
		next = NULL;
		_index = final ? -1 : global_index++;
		if (!final)
			snprintf(name, 32, "S%d", _index);
		else snprintf(name, 32, "FINAL");
	}

	void set_index(int index) {
		_index = index;
		if (_index)
			snprintf(name, 32, "S%d", _index);
		else snprintf(name, 32, "INITIAL");
	}
} fsm_state_t;

class FSM {
	fsm_state_t _initial_state;
	fsm_state_t _final_state = fsm_state_t(true);
	list<fsm_state_t*> *_states;
	const string re;

	void add_state(fsm_state_t *state) {
		_states->push_back(state);
	}

	void add_transition(char c, fsm_state_t *start_state,
				fsm_state_t *next_state) {
		if (start_state != next_state) {
			//assert(!charisset(start_state->move_char));
			start_state->move_char = c;
			start_state->next = next_state;
		} else {
			//assert(!charisset(start_state->stay_char));
			start_state->stay_char = c;
		}
	}

	void buildFSM() {
		fsm_state_t *state = &_initial_state, *next_state;
		char c = '\0';

		for (const char &nextc : re) {
			/* Initial value */
			if (c == '\0' || c == '*') {
				c = nextc;
				continue;
			}

			//printf("New character %c\n", nextc);
			if (nextc == '*' && c == '*') {
				/* Invalid combo '**' */
				_initial_state.next = NULL;
				return;
			}

			if (nextc == '*') {
				add_transition(c, state, state);
				if (c != '.') {
					next_state = new fsm_state_t();
					add_state(next_state);
					add_transition('.', state, next_state);
					state->next = next_state;
					state = next_state;
				}
			} else {
				next_state = new fsm_state_t();
				add_state(next_state);
				add_transition(c, state, next_state);
				state = next_state;
			}

			c = nextc;
		}
		if (c != '*') {
			next_state = new fsm_state_t();
			add_state(next_state);
			add_transition(c, state, next_state);
			state = next_state;
		}

		/* final transition */
		add_transition(EOSCHAR, state, &_final_state);
	}
	int nb_states() { return 2 + _states->size(); }
public:
	FSM(const string &re) : re(re) {
		_initial_state.set_index(0);
		global_index = 1;
		_states = new list<fsm_state_t *>();
		buildFSM();
	}
	~FSM() {
		while(_states->size()) {
			fsm_state_t *state = _states->back();
			_states->pop_back();
			delete state;
		}
		delete _states;
	}

	void dump() {
		printf("fsm for \"%s\" has %d states\n", re.c_str(),
			nb_states());
		fsm_state_t *state = &_initial_state;
		while (state->next) {
			printf("%s", state->name);
			if (charisset(state->stay_char))
				printf(" (%c -> self)", state->stay_char);
			if (charisset(state->move_char)) {
				if (charisset(state->stay_char))
					printf(" (any -> %s)", state->next->name);
				else if (state->move_char == EOSCHAR)
					printf(" (eos -> FINAL)");
				else
					printf(" (%c -> %s)", state->move_char,
						state->next->name);
			}
			printf("\n");
			if (!state->next)
				assert(state->move_char == EOSCHAR &&
					state == &_final_state);
			state = state->next;
		}
	}

	bool matches(const string &s, const fsm_state_t *state = NULL,
			int idx = 0) {

		if (state == NULL) {
			state = &_initial_state;
			printf("Parsing \"%s\" with re \"%s\"\n", s.c_str(),
				re.c_str());
			dump();
		}

		printf("Exploring state %s, index = %d\n",\
			state->name, idx);

		if ((size_t)idx == s.length()) {
			if (state->move_char == '.')
				return matches(s, state->next, idx);
			else return state->move_char == EOSCHAR;
		}

		const char c = s[idx];
		if (c == state->stay_char && state->move_char == '.') {
			return matches(s, state, idx+1) || matches(s, state->next, idx);
		} else if (c == state->move_char || state->move_char == '.') {
			return matches(s, state->next, idx+1);
		}
		/* no move */
		return false;
	}
};

class Solution {
public:
	bool isMatch(const string &s, const string &re) {
		bool result;
		FSM *fsm = new FSM(re);
		result = fsm->matches(s);
		delete fsm;
		return result;
	}
};

int run_test_case(void *_s, TestCase *tc) {
	UNUSED(_s);
	string str = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["str"];
	string pattern = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["pattern"];
	bool expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

	Solution s;
	bool result = s.isMatch(str, pattern);

	if (result == expected) return 0;

	printf("isMatch(%s, %s) returned %d but expected %d\n", str.c_str(),
		pattern.c_str(), result, expected);
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
