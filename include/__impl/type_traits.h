#ifndef __CPA_IMPL__TYPE_TRAITS
#define __CPA_IMPL__TYPE_TRAITS

#include <type_traits>

namespace cpa
  {
  template<typename ...>
  struct voidify;

  template<typename ...Types>
  using voidify_t = typename voidify<Types...>::type;

  template<typename Type>
  using __cpa_negation_t = decltype(-std::declval<Type &>());

  template<typename Type, typename = void>
  struct __cpa_is_negatable : std::false_type {};

  template<typename Type>
  struct __cpa_is_negatable<Type, voidify_t<__cpa_negation_t<Type>>>
  : std::is_same<Type, std::remove_reference_t<__cpa_negation_t<Type>>>::type {};

  template<typename Type>
  struct __cpa_is_negatable<Type const, voidify_t<__cpa_negation_t<Type const>>>
  : std::is_same<Type, __cpa_negation_t<Type const>>::type {};

  template<typename Left, typename Right>
  using __cpa_lessthan_comparison_t = decltype(std::declval<Left>() < std::declval<Right>());

  template<typename Left, typename Right, typename = void>
  struct __cpa_is_lessthan_comparable : std::false_type {};

  template<typename Left, typename Right>
  struct __cpa_is_lessthan_comparable<Left, Right, voidify_t<__cpa_lessthan_comparison_t<Left, Right>>>
  : std::is_same<bool, std::decay_t<__cpa_lessthan_comparison_t<Left, Right>>>::type {};
  }

#endif

