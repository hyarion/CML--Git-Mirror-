/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef matrix_traits_h
#define matrix_traits_h

#include <cml/et/traits.h>

namespace cml {

/* Forward declare for traits class: */
template<typename E, class AT> class matrix;

/* Promotions belong in the et namespace: */
namespace et {

template<typename E, class AT>
struct ExprTraits< cml::matrix<E,AT> >
{
    typedef typename cml::matrix<E,AT> expr_type;
    typedef typename expr_type::value_type value_type;
    typedef typename expr_type::expr_reference reference;
    typedef typename expr_type::expr_const_reference const_reference;
    typedef typename expr_type::result_tag result_tag;
    typedef typename expr_type::size_tag size_tag;
    typedef expr_type result_type;
    typedef expr_leaf_tag node_tag;

    value_type get(const expr_type& m, size_t i, size_t j) const {
        return m(i,j);
    }

    matrix_size size(const expr_type& e) const { return e.size(); }
    size_t rows(const expr_type& m) const { return m.rows(); }
    size_t cols(const expr_type& m) const { return m.cols(); }
};

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
