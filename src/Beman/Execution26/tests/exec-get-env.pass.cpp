// src/Beman/Execution26/tests/exec-get-env.pass.cpp                  -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Beman/Execution26/execution.hpp>
#include "test/execution.hpp"
#include <concepts>
#include <utility>

// ----------------------------------------------------------------------------

namespace
{
    struct with_non_env;
    struct non_env
    {
    private:
        friend struct with_non_env;
        ~non_env() = default;
    };
    struct with_non_env
    {
        auto get_env() const noexcept -> non_env& { static non_env rc{}; return rc; }
    };

    struct other_env {};
    struct test_env {};
    struct non_const
    {
        auto get_env() -> test_env { return test_env{}; }
    };

    template <typename Env, bool Noexcept = true>
    struct normal
    {
        auto get_env() const noexcept(Noexcept) -> Env { return Env{}; }
        auto get_env() noexcept(Noexcept) -> Env { return other_env{}; }
    };
}

auto main() -> int
{
    static_assert(std::semiregular<test_std::empty_env>);

    static_assert(std::semiregular<test_std::get_env_t>);
    static_assert(std::same_as<test_std::get_env_t const, decltype(test_std::get_env)>);

    auto e0 = test_std::get_env(0);
    static_assert(std::same_as<test_std::empty_env, decltype(e0)>);
    auto e1 = test_std::get_env(non_const{});
    static_assert(std::same_as<test_std::empty_env, decltype(e1)>);
    auto e2 = test_std::get_env(normal<test_env>{});
    static_assert(std::same_as<test_env, decltype(e2)>);
    //-dk:TODO add negative compilation test: auto e3 = test_std::get_env(normal<test_env, false>{});
    //-dk:TODO add negative compilation test: auto e4 = test_std::get_env(with_non_env{});
}
