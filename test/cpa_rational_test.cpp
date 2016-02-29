#include <rational.h>

#include <cute/cute.h>
#include <cute/ide_listener.h>
#include <cute/xml_listener.h>
#include <cute/cute_runner.h>

#include <iostream>
#include <stdexcept>

void test_instantiation_with_single_integral()
  {
  auto constexpr r1 = cpa::rational{1};
  ASSERT_EQUAL(1, r1.numerator());
  ASSERT_EQUAL(1, r1.denominator());

  auto constexpr r2 = cpa::rational{-8};
  ASSERT_EQUAL(-8, r2.numerator());
  ASSERT_EQUAL( 1, r2.denominator());
  }

void test_instantiation_with_two_integrals()
  {
  auto constexpr r1 = cpa::rational{3, 9};
  ASSERT_EQUAL(3, r1.numerator());
  ASSERT_EQUAL(9, r1.denominator());

  auto constexpr r2 = cpa::rational{-12, 7};
  ASSERT_EQUAL(-12, r2.numerator());
  ASSERT_EQUAL(  7, r2.denominator());

  auto constexpr r3 = cpa::rational{9, -5};
  ASSERT_EQUAL( 9, r3.numerator());
  ASSERT_EQUAL(-5, r3.denominator());
  }

void test_instantiation_with_zero_denominator()
  {
  ASSERT_THROWS(cpa::rational(1, 0), std::domain_error);
  }

void test_reduce_with_non_reducible_positive_rational()
  {
  auto constexpr r1 = cpa::rational{5, 13};
  auto constexpr r2 = r1.reduce();

  ASSERT_EQUAL( 5, r2.numerator());
  ASSERT_EQUAL(13, r2.denominator());
  }

void test_reduce_with_reducible_positive_rational()
  {
  auto constexpr r1 = cpa::rational{6, 14};
  auto constexpr r2 = r1.reduce();

  ASSERT_EQUAL(3, r2.numerator());
  ASSERT_EQUAL(7, r2.denominator());
  }

void test_reduce_with_non_reducible_negative_numerator_rational()
  {
  auto constexpr r1 = cpa::rational{-5, 13};
  auto constexpr r2 = r1.reduce();

  ASSERT_EQUAL(-5, r2.numerator());
  ASSERT_EQUAL(13, r2.denominator());
  }

void test_reduce_with_reducible_negative_numerator_rational()
  {
  auto constexpr r1 = cpa::rational{-6, 14};
  auto constexpr r2 = r1.reduce();

  ASSERT_EQUAL(-3, r2.numerator());
  ASSERT_EQUAL( 7, r2.denominator());
  }

void test_reduce_with_non_reducible_negative_denominator_rational()
  {
  auto constexpr r1 = cpa::rational{7, -15};
  auto constexpr r2 = r1.reduce();

  ASSERT_EQUAL(  7, r2.numerator());
  ASSERT_EQUAL(-15, r2.denominator());
  }

void test_reduce_with_reducible_negative_denominator_rational()
  {
  auto constexpr r1 = cpa::rational{12, -8};
  auto constexpr r2 = r1.reduce();

  ASSERT_EQUAL( 3, r2.numerator());
  ASSERT_EQUAL(-2, r2.denominator());
  }

void test_addition_positive_positive_with_same_type_and_denominator()
  {
  auto constexpr r1 = cpa::rational{1, 4};
  auto constexpr r2 = cpa::rational{1, 4};
  auto constexpr r3 = r1 + r2;

  ASSERT_EQUAL(2, r3.numerator());
  ASSERT_EQUAL(4, r3.denominator());
  }

void test_addition_positive_negative_with_same_type_and_denominator()
  {
  auto constexpr r1 = cpa::rational{ 3, 5};
  auto constexpr r2 = cpa::rational{-1, 5};
  auto constexpr r3 = r1 + r2;

  ASSERT_EQUAL(2, r3.numerator());
  ASSERT_EQUAL(5, r3.denominator());
  }

void test_addition_negative_positive_with_same_type_and_denominator()
  {
  auto constexpr r1 = cpa::rational{-3, 4};
  auto constexpr r2 = cpa::rational{ 1, 4};
  auto constexpr r3 = r1 + r2;

  ASSERT_EQUAL(-2, r3.numerator());
  ASSERT_EQUAL( 4, r3.denominator());
  }

