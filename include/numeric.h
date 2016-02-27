#ifndef __CPA__NUMERIC
#define __CPA__NUMERIC

#include <type_traits.h>

#include <cstdint>
#include <iostream>
#include <sstream>
#include <stdexcept>

/**
 * \file numeric.h
 * \author Felix Morgner
 * \copyright 3-Clause-BSD
 *
 * \brief This file contains numeric support functionality
 */

namespace cpa
  {

  /**
   * Get the absolute value of a number
   *
   * \note T is required to be an Negatable
   * \note Applications might specialize this function iff T is a user-defined type, otherwise the program is ill-formed.
   */
  template<typename Type>
  constexpr std::enable_if_t<is_negatable_v<Type> && is_lessthan_comparable_v<Type>, Type> abs(Type const val)
    {
    if(is_signed_v<Type> && val < static_cast<Type>(0))
      {
      return -val;
      }

    return val;
    }

  /**
   * Get the GCD of two numbers
   *
   * \note lhs and rhs must have a common type
   * \note Applications might specialize this function iff at least one of \p Left or \p Right is a user-defined type, otherwise
   * the program is ill-formed.
   */
  template<typename Left, typename Right>
  constexpr std::common_type_t<Left, Right> gcd(Left lhs, Right rhs)
    {
    using common_t = std::common_type_t<Left, Right>;

    if(!lhs && !rhs)
      {
      return 0;
      }

    common_t left = abs(lhs);
    common_t right = abs(rhs);

    while(left && right)
      {
      if(left > right)
        {
        left %= right;
        }
      else
        {
        right %= left;
        }
      }

    return right > left ? right : left;
    }

  /**
   * Get the LCM of two numbers
   *
   * \note \p lhs and \p rhs must have a common type
   * \note Applications might specialize this function iff at least one of \p Left or \p Right is a user-defined type, otherwise
   * the program is ill-formed.
   */
  template<typename Left, typename Right>
  constexpr std::common_type_t<Left, Right> lcm(Left lhs, Right rhs)
    {
    return (lhs / gcd(lhs, rhs)) * rhs;
    }

  }

#endif

