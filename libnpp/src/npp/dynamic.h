#pragma once

#include "types.h"
#include "result.h"
#include <exception>
#include <functional>
#include <vector>

namespace npp {

  /// Declare classes for deps
  class IDynamicLoader;

  /// Initialize a dynamic library with this type
  typedef std::function< void(const char *) > DynamicInitLib;
  typedef std::function< void(const char *, i32) > DynamicInitSym;
  typedef std::function< void(DynamicInitLib, DynamicInitSym) > DynamicInit;

  /// A singleton helper for loading dynamic libraries
  class Dynamic {
  };

  /// A single dynamic library
  class DynamicLib {
    private:

      /// The list of loaded functions
      std::vector<void *> symbols;

      /// The library handle
      void *handle;

      /// The loader singleton
      IDynamicLoader *loader;

    public:

      /// Create a new instance
      DynamicLib(IDynamicLoader *loader, DynamicInit init);

      /// Destroy and shutdown
      ~DynamicLib();

      /// Return a symbol by id, providing a prototype to bind to
      template<typename TRtn> TRtn as(i32 symbol) {
        return (TRtn) this->symbols[symbol];
      }
  };

  /// Failure type
  class DynamicError : public std::exception {
    private:
      const char *message;

    public:
      DynamicError(const char *error);
      const char *error();
  };

  /// The dynamic loader interface
  class IDynamicLoader {
    public:

      /// Open a library handle
      /// @return The handle for the library for an error status
      virtual Result<void *, const char *> dlopen(const char *path) = 0;

      /// Fetch a named library symbol
      /// @return The symbol or an error status
      virtual Result<void *, const char *> dlsym(const char *path) = 0;

      /// Close an open library handle
      virtual void dlclose(void *handle) = 0;
  };

  /// A dummy IDynamicLib implementation
  class DummyDynamicLoader : public IDynamicLoader {
    public:
      Result<void *, const char *> dlopen(const char *path);
      Result<void *, const char *> dlsym(const char *path);
      void dlclose(void *handle);
  };
}