void test_addition_negative_negative_with_same_type_and_denominator()
  {
  auto constexpr r1 = cpa::rational{-9, 23};
  auto constexpr r2 = cpa::rational{-7, 23};
  auto constexpr r3 = r1 + r2;

  ASSERT_EQUAL(-16, r3.numerator());
  ASSERT_EQUAL( 23, r3.denominator());
  }

void test_addition_positive_positive_with_same_type_and_different_denominator()
  {
  auto constexpr r1 = cpa::rational{1, 4};
  auto constexpr r2 = cpa::rational{1, 8};
  auto constexpr r3 = r1 + r2;

  ASSERT_EQUAL(3, r3.numerator());
  ASSERT_EQUAL(8, r3.denominator());
  }

void test_addition_positive_negative_with_same_type_and_different_denominator()
  {
  auto constexpr r1 = cpa::rational{ 3, 7};
  auto constexpr r2 = cpa::rational{-1, 9};
  auto constexpr r3 = r1 + r2;

  ASSERT_EQUAL(20, r3.numerator());
  ASSERT_EQUAL(63, r3.denominator());
  }

void test_addition_negative_positive_with_same_type_and_different_denominator()
  {
  auto constexpr r1 = cpa::rational{-3, 4};
  auto constexpr r2 = cpa::rational{ 1, 2};
  auto constexpr r3 = r1 + r2;

  ASSERT_EQUAL(-1, r3.numerator());
  ASSERT_EQUAL( 4, r3.denominator());
  }

void test_addition_negative_negative_with_same_type_and_different_denominator()
  {
  auto constexpr r1 = cpa::rational{-9, 2};
  auto constexpr r2 = cpa::rational{-7, 8};
  auto constexpr r3 = r1 + r2;

  ASSERT_EQUAL(-43, r3.numerator());
  ASSERT_EQUAL(  8, r3.denominator());
  }

int main(int argc, char * argv[])
  {
  auto suite = cute::suite{};

  using T = cute::test;

  suite += T{"Instantiation with a single IntegralValue",
             test_instantiation_with_single_integral};
  suite += T{"Instantiation with two IntegralValues",
             test_instantiation_with_two_integrals};
  suite += T{"Instantiation with zero as the denominator",
             test_instantiation_with_zero_denominator};

  suite += T{"Reduce a non-reducible positive rational",
             test_reduce_with_non_reducible_positive_rational};
  suite += T{"Reduce a positive rational",
             test_reduce_with_reducible_positive_rational};
  suite += T{"Reduce a non-reducible rational with a negative numerator",
             test_reduce_with_non_reducible_negative_numerator_rational};
  suite += T{"Reduce a rational with a negative numerator",
             test_reduce_with_reducible_negative_numerator_rational};
  suite += T{"Reduce a non-reducible rational with a negative denominator",
             test_reduce_with_non_reducible_negative_denominator_rational};
  suite += T{"Reduce a rational with a negative numerator with a negative denominator",
             test_reduce_with_reducible_negative_denominator_rational};

  suite += T{"Add two positive rationals with the same representation and denominator",
              test_addition_positive_positive_with_same_type_and_denominator};
  suite += T{"Add a positive and a negative rational with the same representation and denominator",
             test_addition_positive_negative_with_same_type_and_denominator};
  suite += T{"Add a negative and a positive rational with the same representation and denominator",
             test_addition_negative_positive_with_same_type_and_denominator};
  suite += T{"Add two negative rationals with the same representation and denominator",
             test_addition_negative_negative_with_same_type_and_denominator};

  suite += T{"Add two posisitive rationals with the same representation but different denominators",
             test_addition_positive_positive_with_same_type_and_different_denominator};
  suite += T{"Add a positive and a negative rational with the same representation but different denominators",
             test_addition_positive_negative_with_same_type_and_different_denominator};
  suite += T{"Add a negative and a positive rational with the same representation but different denominators",
             test_addition_negative_positive_with_same_type_and_different_denominator};
  suite += T{"Add two negative rationals with the same representation but different denominators",
             test_addition_negative_negative_with_same_type_and_different_denominator};

  auto file = cute::xml_file_opener{argc, argv};
  auto listener = cute::xml_listener<cute::ide_listener<>>{file.out};

  auto runner = cute::makeRunner(listener, argc, argv);

  return !runner(suite, "CPA::rational::basic_rational");
  }

