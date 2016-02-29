#include <numeric.h>

#include <cute/cute.h>
#include <cute/ide_listener.h>
#include <cute/xml_listener.h>
#include <cute/cute_runner.h>

#include <iostream>
#include <stdexcept>

void test_abs_with_positive_int()
  {
  ASSERT_EQUAL(1337, cpa::abs(1337));
  }

void test_abs_with_negative_int()
  {
  ASSERT_EQUAL(42, cpa::abs(-42));
  }

void test_abs_with_positive_float()
  {
  ASSERT_EQUAL(2.f, cpa::abs(2.f));
  }

void test_abs_with_negative_float()
  {
  ASSERT_EQUAL(2.f, cpa::abs(-2.f));
  }

void test_gcd_with_positive_positive_prime_ints()
  {
  ASSERT_EQUAL(1, cpa::gcd(3, 7));
  }

void test_gcd_with_positive_negative_prime_ints()
  {
  ASSERT_EQUAL(1, cpa::gcd(7, -11));
  }

void test_gcd_with_negative_positive_prime_ints()
  {
  ASSERT_EQUAL(1, cpa::gcd(-5, 2));
  }

void test_gcd_with_negative_negative_prime_ints()
  {
  ASSERT_EQUAL(1, cpa::gcd(-13, -17));
  }

void test_gcd_with_positive_positive_nonprime_ints()
  {
  ASSERT_EQUAL(2, cpa::gcd(8, 18));
  }

void test_gcd_with_positive_negative_nonprime_ints()
  {
  ASSERT_EQUAL(12, cpa::gcd(12, -144));
  }

void test_gcd_with_negative_positive_nonprime_ints()
  {
  ASSERT_EQUAL(9, cpa::gcd(-18, 9));
  }

void test_gcd_with_negative_negative_nonprime_ints()
  {
  ASSERT_EQUAL(10, cpa::gcd(-20, -30));
  }

void test_gcd_with_positive_positive_mixed_ints()
  {
  ASSERT_EQUAL(1, cpa::gcd(8, 17));
  }

void test_gcd_with_positive_negative_mixed_ints()
  {
  ASSERT_EQUAL(1, cpa::gcd(12, -23));
  }

void test_gcd_with_negative_positive_mixed_ints()
  {
  ASSERT_EQUAL(1, cpa::gcd(-7, 9));
  }

void test_gcd_with_negative_negative_mixed_ints()
  {
  ASSERT_EQUAL(1, cpa::gcd(-19, -30));
  }

int main(int argc, char * argv[])
  {
  auto suite = cute::suite{};

  suite += CUTE(test_abs_with_positive_int);
  suite += CUTE(test_abs_with_negative_int);
  suite += CUTE(test_abs_with_positive_float);
  suite += CUTE(test_abs_with_negative_float);

  suite += CUTE(test_gcd_with_positive_positive_prime_ints);
  suite += CUTE(test_gcd_with_negative_positive_prime_ints);
  suite += CUTE(test_gcd_with_positive_negative_prime_ints);
  suite += CUTE(test_gcd_with_negative_negative_prime_ints);

  suite += CUTE(test_gcd_with_positive_positive_nonprime_ints);
  suite += CUTE(test_gcd_with_negative_positive_nonprime_ints);
  suite += CUTE(test_gcd_with_positive_negative_nonprime_ints);
  suite += CUTE(test_gcd_with_negative_negative_nonprime_ints);

  suite += CUTE(test_gcd_with_positive_positive_mixed_ints);
  suite += CUTE(test_gcd_with_negative_positive_mixed_ints);
  suite += CUTE(test_gcd_with_positive_negative_mixed_ints);
  suite += CUTE(test_gcd_with_negative_negative_mixed_ints);

  auto file = cute::xml_file_opener{argc, argv};
  auto listener = cute::xml_listener<cute::ide_listener<>>{file.out};

  auto runner = cute::makeRunner(listener, argc, argv);

  return !runner(suite, "CPA::numeric");
  }

