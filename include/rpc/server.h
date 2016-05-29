#pragma once

#ifndef SERVER_H_S0HB5KXY
#define SERVER_H_S0HB5KXY

#include "msgpack.hpp"

#include "callme/dispatcher.h"
#include "callme/detail/pimpl.h"

namespace callme {

namespace detail {
class server_session;
}

//! \brief Implements a msgpack-rpc server. This is the main interfacing
//! point with the library for creating servers.
class server {
public:
    //! \brief Constructs a server that listens on the localhost on the
    //! specified port.
    explicit server(uint16_t port);

    //! \brief Constructs a server that listens on the specified address on 
    //! the specified port.
    server(std::string const &address, uint16_t port);

    ~server();

    //! \brief Starts the server loop. This is a blocking call.
    void run();

    //! \brief Starts the server loop on a separate thread. This is a
    //! non-blocking call.
    //! \param worker_threads The number of worker threads to start.
    void async_run(std::size_t worker_threads = 1);

    //! \brief Binds a functor to a name so it becomes callable via RPC.
    //! \param name The name of the functor.
    //! \param func The functor to bind.
    //! \tparam F The type of the functor.
    template <typename F> void bind(std::string const &name, F func) {
        disp_->bind(name, func);
    }

    //! \brief Sets the exception behavior in handlers. By default,
    //! handlers throwing will crash the server. If suppressing is on,
    //! the server will try to gather textual data and return it to
    //! the client as an error response.
    //! \note Setting this flag only affects subsequent connections.
    void suppress_exceptions(bool suppress);

    //! \brief Stops the server.
    //! \note This should not be called from worker threads.
    void stop();

    //! \brief Closes all sessions gracefully.
    void close_sessions();

    friend class detail::server_session;

private:
	CALLME_DECL_PIMPL(180)
    std::shared_ptr<dispatcher> disp_;
};

} /* callme */

#endif /* end of include guard: SERVER_H_S0HB5KXY */