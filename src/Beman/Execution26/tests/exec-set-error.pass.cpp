// src/Beman/Execution26/tests/exec-set-error.pass.cpp                      -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Beman/Execution26/execution.hpp>
#include "test/execution.hpp"
#include <concepts>
#include <utility>

// ----------------------------------------------------------------------------

namespace
{
    struct arg { int value; };

    struct receiver
    {
        template <typename Error>
        auto set_error(Error&&) noexcept -> void {}
        auto set_error(arg a) noexcept -> void
        {
            assert(a.value == 43);
        }
    };

    template <typename R>
    void test_callable()
    {
        static_assert(requires{ test_ex::set_error(std::declval<R>(), 42); });
        static_assert(not requires{ test_ex::set_error(std::declval<R const>(), 42); });
        static_assert(requires{ test_ex::set_error(std::declval<R&&>(), 42); });
        static_assert(not requires{ test_ex::set_error(std::declval<R const&&>(), 42); });
        static_assert(not requires{ test_ex::set_error(std::declval<R&>(), 42); });
        static_assert(not requires{ test_ex::set_error(std::declval<R const&>(), 42); });
        static_assert(not requires{ test_ex::set_error(std::declval<R volatile&>(), 42); });
        static_assert(not requires{ test_ex::set_error(std::declval<R const volatile&>(), 42); });
    }
}

auto main() -> int
{
    static_assert(std::semiregular<test_ex::set_error_t>);
    static_assert(std::same_as<test_ex::set_error_t const, decltype(test_ex::set_error)>);

    #if defined(BEMAN_EXECUTION26_HAS_DELETED_MESSAGE)
    //-dk:TODO add negative compilation tests
    test_callable<receiver>();
    #endif

    test_ex::set_error(receiver{}, 42);
    test_ex::set_error(receiver{}, arg{43});
}