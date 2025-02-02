
#include <IsSigmoid.h>

#include "IsTest.h"

void IsTest::testIsTriangle() {

    IsTriangle<double> isTriangle(0.1, 0.6, 0.7);
    ValueModel<double> valueModelA(0.7);
    ValueModel<double> valueModelB(0.2);

    CPPUNIT_ASSERT_EQUAL(0.1, isTriangle.getMin());
    CPPUNIT_ASSERT_EQUAL(0.6, isTriangle.getMid());
    CPPUNIT_ASSERT_EQUAL(0.7, isTriangle.getMax());

    isTriangle.setMax(0.5);
    isTriangle.setMid(0.2);
    isTriangle.setMin(0.05);

    CPPUNIT_ASSERT_EQUAL(0.05, isTriangle.getMin());
    CPPUNIT_ASSERT_EQUAL(0.2, isTriangle.getMid());
    CPPUNIT_ASSERT_EQUAL(0.5, isTriangle.getMax());

    double evaluate = isTriangle.evaluate(&valueModelA);
    double expected = 0.0;

    double evaluate1 = isTriangle.evaluate(&valueModelB);
    double expected1 = 1.0;


    CPPUNIT_ASSERT_EQUAL(round(expected1 * 1000), round(evaluate1 * 1000));
    CPPUNIT_ASSERT_EQUAL(round(expected * 1000), round(evaluate * 1000));
}

void IsTest::testIsTrapezoid() {

    IsTrapezoid<double> isTrapezoid(0.1, 0.7, 0.5, 0.5);
    ValueModel<double> valueModelA(0.7);
    ValueModel<double> valueModelB(1.2);
    ValueModel<double> valueModelC(0.3);

    CPPUNIT_ASSERT_EQUAL(0.1, isTrapezoid.getLowLeft());
    CPPUNIT_ASSERT_EQUAL(0.7, isTrapezoid.getLowRight());
    CPPUNIT_ASSERT_EQUAL(0.5, isTrapezoid.getHighLeft());
    CPPUNIT_ASSERT_EQUAL(0.5, isTrapezoid.getHighRight());

    isTrapezoid.setLowLeft(0.0);
    isTrapezoid.setLowRight(1.0);
    isTrapezoid.setHighLeft(0.6);
    isTrapezoid.setHighRight(0.7);

    CPPUNIT_ASSERT_EQUAL(0.0, isTrapezoid.getLowLeft());
    CPPUNIT_ASSERT_EQUAL(1.0, isTrapezoid.getLowRight());
    CPPUNIT_ASSERT_EQUAL(0.6, isTrapezoid.getHighLeft());
    CPPUNIT_ASSERT_EQUAL(0.7, isTrapezoid.getHighRight());

    CPPUNIT_ASSERT_EQUAL(1.0, isTrapezoid.evaluate(&valueModelA));
    CPPUNIT_ASSERT_EQUAL(0.0, isTrapezoid.evaluate(&valueModelB));

    double expected = 0.429;
    double evaluate = isTrapezoid.evaluate(&valueModelC);
    CPPUNIT_ASSERT_EQUAL(round(expected * 1000), round(evaluate * 1000));
}

void IsTest::testIsSingleton() {

    ValueModel<double> valueModelA(0.5);
    ValueModel<double> valueModelB(0.4);
    IsSingleton<double> isSingleton(0.5);

    CPPUNIT_ASSERT_EQUAL(0.5, isSingleton.getValue());
    isSingleton.setValue(0.4);
    CPPUNIT_ASSERT_EQUAL(0.4, isSingleton.getValue());

    CPPUNIT_ASSERT_EQUAL(1.0, isSingleton.evaluate(&valueModelB));
    CPPUNIT_ASSERT_EQUAL(0.0, isSingleton.evaluate(&valueModelA));

}

void IsTest::testIsRampRight() {

    IsRampRight<double> IsRampRight(0.1, 0.6, 0.7);
    ValueModel<double> valueModelA(0.01);
    ValueModel<double> valueModelB(0.7);
    ValueModel<double> valueModelC(0.3);

    CPPUNIT_ASSERT_EQUAL(0.1, IsRampRight.getMin());
    CPPUNIT_ASSERT_EQUAL(0.6, IsRampRight.getMid());
    CPPUNIT_ASSERT_EQUAL(0.7, IsRampRight.getMax());

    IsRampRight.setMax(0.5);
    IsRampRight.setMid(0.2);
    IsRampRight.setMin(0.05);

    CPPUNIT_ASSERT_EQUAL(0.05, IsRampRight.getMin());
    CPPUNIT_ASSERT_EQUAL(0.2, IsRampRight.getMid());
    CPPUNIT_ASSERT_EQUAL(0.5, IsRampRight.getMax());

    CPPUNIT_ASSERT_EQUAL(0.0, IsRampRight.evaluate(&valueModelB));
    CPPUNIT_ASSERT_EQUAL(1.0, IsRampRight.evaluate(&valueModelA));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.666666, IsRampRight.evaluate(&valueModelC), 0.000001);


}

