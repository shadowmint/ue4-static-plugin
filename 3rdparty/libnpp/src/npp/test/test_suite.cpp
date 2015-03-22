#include <stdio.h>
#include "../types.h"
#include "test_suite.h"
#include "test_result.h"

using namespace npp::test;

/// Create a new instance
TestSuite::TestSuite() {
}

/// Destroy instance
TestSuite::~TestSuite() {
  for (auto i = 0; i < this->tests.size(); ++i) {
    delete this->tests.at(i);
  }
  this->tests.clear();
}

/// Add a new a test
void TestSuite::test(const char *name, Test handle) {
  this->tests.push_back(new TestResult(name, handle));
}

/// Run the test suite and return a count of failures
int TestSuite::report() {
  auto failures = 0;
  auto count = 0;
  for (auto i = 0; i < this->tests.size(); ++i) {
    TestResult *t = this->tests.at(i);
    count += 1;
    printf("exec: %s ", t->name);
    if (t->run()) {
      printf("\033[32mOK\033[0m\n");
    }
    else {
      failures += 1;
      printf("\033[31;1mFAIL\033[0m\n");
    }
  }
  if (failures > 0) {
    printf("\033[31;1mFAILED (%d/%d passed)\033[0m\n", count - failures, count);
  }
  else {
    printf("SUCCESS\n");
  }
  return failures;
}
