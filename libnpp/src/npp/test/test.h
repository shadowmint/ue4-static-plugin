#pragma once

#include <stdio.h>
#include <vector>
#include <exception>
#include "test_result.h"

/// Usage:
///
///   TRACE("%d", 100);
///
#define TRACE(...) \
  printf(__VA_ARGS__); \
  fflush(stdout);

/// Usage:
///
///   class Tests: public TestSuite {
///    public:
///      Tests() {
///        TEST(test_ok_helper)
///        TEST(test_err_helper)
///        ...
///
#define TEST(name) this->test(#name, name);

/// Usage:
///
///   ASSERT(x == 1);
///
#define ASSERT(truth) \
  if (!(truth)) { \
    TRACE("%s:%d ", __FILE__, __LINE__); \
    throw TestError(); \
  }

/// Usage:
///
///  if (cannot_be_false) { UNREACHABLE };
///
#define UNREACHABLE ASSERT(false)

namespace npp {

  namespace test {

    /// Failure type
    class TestError : public std::exception {};
  }
}
