#include <npp/test/test_suite.h>
#include <npp/result.h>

using namespace npp;
using namespace npp::test;

Result<int, const char *> test_fixture(int value) {
  if (value >= 0) {
    return Ok<int, const char *>(value + 10);
  }
  return Err<int, const char *>("Invalid request, must be +ve");
}

void test_ok_helper() {
  auto value = Ok<int, int>(100);
  ASSERT(value.is_ok());
  ASSERT(value.ok() == 100);
}

void test_err_helper() {
  auto value = Err<int, int>(100);
  ASSERT(value.is_err());
  ASSERT(value.err() == 100);
}

void test_then_fixture() {
  auto value = test_fixture(100);
  ASSERT(value.is_ok() && value.ok() == 110);
  value = test_fixture(-10);
  ASSERT(value.is_err());
}

void test_then() {
  test_fixture(100).then([] (int v) { ASSERT(v == 110); }, [] (const char * err) { UNREACHABLE; });
  test_fixture(-10).then([] (int v) { UNREACHABLE; }, [] (const char * err) { ASSERT(err != NULL); });
}

void test_then_as_lambdas() {
  int v0 = 0;
  test_fixture(100).then([&] (int v) { v0 = 100; }, [] (const char * err) { UNREACHABLE; });
  ASSERT(v0 == 100);

  int v1 = 0;
  test_fixture(-10).then([] (int v) { UNREACHABLE; }, [&] (const char * err) { v1 = 100; });
  ASSERT(v1 == 100);
}

class Tests: public TestSuite {
  public:
    Tests() {
      TEST(test_ok_helper)
      TEST(test_err_helper)
      TEST(test_then_fixture)
      TEST(test_then)
    }
};

int main(int argc, char **argv) {
  return (new Tests())->report();
}
