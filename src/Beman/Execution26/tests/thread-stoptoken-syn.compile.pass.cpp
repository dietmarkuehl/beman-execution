// src/Beman/Execution26/tests/thread-stoptoken-syn.compile.pass.cpp
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Beman/Execution26/stop_token.hpp>
#include "test/execution.hpp"

namespace
{
    template <typename> void type_exists() {}

    struct test_token
    {
        template <typename CallbackFn>
        using callback_type = ::test_std::stop_callback<CallbackFn>;
    };
}

auto main() -> int
{
    // Plan:
    // - Given a header with the declarations relating to <stop_token>
    // - When trying to access the various names in the header.
    // - Then the compiler should OK doing so.
    // Reference: [thread.stoptoken.syn]

    static_assert((not ::test_detail::stoppable_callback_for<int, int, int>));
    static_assert((not ::test_detail::stoppable_source<int>));

    static_assert((not ::test_std::stoppable_token<int>));
    static_assert((not ::test_std::unstoppable_token<int>));

    type_exists<::test_std::stop_token>();
    type_exists<::test_std::stop_source>();

    type_exists<::test_std::nostopstate_t>();
    (void)::test_std::nostopstate_t();
    static_assert(noexcept(::test_std::nostopstate_t()));
    ::test_std::nostopstate_t const& nostopstate = ::test_std::nostopstate;
    (void)nostopstate;

    type_exists<::test_std::stop_callback<decltype([]{})>>();

    type_exists<::test_std::never_stop_token>();

    type_exists<::test_std::inplace_stop_token>();
    type_exists<::test_std::inplace_stop_source>();
    type_exists<::test_std::inplace_stop_callback<decltype([]{})>>();

    type_exists<::test_std::stop_callback_for_t<test_token, decltype([]{})>>();
}
