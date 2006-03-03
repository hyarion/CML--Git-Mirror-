/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Defines the various combinations of matrix expressions.
 *
 * Create unary and binary operators with macros.  The available combinations
 * are:
 *
 * Unary expressions:
 *
 * op Matrix -> Matrix
 * op MatXpr -> Matrix
 *
 * Binary expressions:
 *
 * Matrix op Matrix -> Matrix
 * MatXpr op Matrix -> MatXpr
 * Matrix op MatXpr -> MatXpr
 * MatXpr op MatXpr -> MatXpr
 *
 * Matrix op Scalar -> Matrix
 * Scalar op Matrix -> Matrix
 * MatXpr op Scalar -> MatXpr
 * Scalar op MatXpr -> MatXpr
 *
 * All of the generator functions compress the expression tree by hoisting
 * subexpressions into the containing expression.  This has the effect of
 * forcing only the root node of the expression tree to be a MatrixXpr.
 * Every other node is a Unary or BinaryMatrixOp.
 */
#ifndef matop_macros_h
#define matop_macros_h

#include <cml/et/scalar_ops.h>
#include <cml/et/matrix_expr.h>

/** Declare a unary operator taking a matrix operand. */
#define CML_MAT_UNIOP(_op_, _OpT_)                                       \
template<typename E, class AT>                                           \
inline et::MatrixXpr<                                                    \
    et::UnaryMatrixOp< matrix<E,AT>, _OpT_ <E> >                         \
>                                                                        \
                                                                         \
_op_ (const matrix<E,AT>& arg)                                           \
{                                                                        \
    typedef et::UnaryMatrixOp<                                           \
            matrix<E,AT>, _OpT_ <E>                                      \
        > ExprT;                                                         \
    return et::MatrixXpr<ExprT>(ExprT(arg));                             \
}

/** Declare a unary operator taking a et::MatrixXpr operand. */
#define CML_MATXPR_UNIOP(_op_, _OpT_)                                    \
template<class XprT>                                                     \
inline et::MatrixXpr<                                                    \
    et::UnaryMatrixOp<XprT, _OpT_<typename XprT::value_type> >           \
>                                                                        \
                                                                         \
_op_ (const et::MatrixXpr<XprT>& arg)                                    \
{                                                                        \
    typedef et::UnaryMatrixOp<                                           \
        XprT, _OpT_<typename XprT::value_type>                           \
        > ExprT;                                                         \
    return et::MatrixXpr<ExprT>(ExprT(arg.expression()));                \
}

/** Declare an operator taking two matrix operands. */
#define CML_MAT_MAT_BINOP(_op_, _OpT_)                                   \
template<typename E1, class AT1, typename E2, class AT2>                 \
inline et::MatrixXpr<                                                    \
    et::BinaryMatrixOp<                                                  \
        matrix<E1,AT1>, matrix<E2,AT2>, _OpT_<E1,E2> >                   \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const matrix<E1,AT1>& left,                                      \
        const matrix<E2,AT2>& right)                                     \
{                                                                        \
    typedef et::BinaryMatrixOp<                                          \
            matrix<E1,AT1>, matrix<E2,AT2>, _OpT_<E1,E2>                 \
        > ExprT;                                                         \
    return et::MatrixXpr<ExprT>(ExprT(left,right));                      \
}

/** Declare an operator taking a matrix and a et::MatrixXpr. */
#define CML_MAT_MATXPR_BINOP(_op_, _OpT_)                                \
template<typename E, class AT, class XprT>                               \
inline et::MatrixXpr<                                                    \
    et::BinaryMatrixOp<                                                  \
        matrix<E,AT>, XprT, _OpT_ <E, typename XprT::value_type>         \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const matrix<E,AT>& left,                                        \
        const et::MatrixXpr<XprT>& right)                                \
{                                                                        \
    typedef et::BinaryMatrixOp<                                          \
            matrix<E,AT>, XprT,                                          \
            _OpT_ <E, typename XprT::value_type>                         \
        > ExprT;                                                         \
    return et::MatrixXpr<ExprT>(ExprT(left,right.expression()));         \
}

/** Declare an operator taking a et::MatrixXpr and a matrix. */
#define CML_MATXPR_MAT_BINOP(_op_, _OpT_)                                \
template<class XprT, typename E, class AT>                               \
inline et::MatrixXpr<                                                    \
    et::BinaryMatrixOp<                                                  \
        XprT, matrix<E,AT>, _OpT_ <typename XprT::value_type, E>         \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const et::MatrixXpr<XprT>& left,                                 \
        const matrix<E,AT>& right)                                       \
{                                                                        \
    typedef et::BinaryMatrixOp<                                          \
            XprT, matrix<E,AT>,                                          \
            _OpT_ <typename XprT::value_type, E>                         \
        > ExprT;                                                         \
    return et::MatrixXpr<ExprT>(ExprT(left.expression(),right));         \
}

