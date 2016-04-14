#include <type_traits.h>

#include <cute/cute.h>
#include <cute/ide_listener.h>
#include <cute/xml_listener.h>
#include <cute/cute_runner.h>

namespace
  {
  struct non_negatable_type { };

  struct negatable_type
    {
    negatable_type operator - () const;
    };

  struct almost_negatable_type
    {
    void operator - () const;
    };

  struct overloaded_negatable_type
    {
    overloaded_negatable_type operator - () const;
    overloaded_negatable_type operator - ();
    };

  struct reference_overloaded_negatable_type
    {
    reference_overloaded_negatable_type   operator - () const;
    reference_overloaded_negatable_type & operator - ();
    };
  }

void test_is_negatable_int()
  {
  ASSERT((cpa::is_negatable_v<int>));
  }

void test_is_negatable_float()
  {
  ASSERT((cpa::is_negatable_v<float>));
  }

void test_is_negatable_uint()
  {
  ASSERT((cpa::is_negatable_v<unsigned int>));
  }

void test_is_negatable_negatable_type()
  {
  ASSERT((cpa::is_negatable_v<negatable_type>));
  }

void test_is_negatable_non_negatable_type()
  {
  ASSERT(!(cpa::is_negatable_v<non_negatable_type>));
  }

void test_is_negatable_almost_negatable_type()
  {
  ASSERT(!(cpa::is_negatable_v<almost_negatable_type>));
  }

void test_is_negatable_overloaded_negatable_type()
  {
  ASSERT((cpa::is_negatable_v<overloaded_negatable_type>));
  }

void test_is_negatable_overloaded_negatable_type_const()
  {
  ASSERT((cpa::is_negatable_v<overloaded_negatable_type const>));
  }

void test_is_negatable_reference_overloaded_negatable_type()
  {
  ASSERT((cpa::is_negatable_v<reference_overloaded_negatable_type>));
  }

void test_is_negatable_reference_overloaded_negatable_type_const()
  {
  ASSERT((cpa::is_negatable_v<reference_overloaded_negatable_type const>));
  }

int main(int argc, char * argv[])
  {
  auto suite = cute::suite{};

  using T = cute::test;

  suite += T{"'int' should be negatable",
             test_is_negatable_int};
  suite += T{"'float' should be negatable",
             test_is_negatable_float};
  suite += T{"'unsigned int' should be negatable",
             test_is_negatable_uint};
  suite += T{"'negatable_type' should be negatable",
             test_is_negatable_negatable_type};
  suite += T{"'non_negatable_type' should not be negatable",
             test_is_negatable_non_negatable_type};
  suite += T{"'almost_negatable_type' should not be negatable",
             test_is_negatable_almost_negatable_type};
  suite += T{"'overloaded_negatable_type' should be negatable",
             test_is_negatable_overloaded_negatable_type};
  suite += T{"'overloaded_negatable_type const' should be negatable",
             test_is_negatable_overloaded_negatable_type_const};
  suite += T{"'reference_overloaded_negatable_type' should be negatable",
             test_is_negatable_reference_overloaded_negatable_type};
  suite += T{"'reference_overloaded_negatable_type const' should be negatable",
             test_is_negatable_reference_overloaded_negatable_type_const};

  auto file = cute::xml_file_opener{argc, argv};
  auto listener = cute::xml_listener<cute::ide_listener<>>{file.out};

  auto runner = cute::makeRunner(listener, argc, argv);

  return !runner(suite, "CPA::type_traits::is_negatable");
  }

