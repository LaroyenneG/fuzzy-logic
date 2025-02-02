#ifndef LOGIQUEFLOUE_ORTEST_H
#define LOGIQUEFLOUE_ORTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "OrMax.h"
#include "OrPlus.h"
#include "ValueModel.h"

using namespace fuzzylogic::core;
using namespace fuzzylogic::fuzzy;

class OrTest : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(OrTest);
        CPPUNIT_TEST(testOrMax);
        CPPUNIT_TEST(testOrPlus);
    CPPUNIT_TEST_SUITE_END();
public:
    void testOrMax();

    void testOrPlus();
};


#endif //LOGIQUEFLOUE_ORTEST_H