#ifndef __CPA__TYPE_TRAITS
#define __CPA__TYPE_TRAITS

#include <type_traits>

/**
 * @file type_traits.h
 * @author Felix Morgner
 * @brief This file contains "additions" to the standard 'type_traits' header.
 *
 * The standard 'type_traits' header provides a lot of nice meta-programming class-types. Since C++14, a large number
 * of aliases have been introduced for example to access the 'type' member of most type-based classes. However, most if not
 * all 'value-based' meta-programming 'class-types' currently lack respective aliases. Even though C++17 will rectify that,
 * it would be nice to able to use them now. This header introduces those aliases and add some other minor functionality.
 */

namespace cpa
  {
  template<typename ...>
  struct __cpa_void_type { using type = void; };

  /**
   * A meta-programming template to provide spezialization selection through being a better specialized void
   */
  template<typename ...Types>
  using void_t = typename __cpa_void_type<Types...>::type;

  template<typename Type>
  using __cpa_is_negatable = void_t<decltype(-std::declval<Type&>())>;

  template<typename Type>
  using __cpa_is_lessthan_comparable = void_t<std::enable_if_t<std::is_same<bool, decltype(std::declval<Type&>() < std::declval<Type&>())>::value, Type>>;

  /**
   * Determine if a type supports unary '-'
   */
  template<typename Type, typename = void>
  struct is_negatable : std::false_type {};

  template<typename Type>
  struct is_negatable<Type, __cpa_is_negatable<Type>> : std::true_type {};

  /**
   * Convenience alias for cpa::is_negatable<Type>::value
   */
  template<typename Type>
  constexpr bool is_negatable_v = is_negatable<Type>::value;

  /**
   * Determine if a type supports comparison by '<'
   */
  template<typename Type, typename = void>
  struct is_lessthan_comparable : std::false_type {};

  template<typename Type>
  struct is_lessthan_comparable<Type, __cpa_is_lessthan_comparable<Type>> : std::true_type {};

  /**
   * Convenience alias for cpa::is_negatable<Type>::value
   */
  template<typename Type>
  constexpr bool is_lessthan_comparable_v = is_lessthan_comparable<Type>::value;

  /**
   * Convenience alias for std::is_integral<Type>::value
   */
  template<typename Type>
  constexpr bool is_integral_v = std::is_integral<Type>::value;

  /**
   * Convenience alias for std::is_signed<Type>::value
   */
  template<typename Type>
  constexpr bool is_signed_v = std::is_signed<Type>::value;

  /**
   * Convenience alias for std::is_convertible<From, To>::value
   */
  template<typename From, typename To>
  constexpr bool is_convertible_v = std::is_convertible<From, To>::value;
  }

#endif

