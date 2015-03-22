#include <npp/test/test_suite.h>
#include <npp/dynamic.h>

using namespace npp;
using namespace npp::test;

typedef int(*dynamic_library_fixture_type)(int);

enum Sym {
  ThingOne = 0,
  ThingTwo = 1
};

void test_create_dummy_dynamic_loader() {
  auto v = new DummyDynamicLoader();
  delete v;
}

void test_create_dynamic_library() {
  auto loader = new DummyDynamicLoader();
  try {
    DynamicLib *v = new DynamicLib(loader, [] (DynamicInitLib lib, DynamicInitSym sym) {
      lib("foo.fake");
      sym("foo_1", Sym::ThingOne);
      sym("foo_2", Sym::ThingTwo);
    });
    delete v;
  }
  catch(DynamicError err) {
    UNREACHABLE;
  }
}

void test_fail_create_dynamic_library() {
  auto loader = new DummyDynamicLoader();
  try {
    DynamicLib *v = new DynamicLib(loader, [] (DynamicInitLib lib, DynamicInitSym sym) {
      lib("foo.fake");
      sym(NULL, Sym::ThingOne);
    });
    UNREACHABLE;
  }
  catch(DynamicError err) {
  }
}

void test_use_dynamic_library() {
  auto loader = new DummyDynamicLoader();
  try {
    DynamicLib *v = new DynamicLib(loader, [] (DynamicInitLib lib, DynamicInitSym sym) {
      lib("foo.fake");
      sym("foo_1", Sym::ThingOne);
    });
    i32 rtn = (v->as<dynamic_library_fixture_type>(Sym::ThingOne))(100);
    ASSERT(rtn == 101);
    delete v;
  }
  catch(DynamicError err) {
    UNREACHABLE;
  }
}

class Tests: public TestSuite {
  public:
    Tests() {
      TEST(test_create_dummy_dynamic_loader)
      TEST(test_create_dynamic_library)
      TEST(test_fail_create_dynamic_library)
    }
};

int main(int argc, char **argv) {
  return (new Tests())->report();
}
