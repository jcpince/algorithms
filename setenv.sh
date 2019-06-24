ALGO_ROOTDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

ALGO_BUILDDIR=${ALGO_ROOTDIR}/build

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

export PATH=${ALGO_BUILDDIR}/bin:$PATH
