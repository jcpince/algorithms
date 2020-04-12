add_library(unittests UnitTests.cpp TestsHelper.cpp TreeNode.cpp)

add_executable(test_tree test_tree.cpp)
target_link_libraries(test_tree unittests)
