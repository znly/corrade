#
#   This file is part of Corrade.
#
#   Copyright © 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016,
#               2017, 2018 Vladimír Vondruš <mosra@centrum.cz>
#
#   Permission is hereby granted, free of charge, to any person obtaining a
#   copy of this software and associated documentation files (the "Software"),
#   to deal in the Software without restriction, including without limitation
#   the rights to use, copy, modify, merge, publish, distribute, sublicense,
#   and/or sell copies of the Software, and to permit persons to whom the
#   Software is furnished to do so, subject to the following conditions:
#
#   The above copyright notice and this permission notice shall be included
#   in all copies or substantial portions of the Software.
#
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
#   DEALINGS IN THE SOFTWARE.
#

if(CORRADE_TARGET_EMSCRIPTEN OR CORRADE_TARGET_ANDROID)
    set(UTILITY_TEST_DIR ".")
    set(UTILITY_BINARY_TEST_DIR "./write")
else()
    set(UTILITY_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR})
    set(UTILITY_BINARY_TEST_DIR ${CMAKE_CURRENT_BINARY_DIR})
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/configure.h.cmake
               ${CMAKE_CURRENT_BINARY_DIR}/configure.h)

corrade_add_test(UtilityArgumentsTest ArgumentsTest.cpp LIBRARIES CorradeUtilityTestLib)
set_tests_properties(UtilityArgumentsTest
    PROPERTIES ENVIRONMENT "ARGUMENTSTEST_SIZE=1337;ARGUMENTSTEST_VERBOSE=ON;ARGUMENTSTEST_COLOR=OFF;ARGUMENTSTEST_UNICODE=hýždě")

add_library(AssertTestObjects OBJECT AssertTest.cpp)
target_include_directories(AssertTestObjects PRIVATE $<TARGET_PROPERTY:CorradeUtility,INTERFACE_INCLUDE_DIRECTORIES>)
corrade_add_test(UtilityAssertTest
    $<TARGET_OBJECTS:AssertTestObjects>
    ${PROJECT_SOURCE_DIR}/src/dummy.cpp)
# WILL_FAIL doesn't work for abort() on desktop, test this only on embedded
# then. Oh well. Also the tests could be just one executable added multiple
# times with different arguments, but corrade_add_test() doesn't support that,
# so I'm doing it at least via an OBJECTS library.
if(CORRADE_TARGET_EMSCRIPTEN OR CORRADE_TARGET_ANDROID)
    corrade_add_test(UtilityAssertTestFailAssert
        $<TARGET_OBJECTS:AssertTestObjects>
        ${PROJECT_SOURCE_DIR}/src/dummy.cpp
        ARGUMENTS --fail-on-assert true)
    set_tests_properties(UtilityAssertTestFailAssert PROPERTIES
        PASS_REGULAR_EXPRESSION "A should be zero")
    corrade_add_test(UtilityAssertTestFailConstexprAssert
        $<TARGET_OBJECTS:AssertTestObjects>
        ${PROJECT_SOURCE_DIR}/src/dummy.cpp
        ARGUMENTS --fail-on-constexpr-assert true)
    set_tests_properties(UtilityAssertTestFailConstexprAssert PROPERTIES
        PASS_REGULAR_EXPRESSION "b can't be zero")
    corrade_add_test(UtilityAssertTestFailInternalAssert
        $<TARGET_OBJECTS:AssertTestObjects>
        ${PROJECT_SOURCE_DIR}/src/dummy.cpp
        ARGUMENTS --fail-on-internal-assert true)
    set_tests_properties(UtilityAssertTestFailInternalAssert PROPERTIES
        PASS_REGULAR_EXPRESSION "Assertion b && !_failInternalAssert failed in ")
    corrade_add_test(UtilityAssertTestFailInternalConstexprAssert
        $<TARGET_OBJECTS:AssertTestObjects>
        ${PROJECT_SOURCE_DIR}/src/dummy.cpp
        ARGUMENTS --fail-on-internal-constexpr-assert true)
    set_tests_properties(UtilityAssertTestFailInternalConstexprAssert PROPERTIES
        PASS_REGULAR_EXPRESSION "Assertion b failed in ")
    corrade_add_test(UtilityAssertTestFailAssertOutput
        $<TARGET_OBJECTS:AssertTestObjects>
        ${PROJECT_SOURCE_DIR}/src/dummy.cpp
        ARGUMENTS --fail-on-assert-output true)
    set_tests_properties(UtilityAssertTestFailAssertOutput PROPERTIES
        PASS_REGULAR_EXPRESSION "foo\\(\\) should succeed")
    corrade_add_test(UtilityAssertTestFailInternalAssertOutput
        $<TARGET_OBJECTS:AssertTestObjects>
        ${PROJECT_SOURCE_DIR}/src/dummy.cpp
        ARGUMENTS --fail-on-internal-assert-output true)
    set_tests_properties(UtilityAssertTestFailInternalAssertOutput PROPERTIES
        PASS_REGULAR_EXPRESSION "Assertion foo\\(\\) && !_failInternalAssertOutput failed in ")
    corrade_add_test(UtilityAssertTestFailAssertUnreachable
        $<TARGET_OBJECTS:AssertTestObjects>
        ${PROJECT_SOURCE_DIR}/src/dummy.cpp
        ARGUMENTS --fail-on-assert-unreachable true)
    set_tests_properties(UtilityAssertTestFailAssertUnreachable PROPERTIES
        PASS_REGULAR_EXPRESSION "Reached unreachable code in ")
