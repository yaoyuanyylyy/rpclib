#pragma once

#ifndef ALL_H_H8MAAYCG
#define ALL_H_H8MAAYCG

#include "rpcpp/detail/invoke.h"
#include "rpcpp/detail/if.h"
#include "rpcpp/detail/bool.h"

namespace rpc {
namespace detail {

//! \brief This type can be used to check multiple conditions.
//! It will be true_type if all its arguments are true.
template <typename... T> struct all : true_ {};

template <typename H, typename... T>
struct all<H, T...>
    : if_<H, all<T...>, false_> {};

}
}



#endif /* end of include guard: ALL_H_H8MAAYCG */
