#include "AndTest.h"

void AndTest::testAndMin() {

    ValueModel<double> valueModelA(0.5);
    ValueModel<double> valueModelB(0.7);

    AndMin<double> andMin;

    CPPUNIT_ASSERT_EQUAL(0.5, andMin.evaluate(&valueModelA, &valueModelB));
}

void AndTest::testAndMult() {

    ValueModel<double> valueModelA(0.5);
    ValueModel<double> valueModelB(0.7);

    AndMult<double> andMult;

    CPPUNIT_ASSERT_EQUAL(0.35, andMult.evaluate(&valueModelA, &valueModelB));

}