endif()

corrade_add_test(UtilityAssertDisabledTest AssertDisabledTest.cpp)
corrade_add_test(UtilityAssertGracefulTest AssertGracefulTest.cpp)
corrade_add_test(UtilityEndianTest EndianTest.cpp)
corrade_add_test(UtilityMurmurHash2Test MurmurHash2Test.cpp)
corrade_add_test(UtilityConfigurationTest ConfigurationTest.cpp
    LIBRARIES CorradeUtilityTestLib
    FILES
        ConfigurationTestFiles/bom.conf
        ConfigurationTestFiles/comments.conf
        ConfigurationTestFiles/comments-saved.conf
        ConfigurationTestFiles/eol-mixed.conf
        ConfigurationTestFiles/eol-unix.conf
        ConfigurationTestFiles/eol-windows.conf
        ConfigurationTestFiles/hierarchic.conf
        ConfigurationTestFiles/hierarchic-empty-group.conf
        ConfigurationTestFiles/hierarchic-empty-subgroup.conf
        ConfigurationTestFiles/hierarchic-missing-bracket.conf
        ConfigurationTestFiles/hierarchic-modified.conf
        ConfigurationTestFiles/hierarchic-shortcuts.conf
        ConfigurationTestFiles/hierarchic-shortcuts-modified.conf
        ConfigurationTestFiles/hýždě.conf
        ConfigurationTestFiles/missing-equals.conf
        ConfigurationTestFiles/missing-quote.conf
        ConfigurationTestFiles/missing-multiline-quote.conf
        ConfigurationTestFiles/multiLine.conf
        ConfigurationTestFiles/multiLine-crlf.conf
        ConfigurationTestFiles/multiLine-crlf-saved.conf
        ConfigurationTestFiles/multiLine-saved.conf
        ConfigurationTestFiles/parse.conf
        ConfigurationTestFiles/parse-modified.conf
        ConfigurationTestFiles/whitespaces.conf
        ConfigurationTestFiles/whitespaces-saved.conf)
