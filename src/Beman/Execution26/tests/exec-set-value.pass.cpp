// src/Beman/Execution26/tests/exec.set.value.pass.cpp                -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Beman/Execution26/execution.hpp>
#include <concepts>
#include <string>
#include <type_traits>
#include <utility>
#include "test/execution.hpp"

// ----------------------------------------------------------------------------

namespace
{
    template <int> struct arg {};
    struct throws
    {
        throws() = default;
        throws(throws const&) {}
    };
    struct receiver
    {
        template <typename ...T>
        auto set_value(T&&...) noexcept -> void {}
        auto set_value(throws) noexcept -> void {}
        auto set_value(int i, bool b, double d) noexcept
        {
            assert(i == 42);
            assert(b == true);
            assert(d == 123.75);
        }
    };

    template <typename R>
    void test_callable()
    {
        static_assert(requires{ test_ex::set_value(std::declval<R>()); });
        static_assert(not requires{ test_ex::set_value(std::declval<R const>()); });
        static_assert(requires{ test_ex::set_value(std::declval<R&&>()); });
        static_assert(not requires{ test_ex::set_value(std::declval<R const&&>()); });
        static_assert(not requires{ test_ex::set_value(std::declval<R&>()); });
        static_assert(not requires{ test_ex::set_value(std::declval<R const&>()); });
        static_assert(not requires{ test_ex::set_value(std::declval<R volatile&>()); });
        static_assert(not requires{ test_ex::set_value(std::declval<R const volatile&>()); });
    }
}

auto main() -> int
{
    static_assert(std::semiregular<test_ex::set_value_t>);
    static_assert(std::same_as<test_ex::set_value_t const, decltype(test_ex::set_value)>);

    #if defined(BEMAN_EXECUTION26_HAS_DELETED_MESSAGE)
    //-dk:TODO add negative compilation tests
    test_callable<receiver>();
    #endif

    test_ex::set_value(receiver{}, 1);
    test_ex::set_value(receiver{}, arg<0>(), arg<1>(), arg<2>(), arg<3>(), arg<4>());
    test_ex::set_value(receiver{}, 42, true, 123.75);
    //-dk:TODO add negative compilation tests: test_ex::set_value(receiver{}, throws());
}

