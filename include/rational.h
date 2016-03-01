#ifndef __CPA__RATIONAL
#define __CPA__RATIONAL

#include <numeric.h>

#include <cstdint>
#include <stdexcept>
#include <type_traits>

/**
 * \file rational.h
 * \author Felix Morgner
 * \copyright 3-Clause-BSD
 *
 * \brief Support for expressing almost arbitrary precission rational numbers.
 *
 * This file contains struct and functions that allow the use and creation of almost arbitrary precission rational numbers. Please
 * note that the precission and value-range supported by the basic_rational is dependent on its template parameter.
 */

namespace cpa
  {

  template<typename Rep,
           typename IsIntegralType = std::enable_if_t<std::is_integral<Rep>::value, Rep>>
  struct __rational_constraint { };

  template<typename Rep>
  struct basic_rational
    {
    using rep = Rep;

    /**
     * Construct a cpa::basic_rational representing 0.
     *
     * \note
     * Does not throw if Rep is nothrow constructible
     *
     * \note
     * This constructor does not throw if Rep is NothrowConstructible
     */
    constexpr basic_rational() noexcept(std::is_nothrow_constructible<Rep>::value) = default;

    /**
     * Copy construct a cpa::basic_rational from another cpa::basic_rational.
     *
     * \note
     * No simplifications are applied. The new cpa::basic_rational is an exact value-wise copy of \p other.
     *
     * \note
     * This constructor does not throw if Rep is NothrowCopyConstructible
     */
    constexpr basic_rational(basic_rational const & other) noexcept(std::is_nothrow_copy_constructible<Rep>::value) = default;

    /**
     * Copy construct a cpa::basic_rational from another cpa::basic_rational with a different representation type.
     *
     * \note
     * Just as with cpa::basic_rational::basic_rational(basic_rational const &) no simplications are applied. If the Rep can
     * not represent the value contained in \p other, the behavior is undefined.
     *
     * \note
     * This constructor does not throw if Rep is NothrowConstructible with a value of type OtherRep
     */
    template<typename OtherRep>
    constexpr basic_rational(basic_rational<OtherRep> const & other) noexcept(std::is_nothrow_constructible<Rep, OtherRep>::value)
      : m_numerator{other.m_numerator},
        m_denominator{other.m_denominator}
      {
      static_assert(is_convertible_v<OtherRep, Rep>, "Incompatible types in conversion");
      }

    /**
     * Construct a cpa::basic_rational with a given numerator and an optional denominator. If no denomitor is supplied,
     * it will default to 1.
     *
     * \note
     * This constructor will throw an object of type std::domain_error iff denominator is 0
     */
    explicit constexpr basic_rational(std::intmax_t const numerator, std::intmax_t const denominator = 1)
      : m_numerator{numerator},
        m_denominator{denominator}
      {
      if(!denominator)
        {
        throw std::domain_error{"denominator must not be 0"};
        }
      }

    /**
     * Convert a cpa::basic_rational to a bool
     *
     * \return
     * true if the cpa::basic_rational object does not represent 0, false otherwise
     */
    explicit constexpr operator bool() const
      {
      return m_numerator;
      }

    /**
     * Convert a cpa::basic_rational to a long double
     *
     * \note
     * This conversion will most probably loose precission. The maximum precission achievable is dependend of on the compiler.
     *
     * \return
     * A value of type long double approximating the value held by the cpa::basic_rational object.
     */
    explicit constexpr operator long double() const
      {
      return (long double)m_numerator / m_denominator;
      }

    /**
     * Create an object of type cpa::basic_rational representing a reduction of the current object
     */
    constexpr basic_rational reduce() const
      {
      auto const gcd = cpa::gcd(m_numerator, m_denominator);
      auto const numerator = m_numerator / gcd;
      auto const denominator = m_denominator / gcd;

      return basic_rational{numerator, denominator};
      }

    /**
     * Reduce the current object
     */
    basic_rational & reduce()
      {
      auto const gcd = cpa::gcd(m_numerator, m_denominator);
      m_numerator /= gcd;
      m_denominator /= gcd;

      return *this;
      }

    /**
     * Create an object of type cpa::basic_rational representing an expansion to the common denominator of the current object
     * and \p other
     */
    template<typename OtherRep>
    constexpr basic_rational common(basic_rational const & other) const
      {
      auto const factor = cpa::lcm(m_denominator, other.m_denominator) / m_denominator;
      auto const numerator = m_numerator * factor;
      auto const denominator = m_denominator * factor;

      return basic_rational{numerator, denominator};
      }

    /**
     * Expand the current object to the denominator common to \p other
     */
    basic_rational & common(basic_rational const & other)
      {
      auto const factor = cpa::lcm(m_denominator, other.m_denominator) / m_denominator;
      m_numerator *= factor;
      m_denominator *= factor;

      return *this;
      }

    /**
     * Create an object of type cpa::basic_rational representing an expansion of the current object with \p factor
     *
     * \note
     * If the internal representation type of the newly created object can not represent the value of the expansion, the behavior
     * is undefined.
     *
     * \note
     * This function will throw an instance of std::domain_error iff factor is equal to 0.
     */
    constexpr basic_rational expand(std::intmax_t const factor) const
      {
      if(!factor)
        {
        throw std::domain_error{"expansion by 0 would result in an undefined value"};
        }

      return basic_rational{m_numerator * factor, m_denominator * factor};
      }

    /**
     * Expand the current object by \p factor
     *
     * \note
     * If the internal representation type of the object can not represent the value of the expansion, the behavior is undefined.
     *
     * \note
     * This function will throw an instance of std::domain_error iff factor is equal to 0.
     */
    basic_rational & expand(std::intmax_t const factor)
      {
      if(!factor)
        {
        throw std::domain_error{"expansion by 0 would result in an undefined value"};
        }

      m_numerator *= factor;
      m_denominator *= factor;

      return *this;
      }

    /**
     * Get the numerator of the current object.
     *
     * \note
     * This function will not throw if the Rep is NothrowCopyConstructible
     */
    constexpr rep numerator() const noexcept(std::is_nothrow_copy_constructible<Rep>::value)
      {
      return m_numerator;
      }

    /**
     * Get the denominator of the current object.
     *
     * \note
     * This function will not throw if the Rep is NothrowCopyConstructible
     */
    constexpr rep denominator() const noexcept(std::is_nothrow_copy_constructible<Rep>::value)
      {
      return m_denominator;
      }


    private:
      rep m_numerator;
      rep m_denominator;
    };

  /**
   * Calculate the GCD of two cpa::basic_rational objects
   *
   * \note
   * This is a specialization of cpa::gcd found in numeric.h
   */
  template<typename LeftRep, typename RightRep>
  constexpr auto gcd(basic_rational<LeftRep> const & lhs, basic_rational<RightRep> const & rhs)
    {
    using target_type = basic_rational<std::common_type_t<LeftRep, RightRep>>;
    return target_type{cpa::gcd(lhs.numerator(), rhs.numerator()), cpa::lcm(lhs.denominator(), rhs.denominator())};
    }

  /**
   * Add two cpa::basic_rational objects
   *
   * \note
   * No simplifications will be applied to the result.
   */
  template<typename Rep>
  constexpr auto operator + (basic_rational<Rep> const & lhs, basic_rational<Rep> const & rhs)
    {
    auto const & cl = lhs.common(rhs);
    auto const & cr = rhs.common(lhs);

    return basic_rational<Rep>{cl.numerator() + cr.numerator(), cl.denominator()};
    }

  /*
   * Alias for a cpa::basic_rational instantiated with std::intmax_t
   */
  using rational = cpa::basic_rational<std::intmax_t>;

  }

#endif
