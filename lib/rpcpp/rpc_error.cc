#include "rpcpp/rpc_error.h"
#include "format.h"

namespace rpc {

rpc_error::rpc_error(std::string const &what_arg,
                     std::string const &function_name,
                     std::shared_ptr<RPCLIB_MSGPACK::object_handle> o)
    : std::runtime_error(what_arg),
      func_name_(function_name),
      ob_h_(std::move(o)) {}

std::string rpc_error::get_function_name() const { return func_name_; }

RPCLIB_MSGPACK::object_handle &rpc_error::get_error() { return *ob_h_; }

timeout::timeout(std::string const &what_arg) : std::runtime_error(what_arg) {
    formatted =
        RPCLIB_FMT::format("rpc::timeout: {}", std::runtime_error::what());
}

const char *timeout::what() const noexcept { return formatted.data(); }

} /* rpc */
