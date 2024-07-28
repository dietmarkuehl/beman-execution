// src/Beman/Execution26/tests/exec-opstate.pass.cpp                  -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Beman/Execution26/detail/operation_state.hpp>
#include <test/execution.hpp>

// ----------------------------------------------------------------------------

namespace
{
    struct base {};
    struct opstate_base: test_std::operation_state_t {};

    struct non_operation_state {};
    struct no_tag
    {
        using operation_state_concept = test_std::operation_state_t;
        auto start() noexcept {}
    };
    struct no_start
    {
        using operation_state_concept = test_std::operation_state_t;
        auto start() noexcept {}
    };

    template <bool Noexcept, typename Tag>
    struct operation_state
    {
        using operation_state_concept = Tag;
        auto start() noexcept(Noexcept) {}
    };

    template <bool Expect, typename State>
    auto test_operation_state()
    {
        static_assert(Expect == test_std::operation_state<State>);
    }
}

auto main() -> int
{
    test_std::operation_state_t state_tag{};
    (void)state_tag;

    test_operation_state<false, non_operation_state>();
    test_operation_state<true, no_tag>();
    test_operation_state<true, no_start>();

    test_operation_state<true, operation_state<true, test_std::operation_state_t>>();
    test_operation_state<false, operation_state<false, test_std::operation_state_t>>();
    test_operation_state<false, operation_state<true, base>>();
    test_operation_state<true, operation_state<true, opstate_base>>();
    test_operation_state<false, operation_state<true, test_std::operation_state_t>&>();
}