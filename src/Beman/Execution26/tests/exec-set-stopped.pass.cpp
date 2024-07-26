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

    struct receiver_throwing
    {
        auto set_stopped() -> void {}
    };


    template <typename R>
    auto test_callable() -> void
    {
        // can be called with non-const rvalue receiver
        static_assert(requires{ test_std::set_stopped(std::declval<R>()); });
        static_assert(requires{ test_std::set_stopped(std::declval<R&&>()); });

        // cannot be called with const or lvalue receiver
        static_assert(not requires{ test_std::set_stopped(std::declval<R const>()); });
        static_assert(not requires{ test_std::set_stopped(std::declval<R const&&>()); });
        static_assert(not requires{ test_std::set_stopped(std::declval<R&>()); });
        static_assert(not requires{ test_std::set_stopped(std::declval<R const&>()); });
        static_assert(not requires{ test_std::set_stopped(std::declval<R volatile&>()); });
        static_assert(not requires{ test_std::set_stopped(std::declval<R const volatile&>()); });
    }

    template <typename R>
    auto test_noexcept() -> void
    {
        static_assert(not requires{ test_std::set_stopped(R()); });
    }
}

// ----------------------------------------------------------------------------

auto main() -> int
{
    static_assert(std::semiregular<test_std::set_stopped_t>);
    static_assert(std::same_as<test_std::set_stopped_t const, decltype(test_std::set_stopped)>);

    test_callable<receiver>();
    test_noexcept<receiver_throwing>();

    bool called{false};
    assert(not called);
    test_std::set_stopped(receiver{&called});
    assert(called);

}
