#ifndef LOGIQUEFLOUE_ANDMIN_H
#define LOGIQUEFLOUE_ANDMIN_H

#include "And.h"
#include "Expression.h"

namespace fuzzylogic::fuzzy {
    template<typename T>
    class AndMin : public And<T> {

    public:
        T evaluate(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) const override;
    };

    template<typename T>
    T AndMin<T>::evaluate(fuzzylogic::core::Expression<T> *left, fuzzylogic::core::Expression<T> *right) const {

        T l = left->evaluate();
        T r = right->evaluate();

        return (l <= r) ? l : r;
    }
}

#endif //LOGIQUEFLOUE_ANDMIN_H
