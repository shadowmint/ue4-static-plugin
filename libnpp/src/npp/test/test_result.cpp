#include <iostream>
#include <exception>
#include <typeinfo>
#include <stdexcept>
#include <stdio.h>
#include "test_result.h"

using namespace npp::test;

/// Create a new instance
TestResult::TestResult(const char *name, Test handle) {
  this->name = name;
  this->handle = handle;
  this->success = false;
}

/// Run this test
bool TestResult::run() {
  try {
    (*this->handle)();
    this->success = true;
  }
  catch (const TestError e) {
    this->success = false;
  }
  catch(...)
  {
    std::exception_ptr p = std::current_exception();
    std::clog <<(p ? p.__cxa_exception_type()->name() : "null") << std::endl;
  }
  return this->success;
}