/** Declare an operator taking two et::MatrixXpr operands. */
#define CML_MATXPR_MATXPR_BINOP(_op_, _OpT_)                             \
template<class XprT1, class XprT2>                                       \
inline et::MatrixXpr<                                                    \
    et::BinaryMatrixOp<                                                  \
        XprT1, XprT2,                                                    \
        _OpT_ <                                                          \
            typename XprT1::value_type,                                  \
            typename XprT2::value_type                                   \
        >                                                                \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const et::MatrixXpr<XprT1>& left,                                \
        const et::MatrixXpr<XprT2>& right)                               \
{                                                                        \
    typedef et::BinaryMatrixOp<                                          \
            XprT1, XprT2,                                                \
            _OpT_ <                                                      \
                typename XprT1::value_type,                              \
                typename XprT2::value_type>                              \
        > ExprT;                                                         \
    return et::MatrixXpr<ExprT>(                                         \
            ExprT(left.expression(),right.expression()));                \
}


/** Declare an operator taking a matrix and a scalar. */
#define CML_MAT_SCALAR_BINOP(_op_, _OpT_)                                \
template<typename E, class AT, typename ScalarT>                         \
inline et::MatrixXpr<                                                    \
    et::BinaryMatrixOp<                                                  \
        matrix<E,AT>, ScalarT, _OpT_ <E,ScalarT>                         \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const matrix<E,AT>& left,                                        \
        SCALAR_ARG_TYPE right)                                           \
{                                                                        \
    typedef et::BinaryMatrixOp<                                          \
            matrix<E,AT>, ScalarT, _OpT_ <E,ScalarT  >                   \
        > ExprT;                                                         \
    return et::MatrixXpr<ExprT>(ExprT(left,right));                      \
}

/** Declare an operator taking a scalar and a matrix. */
#define CML_SCALAR_MAT_BINOP(_op_, _OpT_)                                \
template<typename ScalarT, typename E, class AT>                         \
inline et::MatrixXpr<                                                    \
    et::BinaryMatrixOp<                                                  \
        ScalarT, matrix<E,AT>, _OpT_ <ScalarT,E>                         \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        SCALAR_ARG_TYPE left,                                            \
        const matrix<E,AT>& right)                                       \
{                                                                        \
    typedef et::BinaryMatrixOp<                                          \
            ScalarT, matrix<E,AT>, _OpT_<ScalarT,E>                      \
        > ExprT;                                                         \
    return et::MatrixXpr<ExprT>(ExprT(left,right));                      \
}

/** Declare an operator taking a et::MatrixXpr and a scalar. */
#define CML_MATXPR_SCALAR_BINOP(_op_, _OpT_)                             \
template<class XprT, typename ScalarT>                                   \
inline et::MatrixXpr<                                                    \
    et::BinaryMatrixOp<                                                  \
        XprT, ScalarT, _OpT_ <typename XprT::value_type, ScalarT>        \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const et::MatrixXpr<XprT>& left,                                 \
        SCALAR_ARG_TYPE right)                                           \
{                                                                        \
    typedef et::BinaryMatrixOp<                                          \
            XprT, ScalarT, _OpT_ <typename XprT::value_type,ScalarT>     \
        > ExprT;                                                         \
    return et::MatrixXpr<ExprT>(ExprT(left.expression(),right));         \
}

/** Declare an operator taking a scalar and a et::MatrixXpr. */
#define CML_SCALAR_MATXPR_BINOP(_op_, _OpT_)                             \
template<typename ScalarT, class XprT>                                   \
inline et::MatrixXpr<                                                    \
    et::BinaryMatrixOp<                                                  \
        ScalarT, XprT, _OpT_ <ScalarT, typename XprT::value_type>        \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        SCALAR_ARG_TYPE left,                                            \
        const et::MatrixXpr<XprT>& right)                                \
{                                                                        \
    typedef et::BinaryMatrixOp<                                          \
            ScalarT, XprT, _OpT_ <ScalarT, typename XprT::value_type>    \
        > ExprT;                                                         \
    return et::MatrixXpr<ExprT>(ExprT(left,right.expression()));         \
}

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
