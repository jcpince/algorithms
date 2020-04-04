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

static int global_index = 0;

struct fsm_state;

typedef struct fsm_transition {
	struct fsm_state *next;
	char c;
	bool is_any;
	uint8_t cost;

	fsm_transition(const char _c, const uint8_t _cost) {
		c = _c;
		is_any = (c == '.');
		cost = _cost;
	}
	fsm_transition(const uint8_t _cost) {
		is_any = true;
		cost = _cost;
	}
	bool matches(const char _c) {
		bool ret = is_any || (_c == c);
		// printf("transition (c:%c, is_any:%d, cost:%d) matches returns %d for %c\n",
		// 	c, is_any, cost, ret, _c);
		return ret;
	}
} fsm_transition_t;

typedef struct fsm_state {
	fsm_transition_t *stay_trans;
	fsm_transition_t *move_trans;
	int index;
	bool final;
	char name[32];

	fsm_state(bool _final = false) {
		stay_trans = move_trans = NULL;
		index = _final ? -1 : global_index++;
		final = _final;
		set_name();
	}

	void set_index(int _index) {
		index = _index;
		set_name();
	}

	void set_name() {
		if (index == 0)
			snprintf(name, 32, "INITIAL");
		else if (final)
			snprintf(name, 32, "FINAL");
		else
			snprintf(name, 32, "S%d", index);
	}
} fsm_state_t;

class FSM {
	fsm_state_t _initial_state;
	list<fsm_state_t*> *states;
	const string re;

	void add_state(fsm_state_t *state) {
		states->push_back(state);
	}

	void add_transition(char c, int cost, fsm_state_t *start_state,
				fsm_state_t *next_state) {
		fsm_transition_t *t = new fsm_transition_t(c, cost);
		if (start_state != next_state) {
			start_state->move_trans = t;
			start_state->move_trans->next = next_state;
		} else {
			start_state->stay_trans = t;
		}
	}

	void add_any_transition(int cost, fsm_state_t *start_state,
				fsm_state_t *next_state) {
		fsm_transition_t *t = new fsm_transition_t(cost);
		if (start_state != next_state) {
			start_state->move_trans = t;
			start_state->move_trans->next = next_state;
		} else {
			start_state->stay_trans = t;
		}
	}

	bool buildFSM() {
		fsm_state_t *state = &_initial_state, *next_state;
		char c = '\0';
		//printf("Building FSM...\n");

		for (const char &nextc : re) {
			/* Initial value */
			if (c == '\0' || c == '*') {
				c = nextc;
				continue;
			}

			//printf("New character %c\n", c);
			if (nextc == '*' && c == '*') {
				/* Invalid combo '**' */
				return false;
			}

			if (nextc == '*') {
				//printf("%c* combo...\n", c);
				add_transition(c, 1, state, state);
				next_state = new fsm_state_t();
				add_state(next_state);
				add_any_transition(0, state, next_state);
				state = next_state;
			} else {
				//printf("%c simple...\n", c);
				next_state = new fsm_state_t();
				add_state(next_state);
				add_transition(c, 1, state, next_state);
				state = next_state;
			}

			c = nextc;
		}
		if (c != '*') {
			//printf("last %c simple...\n", c);
			next_state = new fsm_state_t();
			add_state(next_state);
			add_transition(c, 1, state, next_state);
			state = next_state;
		}

		state->final = true;
		state->set_name();
		return true;
	}
	int nb_states() { return 1 + states->size(); }
public:
	FSM(const string &re) : re(re) {
		_initial_state.set_index(0);
		global_index = 1;
		states = new list<fsm_state_t *>();
		assert(buildFSM());
	}
	~FSM() {
		while(states->size()) {
			fsm_state_t *state = states->back();
			states->pop_back();
			if (state->move_trans) delete state->move_trans;
			if (state->stay_trans) delete state->stay_trans;
			delete state;
		}
		delete states;
		if (_initial_state.move_trans) delete _initial_state.move_trans;
		if (_initial_state.stay_trans) delete _initial_state.stay_trans;
	}

	void dump() {
		printf("fsm for \"%s\" has %d states\n", re.c_str(),
			nb_states());
		fsm_state_t *state = &_initial_state;
		while (state) {
			printf("%s", state->name);
			if (state->stay_trans)
				printf(" (%c -%d> self)",
					state->stay_trans->c,
					state->stay_trans->cost);
			if (state->move_trans) {
				if (state->move_trans->is_any)
					printf(" (any -%d> %s)",
						state->move_trans->cost,
						state->move_trans->next->name);
				else if (state->final)
					printf(" FINAL");
				else
					printf(" (%c -%d> %s)",
						state->move_trans->c,
						state->move_trans->cost,
						state->move_trans->next->name);
			}
			printf("\n");
			if (!state->move_trans) {
				assert(state->final);
				break;
			}
			state = state->move_trans->next;
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

		printf("Exploring state %s, index = %d\n", state->name, idx);

		if ((size_t)idx == s.length()) {
			while (!state->final &&
				state->move_trans->is_any &&
					state->move_trans->cost == 0) {
				state = state->move_trans->next;
			}
			return state->final;
		}

		const char c = s[idx];
		if (state->stay_trans && state->stay_trans->matches(c) &&
				matches(s, state, idx+state->stay_trans->cost)) {
			return true;
		} else if (state->move_trans && state->move_trans->matches(c) &&
				matches(s, state->move_trans->next,
						idx+state->move_trans->cost)) {
			return true;
		}
		/* no move */
		return false;
	}
};

class Solution {
public:
	bool isMatch(const string &s, const string &re) {
		if (s == re) return true;
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
