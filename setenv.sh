ALGO_ROOTDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

ALGO_BUILDDIR=${ALGO_ROOTDIR}/build

export PATH=$PATH:${ALGO_ROOTDIR}/build/bin

algo_buildexists()
{
    if [ ! -d ${ALGO_BUILDDIR} ]; then
        echo "Build directory ${ALGO_BUILDDIR} not found!"
        return 0
    fi
    return 1
}

algo_cleanbuild()
{
    algo_buildexists
    local exists=$?
    if [ "${exists}" -eq "0" ]; then
        return -1
    fi

    pushd ${ALGO_BUILDDIR} >/dev/null
    if [ -f Makefile ]; then
        make clean 2>/dev/null
    else
        echo "Makefile not found!"
    fi
    popd >/dev/null
    return 0
}

algo_cleanall()
{
    algo_buildexists
    local exists=$?
    if [ "${exists}" -eq "0" ]; then
        return -1
    fi

    pushd ${ALGO_BUILDDIR} >/dev/null
    if [ -f Makefile ]; then
        algo_cleanbuild

        rm -f cmake_install.cmake Makefile CMakeCache.txt
        rm -fr CMakeFiles
        for subdir in tools hackerrank leetcode; do
            if [ -d ${subdir} ]; then
                cd ${subdir}
                rm -f cmake_install.cmake Makefile
                rm -fr CMakeFiles
                cd ..
                rmdir ${subdir}
            fi
        done
        rmdir bin lib
    fi
    popd >/dev/null
    rmdir ${ALGO_BUILDDIR}
}

algo_rebuildall()
{
    algo_cleanall

    mkdir -p ${ALGO_BUILDDIR}
    pushd ${ALGO_BUILDDIR} >/dev/null
    cmake ..
    make -j
    popd >/dev/null
}

algo_buildall()
{
    mkdir -p ${ALGO_BUILDDIR}
    pushd ${ALGO_BUILDDIR} >/dev/null
    if [ ! -f Makefile ] ; then
        algo_rebuildall
    else
        make -j
    fi
    popd >/dev/null
}

algo_newecpp()
{
    NEWCPP=$1
    if [[ -f ${NEWCPP} ]] ; then
        echo "File ${NEWCPP} already exists!"
        return -1
    fi
    if [[ ${NEWCPP: -4} != ".cpp" ]]; then
        echo "Usage algo_newecpp <path to new file.cpp>"
        return -1
    fi
    BASEDIR=$(dirname "${NEWCPP}")
    BASEFILE=$(basename "${NEWCPP}")

    CMAKEFILE=${BASEDIR}/CMakeLists.txt
    BASEFILE="${BASEFILE%????}"
    NEWJSON="${BASEDIR}/${BASEFILE}.unittests.json"

    cat > ${NEWCPP} << EOF
#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

int run_test_case(void *_s, TestCase *tc) {
    UNUSED(_s);
    vector<int> vtree = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["tree"];
    int k = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["k"];
    bool expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    struct TreeNode tree[vtree.size()];
    bzero(tree, vtree.size()*sizeof(struct TreeNode));
    vector2tree(vtree, tree);

    Solution s;
    bool result = s.findTarget(tree, k);

    if (result == expected) return 0;

    printf("findTarget(%s, %d) returned %d but expected %d\n", array2str(vtree).c_str(), k,
        result, expected);
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
EOF

    echo >> ${CMAKEFILE}
    echo "add_executable(${BASEFILE} ${BASEFILE}.cpp)" >> ${CMAKEFILE}
    echo "target_link_libraries(${BASEFILE} unittests)" >> ${CMAKEFILE}

    if [[ -f ${NEWJSON} ]] ; then
        echo "File ${NEWJSON} already exists!"
        return 0
    fi
    cat > ${NEWJSON} << EOF
{
    "tests" :
    [
        {
            "in"        :
            {
                "tree"  : [5,3,6,2,4,-1,7],
                "k"     : 9
            },
            "expected"  : true
        }
    ]
}
EOF
}

export PATH=${ALGO_BUILDDIR}/bin:$PATH
