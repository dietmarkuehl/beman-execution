// src/Beman/Execution26/tests/exec-opstate-start.pass.cpp            -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Beman/Execution26/execution.hpp>
#include <test/execution.hpp>

#include <utility>

// ----------------------------------------------------------------------------

namespace
{
    struct receiver
    {
        int value{};
        auto set_value(int value) noexcept -> void { this->value = value; }
    };

    struct non_opstate
    {
    };

    template <bool Noexcept>
    struct opstate
    {
        receiver* rcvr;
        auto start() const noexcept(Noexcept) -> void
        {
            test_std::set_value(std::move(*rcvr), 42);
        }
    };

    template <typename State>
    auto test_start_argument_type()
    {
        receiver rcvr{};
        State state{&rcvr};
        receiver crcvr{};
        State const cstate{&crcvr};

        static_assert(requires{ test_std::start(state); });
        static_assert(requires{ test_std::start(cstate); });

        static_assert(not requires{ test_std::start(State(&rcvr)); });
        static_assert(not requires{ test_std::start(std::move(state)); });
        static_assert(not requires{ test_std::start(std::move(cstate)); });
    }

    template <typename State>
    auto test_start_member()
    {
        State state;
        static_assert(not requires{ test_std::start(state); });
        State cstate;
        static_assert(not requires{ test_std::start(cstate); });
    }

    template <typename State>
    auto test_start_noexcept()
    {
        State state;
        static_assert(not requires{ test_std::start(state); });
        State cstate;
        static_assert(not requires{ test_std::start(cstate); });
    }

    template <typename State>
    auto test_start_call()
    {
        receiver rcvr{};
        State state{&rcvr};
        receiver crcvr{};
        State const cstate{&crcvr};

        assert(rcvr.value == 0);
        test_std::start(state);
        assert(rcvr.value == 42);

        assert(crcvr.value == 0);
        test_std::start(cstate);
        assert(crcvr.value == 42);
    }
}

auto main() -> int
{
    static_assert(std::same_as<test_std::start_t const, decltype(test_std::start)>);

    test_start_argument_type<opstate<true>>();
    test_start_member<non_opstate>();
    test_start_noexcept<opstate<false>>();
    test_start_call<opstate<true>>();
}