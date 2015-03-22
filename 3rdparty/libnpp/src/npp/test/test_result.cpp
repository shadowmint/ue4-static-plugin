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
    try {
      std::exception_ptr p = std::current_exception();
      std::rethrow_exception(p);
    }
    catch(const std::exception& e) {
      std::clog << e.what() << std::endl;
    }
  }
  return this->success;
}