void IsTest::testIsRampLeft() {

    IsRampLeft<double> IsRampLeft(0.2, 0.7, 0.9);

    ValueModel<double> valueModelA(0.1);
    ValueModel<double> valueModelB(0.6);
    ValueModel<double> valueModelC(0.4);

    CPPUNIT_ASSERT_EQUAL(0.2, IsRampLeft.getMin());
    CPPUNIT_ASSERT_EQUAL(0.7, IsRampLeft.getMid());
    CPPUNIT_ASSERT_EQUAL(0.9, IsRampLeft.getMax());

    IsRampLeft.setMax(0.8);
    IsRampLeft.setMid(0.5);
    IsRampLeft.setMin(0.2);

    CPPUNIT_ASSERT_EQUAL(0.2, IsRampLeft.getMin());
    CPPUNIT_ASSERT_EQUAL(0.5, IsRampLeft.getMid());
    CPPUNIT_ASSERT_EQUAL(0.8, IsRampLeft.getMax());

    CPPUNIT_ASSERT_EQUAL(0.0, IsRampLeft.evaluate(&valueModelA));
    CPPUNIT_ASSERT_EQUAL(1.0, IsRampLeft.evaluate(&valueModelB));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.666666, IsRampLeft.evaluate(&valueModelC), 0.000001);

}

void IsTest::testIsBell() {

    IsBell<double> IsBell(0.2, 0.7, 0.9);

    ValueModel valueModelA(0.05);
    ValueModel valueModelB(7.8);
    ValueModel valueModelC(10.0);

    CPPUNIT_ASSERT_EQUAL(0.2, IsBell.getMin());
    CPPUNIT_ASSERT_EQUAL(0.7, IsBell.getMid());
    CPPUNIT_ASSERT_EQUAL(0.9, IsBell.getMax());

    IsBell.setMin(2.0);
    IsBell.setMid(4.0);
    IsBell.setMax(6.0);

    CPPUNIT_ASSERT_EQUAL(2.0, IsBell.getMin());
    CPPUNIT_ASSERT_EQUAL(4.0, IsBell.getMid());
    CPPUNIT_ASSERT_EQUAL(6.0, IsBell.getMax());

    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.000162, IsBell.evaluate(&valueModelA), 0.000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.699072, IsBell.evaluate(&valueModelB), 0.000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.003891, IsBell.evaluate(&valueModelC), 0.000001);
}

void IsTest::testIsSigmoid() {

    ValueModel valueModel(2.0);

    IsSigmoid<double> isSigmoid(0.5);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5, isSigmoid.getMin(), 0.01);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.92, isSigmoid.evaluate(&valueModel), 0.01);
}

void IsTest::testIsGaussian() {
    ValueModel valueModelA(4.0);
    ValueModel valueModelB(2.0);

    IsGaussian<double> isGaussian(4.0, 2.0);

    CPPUNIT_ASSERT_EQUAL(4.0, isGaussian.getMean());
    CPPUNIT_ASSERT_EQUAL(1.0, isGaussian.evaluate(&valueModelA));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.60, isGaussian.evaluate(&valueModelB), 0.01);
}

void IsTest::testIsRangeBell() {
    ValueModel valueModelA(1.0);
    ValueModel valueModelB(2.0);
    ValueModel valueModelC(0.0);

    IsRangeBell<double> isRangeBell_lazerOne(1.0, 1.0, 0.0, 0.0, 1.0);

    IsRangeBell<double> isRangeBell_lazerTwo(1.0, 1.0, 0.0, 0.0, 1.0);

    IsRangeBell<double> isRangeBell_lazerThree(1.0, 1.0, 1.0, 0.0, 1.0);

    CPPUNIT_ASSERT_EQUAL(1.0, isRangeBell_lazerOne.getMid());

    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, isRangeBell_lazerOne.evaluate(&valueModelB), 0.01);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5, isRangeBell_lazerOne.evaluate(&valueModelA), 0.01);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, isRangeBell_lazerOne.evaluate(&valueModelC), 0.01);
}
