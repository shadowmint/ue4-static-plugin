#include "dynamic.h"
#include "types.h"

using namespace npp;

/// Create a new instance
DynamicLib::DynamicLib(IDynamicLoader *loader, DynamicInit init) {
  this->loader = loader;
  DynamicInitLib lib = [&](const char *value) {
    loader->dlopen(value).then([&] (void *handle) {
      this->handle = handle;
    }, [] (const char *value) {
      throw DynamicError(value);
    });
  };
  DynamicInitSym sym = [&](const char *value, i32 key) {
    loader->dlsym(value).then([&] (void *handle) {
      this->symbols.resize(key + 1);
      this->symbols.at(key) = handle;
    }, [] (const char *value) {
      throw DynamicError(value);
    });
  };
  init(lib, sym);
}

/// Destroy and shutdown
DynamicLib::~DynamicLib() {
  if (this->handle != NULL) {
    this->loader->dlclose(this->handle);
  }
}

/// Create an error from this error
DynamicError::DynamicError(const char *error) {
  this->message = error;
}

/// Get the error message
const char *DynamicError::error() {
  return this->message;
}

/// Open a library handle
/// @return The handle for the library for an error status
Result<void *, const char *> DummyDynamicLoader::dlopen(const char *path) {
  if (path != NULL) {
    return Ok<void *, const char *>(this);
  }
  return Err<void *, const char *>("Invalid name");
}

/// Internal temporary function
int DummyDynamicLoader__dummy(int value) {
  return value + 1;
}

/// Fetch a named library symbol
/// @return The symbol or an error status
Result<void *, const char *> DummyDynamicLoader::dlsym(const char *path) {
  if (path != NULL) {
    return Ok<void *, const char *>((void *) DummyDynamicLoader__dummy);
  }
  return Err<void *, const char *>("Invalid name");
}

/// Close an open library handle
void DummyDynamicLoader::dlclose(void *handle) {
}

/// Graceful shutdown
DummyDynamicLoader::~DummyDynamicLoader() {
}
