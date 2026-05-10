/*
    baseclasses2
    https://github.com/dblock/baseclasses2
*/

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestResult.h>

#include "string_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(StringConstructorTest);
CPPUNIT_TEST_SUITE_REGISTRATION(StringComparisonTest);
CPPUNIT_TEST_SUITE_REGISTRATION(StringCaseTest);
CPPUNIT_TEST_SUITE_REGISTRATION(StringTrimTest);
CPPUNIT_TEST_SUITE_REGISTRATION(StringSearchTest);
CPPUNIT_TEST_SUITE_REGISTRATION(StringSubstringTest);
CPPUNIT_TEST_SUITE_REGISTRATION(StringMutationTest);
CPPUNIT_TEST_SUITE_REGISTRATION(StringNumericTest);
CPPUNIT_TEST_SUITE_REGISTRATION(StringMiscTest);

int main() {
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry& registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());

    CppUnit::BriefTestProgressListener listener;
    runner.eventManager().addListener(&listener);

    return runner.run() ? 0 : 1;
}
