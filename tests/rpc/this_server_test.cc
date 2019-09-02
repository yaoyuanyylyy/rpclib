#include "gtest/gtest.h"

#include "rpcpp/client.h"
#include "rpcpp/server.h"
#include "rpcpp/this_server.h"

#include "testutils.h"

using namespace rpc::testutils;
using namespace rpc;

static RPCLIB_CONSTEXPR uint16_t test_port = rpc::constants::DEFAULT_PORT;

class this_server_test : public testing::Test {
public:
    this_server_test()
        : s(test_port),
          c1("127.0.0.1", test_port),
          c2("127.0.0.1", test_port) {}

protected:
    rpc::server s;
    rpc::client c1;
    rpc::client c2;
};

TEST_F(this_server_test, stop) {
    s.bind("stop_server", []() { rpc::this_server().stop(); });
    s.async_run();
    c1.call("stop_server");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    EXPECT_EQ(c1.get_connection_state(),
              client::connection_state::disconnected);
    EXPECT_EQ(c2.get_connection_state(),
              client::connection_state::disconnected);
}
