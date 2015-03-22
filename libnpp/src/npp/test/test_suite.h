#pragma once

#include <vector>
#include "test.h"

namespace npp {

  namespace test {

    /// A result type, like in rust
    class TestSuite {

      private:

        /// The list of test functions to run
        std::vector<TestResult*> tests;

      protected:

        /// Add a new a test
        void test(const char *name, Test target);

      public:

        /// Create a new instance
        TestSuite();

        /// Destory instance
        ~TestSuite();

        /// Run the test suite and return a count of failures
        int report();
    };
  }
}
