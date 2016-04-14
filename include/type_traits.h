#ifndef __CPA__TYPE_TRAITS
#define __CPA__TYPE_TRAITS

#include <type_traits>
#include <__impl/type_traits.h>

/**
 * @file type_traits.h
 * @author Felix Morgner
 * @defgroup type_support Type support library
 * @brief This file contains additions to the standard \p type_traits header.
 *
 * The standard header \p type_traits provides a lot of template
 * meta-programming infrastructure. Since C++14, aliases for the \p type
 * member typedefs of the respective structures have been defined. C++17 will
 * introduce additional aliases for the \p value member of structures like
 * std::is_integral.
 *
 * This header enhances the standard C++14 \p type_traits header by adding the
 * C++17 aliases and some custom utilities.
 */


namespace cpa
  {
  /**
   * @ingroup type_support
   * @defgroup value_aliases Value aliases
   *
   * These variables are aliases for the \p value member of value based
   * meta-programming structures.
   */

  /**
   * @ingroup type_support
   * @defgroup operation_support Operation support
   *
   * These structs allow the user to check wheter or not one or multiple types
   * support a certain operation.
   *
   * @note
   * It is not possible to check the semantics of an operataion purely based on
   * type information. Even worse, determining the semantics of a segment of
   * code is known to be NP-complete in the generic case. Therefore, the
   * template meta-programming structures found here are not able to make
   * semantic decissions. The only decissions that are made here are if the
   * arguments to the templates full-fill some type/syntactic constaint.
   */

  /**
   * @ingroup type_support
   * @defgroup type_aliases Type aliases
   *
   * These types are aliases for the \p type member of type based
   * meta-programming structures.
   */

  /**
   * @ingroup type_support
   *
   * Template meta-programming type to transform arbitrary types to \p void
   */
  template<typename ...>
  struct voidify { using type = void; };

  /**
   * @ingroup type_aliases
   *
   * Alias for the type member of cpa::voidify<Types>
   */
  template<typename ...Types>
  using voidify_t = typename voidify<Types...>::type;

  /**
   * @ingroup value_aliases
   * Convenience alias for std::is_integral<Type>::value
   */
  template<typename Type>
  constexpr bool is_integral_v = std::is_integral<Type>::value;

  /**
   * @ingroup value_aliases
   * Convenience alias for std::is_signed<Type>::value
   */
  template<typename Type>
  constexpr bool is_signed_v = std::is_signed<Type>::value;

  /**
   * @ingroup value_aliases
   * Convenience alias for std::is_convertible<From, To>::value
   */
  template<typename From, typename To>
  constexpr bool is_convertible_v = std::is_convertible<From, To>::value;

  /**
   * @ingroup value_aliases
   * Convenience alias for std::is_same<Left, Right>::value
   */
  template<typename Left, typename Right>
  constexpr bool is_same_v = std::is_same<Left, Right>::value;

  /**
   * @ingroup value_aliases
   * Alias for std::is_nothrow_constructible<Type, Args...>::value
   */
  template<typename Type, typename ...Args>
  constexpr auto is_nothrow_constructible_v = std::is_nothrow_constructible<Type, Args...>::value;

  /**
   * @ingroup operation_support
   * @brief Determine if a type supports the unary operator \p -
   *
   * Provides a static constant \p value that is either true or false.
   */
  template<typename Type>
  struct is_negatable : __cpa_is_negatable<Type> {};

  /**
   * @ingroup value_aliases
   * Convenience alias for cpa::is_negatable<Type>::value
   */
  template<typename Type>
  constexpr bool is_negatable_v = is_negatable<Type>::value;

  /**
   * @ingroup operation_support
   * @brief Determine if a type comparison by \p <
   *
   * Provides a static constant \p value that is either true or false. If not
   * provided, \p Right defaults to \p Left.
   */
  template<typename Left, typename Right = Left>
  struct is_lessthan_comparable : __cpa_is_lessthan_comparable<Left, Right> {};

  /**
   * @ingroup value_aliases
   * Convenience alias for cpa::is_lessthan_comparable<Left, Right>::value. If
   * not provided, \p Right defaults to \p Left.
   */
  template<typename Left, typename Right = Left>
  constexpr bool is_lessthan_comparable_v = is_lessthan_comparable<Left, Right>::value;

  }

#endif

