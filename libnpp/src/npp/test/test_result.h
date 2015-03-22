#pragma once

#include "test.h"

namespace npp {

  namespace test {

    /// A unit test static function type
    typedef void (*Test) (void);

    /// A result type, like in rust
    class TestResult {

      public:
        
        /// Name of this test
        const char *name;

        /// The test callback
        Test handle;

        /// Did the test pass?
        bool success;

        /// Test a test instance
        TestResult(const char *name, Test handler);

        /// Run the test instance
        bool run();
    };
  }
}
