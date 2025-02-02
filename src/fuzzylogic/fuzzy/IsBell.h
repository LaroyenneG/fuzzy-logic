#ifndef LOGIQUEFLOUE_ISBELL_H
#define LOGIQUEFLOUE_ISBELL_H

#include <cmath>
#include "Is.h"

namespace fuzzylogic::fuzzy {
    template<typename T>
    class IsBell : public Is<T> {

    private:
        T min;
        T mid;
        T max;

    public:
        explicit IsBell(const T &_min, const T &_mid, const T &_max);

        T evaluate(fuzzylogic::core::Expression<T> *expression) const override;

        const T &getMin() const;

        const T &getMid() const;

        const T &getMax() const;

        void setMin(const T &_min);

        void setMid(const T &_mid);

        void setMax(const T &_max);

    };


    template<typename T>
    IsBell<T>::IsBell(const T &_min, const T &_mid, const T &_max) : min(_min), mid(_mid), max(_max) {

    }

    template<typename T>
    T IsBell<T>::evaluate(fuzzylogic::core::Expression<T> *expression) const {

        static const T ONE(1);
        static const T TWO(2);

        T value = expression->evaluate();

        return ONE / (ONE + pow(fabs((value - max) / min), (TWO * mid)));
    }

    template<typename T>
    const T &IsBell<T>::getMin() const {
        return min;
    }

    template<typename T>
    const T &IsBell<T>::getMid() const {
        return mid;
    }

    template<typename T>
    const T &IsBell<T>::getMax() const {
        return max;
    }

    template<typename T>
    void IsBell<T>::setMin(const T &_min) {
        min = _min;
    }

    template<typename T>
    void IsBell<T>::setMid(const T &_mid) {
        mid = _mid;
    }

    template<typename T>
    void IsBell<T>::setMax(const T &_max) {
        max = _max;
    }

}
#endif //LOGIQUEFLOUE_ISBELL_H
