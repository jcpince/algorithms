#ifndef __UNITTESTS__
#define __UNITTESTS__

#include <stdexcept>
#include <fstream>
#include <string>
#include <vector>

#include <json/json.hpp>

#define JSON_TESTS_SECTIONNAME              "tests"
#define JSON_TEST_CASE_NAME_FIELDNAME       "name"
#define JSON_TEST_CASE_IN_FIELDNAME         "in"
#define JSON_TEST_CASE_EXPECTED_FIELDNAME   "expected"

using namespace std;
using json = nlohmann::json;

class TestCase
{
public:
    json test_case;
    string name;
    int index;
};

typedef int (*testcase_runner)(void *classUnderTest, TestCase *tc);

class UnitTests
{
private:
    void openFile(const char *filename);

    int run_single_test_case(const char *tc_id);
    int run_all_test_cases();

    json alltests;
    void *classUnderTest;
    testcase_runner tc_runner;

public:
    UnitTests(void *classUnderTest, testcase_runner tc_runner);
    UnitTests(void *classUnderTest, testcase_runner tc_runner, const char *filename);
    UnitTests(void *classUnderTest, testcase_runner tc_runner, const string &filename);

    int getTestsCount() { return alltests[JSON_TESTS_SECTIONNAME].size(); }

    TestCase *getTestCase(int index);
    TestCase *getTestCase(const char *name);
    TestCase *getTestCase(const string &name);

    int run_test_cases(const char *tc_id, int &tests_ran);

    friend ifstream& operator<< (UnitTests &ut, ifstream& in) {
        in >> ut.alltests;

        /* Make sure that all the test cases have name, input anbd expected */
        if (ut.alltests[JSON_TESTS_SECTIONNAME].size() == 0)
            throw invalid_argument((string)"No section \"" + JSON_TESTS_SECTIONNAME + "\" defined.");

        int tc_idx = 0;
        for (json tc : ut.alltests[JSON_TESTS_SECTIONNAME])
        {
            string tc_name = "";
            if (tc[JSON_TEST_CASE_NAME_FIELDNAME].size() != 0)
                tc_name = tc[JSON_TEST_CASE_NAME_FIELDNAME];

            if (tc[JSON_TEST_CASE_IN_FIELDNAME].size() == 0)
                throw invalid_argument((string)"Testcase[" + to_string(tc_idx) + "] (name: \"" +
                    tc_name + "\"): No field \"" + JSON_TEST_CASE_IN_FIELDNAME + "\" defined.");

            if (tc[JSON_TEST_CASE_EXPECTED_FIELDNAME].size() == 0)
                throw invalid_argument((string)"Testcase[" + to_string(tc_idx) + "] (name: \"" +
                    tc_name + "\"): No field \"" + JSON_TEST_CASE_EXPECTED_FIELDNAME +
                    "\" defined.");

            tc_idx++;
        }
        return in;
    }
};

#endif /* __UNITTESTS__ */
