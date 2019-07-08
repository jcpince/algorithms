#include "UnitTests.h"

UnitTests::UnitTests(void *classUnderTest, testcase_runner tc_runner) :
    classUnderTest(classUnderTest), tc_runner(tc_runner)
{}

UnitTests::UnitTests(void *classUnderTest, testcase_runner tc_runner, const char *filename) :
    classUnderTest(classUnderTest), tc_runner(tc_runner)
{
    if (!tc_runner) throw invalid_argument("Cannot create a UnitTests instance with no test runner");
    openFile(filename);
}

UnitTests::UnitTests(void *classUnderTest, testcase_runner tc_runner, const string &filename) :
    classUnderTest(classUnderTest), tc_runner(tc_runner)
{
    if (!tc_runner) throw invalid_argument("Cannot create a UnitTests instance with no test runner");
    openFile(filename.c_str());
}

void UnitTests::openFile(const char *filename)
{
    if (!filename || !strlen(filename))
        throw invalid_argument("Cannot create a UnitTests instance with an empty filename");
    ifstream f(filename);
    f >> alltests;
    f.close();

    if (alltests[JSON_TESTS_SECTIONNAME].size() == 0)
        throw invalid_argument((string)"No section " + JSON_TESTS_SECTIONNAME + " found in " +
            filename);
}

TestCase *UnitTests::getTestCase(int index)
{
    if (index >= (int)alltests[JSON_TESTS_SECTIONNAME].size()) return NULL;

    TestCase *tc = new TestCase();
    if (alltests[JSON_TESTS_SECTIONNAME][index][JSON_TEST_CASE_NAME_FIELDNAME].size() != 0)
        tc->name = alltests[JSON_TESTS_SECTIONNAME][index][JSON_TEST_CASE_NAME_FIELDNAME].size();
    else
        tc->name = "";

    tc->test_case = alltests[JSON_TESTS_SECTIONNAME][index];
    tc->index = index;
    return tc;
}

TestCase *UnitTests::getTestCase(const char *name)
{
    if (!name) return NULL;
    int index= 0;
    for (json tc_json : alltests[JSON_TESTS_SECTIONNAME])
    {
        if (tc_json[JSON_TEST_CASE_NAME_FIELDNAME].size() == 0) continue;
        string tc_name = tc_json[JSON_TEST_CASE_NAME_FIELDNAME];
        if (tc_name == name)
        {
            TestCase *tc = new TestCase();
            tc->name = tc_name;
            tc->test_case = tc_json;
            tc->index = index;
            return tc;
        }
        index++;
    }
    return NULL;
}

TestCase *UnitTests::getTestCase(const string &name)
{
    return getTestCase(name.c_str());
}

int UnitTests::run_single_test_case(const char *tc_id)
{
    const char *tc_name = NULL;
    char *pend;
    int tc_index = strtol(tc_id, &pend, 10);
    TestCase *tc;
    if (strlen(pend))
    {
        tc_index = -1;
        tc_name = tc_id;
        tc = getTestCase(tc_name);
        if (!tc)
            throw invalid_argument((string)"Test named " + tc_name + " not found!");
    }
    else
    {
        tc = getTestCase(tc_index);
        if (!tc)
            throw invalid_argument("Test[" + to_string(tc_index) + "] not found!");
    }
    int res = tc_runner(classUnderTest, tc);
    delete tc;
    return res;
}

int UnitTests::run_all_test_cases()
{
    int tests_count = getTestsCount();
    int tc_index = 0, errors_count = 0;

    while (tests_count--)
    {
        TestCase *tc = getTestCase(tc_index++);
        if (!tc)
            throw invalid_argument("Test[" + to_string(tc_index-1) + "] not found!");
        errors_count += tc_runner(classUnderTest, tc);
        delete tc;
    }

    return errors_count;
}

int UnitTests::run_test_cases(const char *tc_id, int &tests_ran)
{
    /* tc_id can be NULL, an test case index or name */
    tests_ran = 1;
    if (tc_id) return run_single_test_case(tc_id);

    tests_ran = getTestsCount();
    return run_all_test_cases();
}
