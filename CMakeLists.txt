cmake_minimum_required(VERSION 3.15)
project(FinalProjExamples)

# filesystem.h require C++17
set(CMAKE_CXX_STANDARD 17)

file(COPY sample_data/ DESTINATION sample_data/)

# show compiler output and enable warnings
set(CMAKE_VERBOSE_MAKEFILE ON)
add_compile_options(-Wall -Wextra -pedantic)

add_executable(test_DocParser test_DocParser.cpp DocParser.cpp porter2_stemmer.cpp)

add_executable(test_IndexHandler test_IndexHandler.cpp)

add_executable(rapidJSONExample rapidJSONExample.cpp)
add_executable(supersearch main.cpp DocParser.cpp porter2_stemmer.cpp Query.cpp)
add_executable(test_AVLTree test_AVLTree.cpp)
add_test(NAME TestAVL COMMAND test_AVLTree)
add_executable(printingAVLTree printingAVLTree.cpp)
add_executable(UITests UITests.cpp DocParser.cpp porter2_stemmer.cpp Query.cpp)
add_executable(test_QueryProcessor test_QueryProcessor.cpp Query.cpp DocParser.cpp porter2_stemmer.cpp)
#do we need DocParser.cpp and porter2 here? i think so but unsure 






# this makes sure we also link rapidjson
target_include_directories(rapidJSONExample PRIVATE rapidjson/)

set(CMAKE_VERBOSE_MAKEFILE OFF)
