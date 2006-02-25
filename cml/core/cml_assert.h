/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 * Macros and template metaprogramming to implement compile- and run-time
 * assertions.
 */

#ifndef cml_assert_h
#define cml_assert_h

#include <cml/core/cml_meta.h>

#define CML_JOIN(X,Y) CML_DO_JOIN(X,Y)
#define CML_DO_JOIN(X,Y) CML_DO_JOIN2(X,Y)
#define CML_DO_JOIN2(X,Y) X##Y

/** Default undefined compile-time assertion struct. */
template<bool T> struct STATIC_ASSERTION_FAILURE;

/** Struct instantiated when a true assertion is made at compile-time. */
template<> struct STATIC_ASSERTION_FAILURE<true> {
    typedef true_type result;
    enum { value = true };
};

/** Create a compile-time assertion.
 *
 * @note Compile-time assertions must be expressions that can be evaluated at
 * comile time.  This means that the expression must only rely on constants,
 * enums, and/or template parameters, not variables having run-time storage
 * requirements.
 *
 * @warning Enclose expressions that have commas with parens, otherwise the
 * preprocessor will parse the commas as macro argument separators!
 *
 * @sa STATIC_ASSERTION_FAILURE
 */
#define CML_STATIC_REQUIRE(_E_) \
    typedef typename STATIC_ASSERTION_FAILURE<(_E_)>::result \
        CML_JOIN(__cml_assert_test_typedef_, __LINE__)


/** A more meaningful compile-time assertion struct.
 *
 * The parameter M is a struct type which has been declared but not
 * defined; e.g. struct this_is_an_error.
 *
 * When used with CML_STATIC_REQUIRE_M(<expr>,M), the compiler errors will
 * contain the struct name at the point of the error.
 */
template<bool T, typename M> struct STATIC_ASSERTION_FAILURE_M {
    typename M::bogus result;
};

/** Instantiated for true assertions. */
template<typename M> struct STATIC_ASSERTION_FAILURE_M<true,M> {
    typedef true_type result;
    enum { value = true };
};

/** Create a compile-time assertion with a message.
 *
 * @note Compile-time assertions must be expressions that can be evaluated at
 * comile time.  This means that the expression must only rely on constants,
 * enums, and/or template parameters, not variables having run-time storage
 * requirements.
 *
 * @warning Enclose expressions that have commas with parens, otherwise the
 * preprocessor will parse the commas as macro argument separators!
 *
 * @sa STATIC_ASSERTION_FAILURE_M
 */
#define CML_STATIC_REQUIRE_M(_E_, _M_) \
    typedef typename STATIC_ASSERTION_FAILURE_M<(_E_),_M_> \
        ::result CML_JOIN(__bogus_assert_type_, __LINE__)

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
