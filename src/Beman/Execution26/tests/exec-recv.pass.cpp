// src/Beman/Execution26/tests/exec-recv.pass.cpp                     -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Beman/Execution26/execution.hpp>
#include "test/execution.hpp"

// ----------------------------------------------------------------------------

namespace
{
    struct base {};
    struct derived: test_ex::receiver_t {};

    struct no_receiver_concept
    {
    };
    struct receiver_concept_not_deriving_from_receiver_t
    {
        using receiver_concept = base;
    };
    
    struct no_get_env;
    struct non_env
    {
        friend struct no_get_env;
    private:
        ~non_env() {}
    };
    struct no_get_env
    {
        using receiver_concept = test_ex::receiver_t;
        auto get_env() const noexcept -> non_env const& { static non_env rc; return rc; }
    };

    struct not_move_constructible
    {
        using receiver_concept = test_ex::receiver_t;
        not_move_constructible() = default;
        not_move_constructible(not_move_constructible const&) = default;
        not_move_constructible(not_move_constructible&&) = delete;
    };
    struct not_copy_constructible
    {
        using receiver_concept = test_ex::receiver_t;
        not_copy_constructible() = default;
        not_copy_constructible(not_copy_constructible const&) = delete;
        not_copy_constructible(not_copy_constructible&&) = default;
    };

    struct receiver_final final
    {
        using receiver_concept = test_ex::receiver_t;
    };
    struct receiver_base
    {
        using receiver_concept = test_ex::receiver_t;
    };
    struct receiver_derived
    {
        using receiver_concept = derived;
    };
}

auto main() -> int
{
    static_assert(not test_ex::receiver<no_receiver_concept>);
    static_assert(not test_ex::receiver<receiver_concept_not_deriving_from_receiver_t>);
    static_assert(not test_ex::receiver<no_get_env>);
    static_assert(not test_ex::receiver<not_move_constructible>);
    static_assert(not test_ex::receiver<not_copy_constructible const&>);
    static_assert(not test_ex::receiver<not_copy_constructible&>);
    static_assert(not test_ex::receiver<receiver_final>);

    static_assert(test_ex::receiver<receiver_base>);
    static_assert(test_ex::receiver<receiver_derived>);
}