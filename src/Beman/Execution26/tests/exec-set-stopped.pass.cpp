// src/Beman/Execution26/tests/exec-set-stopped.pass.cpp              -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Beman/Execution26/execution.hpp>
#include "test/execution.hpp"
#include <concepts>
#include <utility>

namespace
{
    struct receiver
    {
        bool* called;
        auto set_stopped() noexcept -> void
        {
            *called = true;
        }
    };
}

// ----------------------------------------------------------------------------

auto main() -> int
{
    static_assert(std::semiregular<test_ex::set_stopped_t>);
    static_assert(std::same_as<test_ex::set_stopped_t const, decltype(test_ex::set_stopped)>);

    bool called{false};
    assert(not called);
    test_ex::set_stopped(receiver{&called});
    assert(called);

    #if 0
    //-dk:TODO set up negative compilation tests
    receiver r{&called};
    test_ex::set_stopped(r);
    receiver const rc{&called};
    test_ex::set_stopped(std::move(rc));
    #endif
}