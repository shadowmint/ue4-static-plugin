#pragma once

#include <functional>

namespace npp {

  namespace result {

    /// Either A or B as a single return value
    template<typename TOk, typename TErr> union Value {

      /// Value for success
      TOk ok;

      /// Value for error
      TErr err;
    };

  }

  /// A result type, like in rust
  template<typename TOk, typename TErr> class Result {
    public:

      /// Current value
      result::Value<TOk, TErr> value;

      /// Currently ok?
      bool valid;

      /// Is this valid?
      bool is_ok() {
        return this->valid;
      }

      /// Is this invalid?
      bool is_err() {
        return !this->valid;
      }

      /// Ok value
      TOk ok() {
        return this->value.ok;
      }

      /// Err value
      TErr err() {
        return this->value.err;
      }

      /// Perform some action on success or error
      bool then(std::function< void(TOk t)> on_ok, std::function< void(TErr err)> on_err) {
        if (this->is_ok()) {
          on_ok(this->value.ok);
        }
        else {
          on_err(this->value.err);
        }
        return true;
      }
  };

  /// Shortcut to create an Ok value
  template<typename TOk, typename TErr> Result<TOk, TErr> Ok(TOk ok) {
    Result<TOk, TErr> rtn;
    rtn.valid = true;
    rtn.value.ok = ok;
    return rtn;
  }

  /// Shortcut to create an Err value
  template<typename TOk, typename TErr> Result<TOk, TErr> Err(TErr err) {
    Result<TOk, TErr> rtn;
    rtn.valid = false;
    rtn.value.err = err;
    return rtn;
  }
}
