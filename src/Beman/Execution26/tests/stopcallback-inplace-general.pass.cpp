// src/Beman/Execution26/tests/stopcallback-inplace-general.pass.cpp
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Beman/Execution26/stop_token.hpp>
#include "test/execution.hpp"
#include <concepts>
#include <type_traits>

auto main() -> int
{
    // Reference: [stopcallback.inplace.general]

    struct Callback
    {
        auto operator()() {};
    };

    using CB = ::test_std::inplace_stop_callback<Callback>;
    static_assert(::std::same_as<CB::callback_type, Callback>);
    static_assert(::std::destructible<CB>);
    static_assert(not ::std::move_constructible<CB>);
    static_assert(not ::std::copy_constructible<CB>);
    static_assert(not ::std::is_move_assignable_v<CB>);
    static_assert(not ::std::is_copy_assignable_v<CB>);

    Callback callback;
    ::test_std::inplace_stop_callback cb(::test_std::inplace_stop_token(), callback);
    static_assert(::std::same_as<decltype(cb), CB>);
}