target_include_directories(UtilityConfigurationTest PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
corrade_add_test(UtilityConfigurationValueTest ConfigurationValueTest.cpp)
corrade_add_test(UtilityDebugTest DebugTest.cpp)

# It should return with a non-zero exit code
corrade_add_test(UtilityFatalTest FatalTest.cpp)
set_tests_properties(UtilityFatalTest PROPERTIES WILL_FAIL ON)

set(UtilityDirectoryTest_SRCS DirectoryTest.cpp)
if(CORRADE_TARGET_IOS)
    set(UtilityDirectoryTest_RESOURCES
        DirectoryTestFiles)
    set_source_files_properties(DirectoryTestFiles PROPERTIES
        MACOSX_PACKAGE_LOCATION Resources)
    list(APPEND UtilityDirectoryTest_SRCS DirectoryTestFiles)
endif()
corrade_add_test(UtilityDirectoryTest ${UtilityDirectoryTest_SRCS}
    FILES
        DirectoryTestFiles/dir/dummy
        DirectoryTestFiles/file
        DirectoryTestFilesUtf8/šňůra/dummy
        DirectoryTestFilesUtf8/hýždě)
target_include_directories(UtilityDirectoryTest PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

corrade_add_test(UtilityHashDigestTest HashDigestTest.cpp)
corrade_add_test(UtilityMacrosTest MacrosTest.cpp)
corrade_add_test(UtilitySha1Test Sha1Test.cpp)
corrade_add_test(UtilityStringTest StringTest.cpp LIBRARIES CorradeUtilityTestLib)
corrade_add_test(UtilitySystemTest SystemTest.cpp)
corrade_add_test(UtilityTypeTraitsTest TypeTraitsTest.cpp)
corrade_add_test(UtilityUnicodeTest UnicodeTest.cpp LIBRARIES CorradeUtilityTestLib)

# Compiled-in resource test
corrade_add_resource(ResourceTestData ResourceTestFiles/resources.conf)
corrade_add_resource(ResourceTestEmptyFileData ResourceTestFiles/resources-empty-file.conf)
corrade_add_resource(ResourceTestNothingData ResourceTestFiles/resources-nothing.conf)
corrade_add_test(UtilityResourceTest
    ResourceTest.cpp
    ${ResourceTestData}
    ${ResourceTestEmptyFileData}
    ${ResourceTestNothingData}
    LIBRARIES CorradeUtilityTestLib
    FILES
        ResourceTestFiles/compiled.cpp
        ResourceTestFiles/compiled-empty.cpp
        ResourceTestFiles/compiled-nothing.cpp
        ResourceTestFiles/compiled-unicode.cpp
        ResourceTestFiles/consequence.bin
        ResourceTestFiles/consequence2.txt
        ResourceTestFiles/empty.bin
        ResourceTestFiles/hýždě.bin
        ResourceTestFiles/hýždě.conf
        ResourceTestFiles/predisposition.bin
        ResourceTestFiles/predisposition2.txt
        ResourceTestFiles/resources.conf
        ResourceTestFiles/resources-empty-alias.conf
        ResourceTestFiles/resources-empty-file.conf
        ResourceTestFiles/resources-empty-filename.conf
        ResourceTestFiles/resources-empty-group.conf
        ResourceTestFiles/resources-no-group.conf
        ResourceTestFiles/resources-nonexistent.conf
        ResourceTestFiles/resources-nothing.conf
        ResourceTestFiles/resources-overriden.conf
        ResourceTestFiles/resources-overriden-different.conf
        ResourceTestFiles/resources-overriden-none.conf
        ResourceTestFiles/resources-overriden-nonexistent-file.conf)
target_include_directories(UtilityResourceTest PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

# Static lib resource test
add_library(ResourceTestDataLib STATIC ${ResourceTestData})
target_link_libraries(ResourceTestDataLib CorradeUtility)
corrade_add_test(UtilityResourceStaticTest ResourceStaticTest.cpp
    LIBRARIES ResourceTestDataLib
    FILES
        ResourceTestFiles/consequence.bin
        ResourceTestFiles/predisposition.bin)
target_include_directories(UtilityResourceStaticTest PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

set_target_properties(
    UtilityArgumentsTest
    UtilityEndianTest
    UtilityMurmurHash2Test
    UtilityConfigurationTest
    UtilityConfigurationValueTest
    UtilityDebugTest
    UtilityFatalTest
    UtilityDirectoryTest
    UtilityHashDigestTest
    UtilityMacrosTest
    UtilityResourceTest
    UtilityResourceStaticTest
    UtilitySha1Test
    UtilityStringTest
    UtilitySystemTest
    UtilityTypeTraitsTest
    UtilityUnicodeTest

    ResourceTestDataLib
    ResourceTestData-dependencies
    ResourceTestEmptyFileData-dependencies
    ResourceTestNothingData-dependencies
    PROPERTIES FOLDER "Corrade/Utility/Test")
