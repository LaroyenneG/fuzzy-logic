//
// Created by rabougris on 2/12/19.
//

#ifndef LOGIQUEFLOUE_BINARYEXPRESSIONMODEL_H
#define LOGIQUEFLOUE_BINARYEXPRESSIONMODEL_H

#include <thread_db.h>
#include "BinaryExpression.h"

namespace core {
    template<typename T>
    class BinaryExpressionModel : public BinaryExpression<T> {
    private:
        BinaryExpression<T> m_operator;
        Expression<T> left;
        Expression<T> right;
    public:
        T evaluate(void) const;

        T evaluate(Expression<T> l, Expression<T> r) const;
    };

    template<typename T>
    T BinaryExpressionModel<T>::evaluate(Expression<T> l, Expression<T> r) const {
        if (m_operator != null)
            return m_operator.evaluate(l, r);
    }

    template<typename T>
    T BinaryExpressionModel<T>::evaluate(void) const {
        if (left != null && right != null)
            return evaluate(left, right);
    }

}
#endif //LOGIQUEFLOUE_BINARYEXPRESSIONMODEL_H
