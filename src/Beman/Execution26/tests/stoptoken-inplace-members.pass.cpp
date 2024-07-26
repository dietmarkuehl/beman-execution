// src/Beman/Execution26/tests/stoptoken-inplace-members.pass.cpp
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "test/execution.hpp"

auto test_inplace_stop_token_swap() -> void
{
    // Plan:
    // - Given two inplace_stop_token objects which don't compare equal but
    //   comparing equal to their respective sources token.
    // - When swapping the two objects.
    // - Then they compare equal to the respective opposite source's  token.
    // Reference: [stoptoken.inplace.members] p1

    ::test_std::inplace_stop_source source1, source2;
    auto token1(source1.get_token());
    auto token2(source2.get_token());

    assert(token1 == source1.get_token());
    assert(token2 == source2.get_token());
    assert(token1 != token2);

    token1.swap(token2);

    assert(token1 == source2.get_token());
    assert(token2 == source1.get_token());
}

auto test_inplace_stop_token_stop_requested() -> void
{
    // Plan:
    // - Given a connected and a disconnected inplace_stop_token.
    // - Then using stop_requested() it return false.
    // - When requesteing stop for the inplace_stop_source.
    // - Then the connected inplace_stop_token returns true from
    //   stop_requested().
    // Reference: [stoptoken.inplace.members] p2

    ::test_std::inplace_stop_source source;
    ::test_std::inplace_stop_token  connected{source.get_token()};
    ::test_std::inplace_stop_token  disconnected;

    assert(connected.stop_requested() == false);
    assert(disconnected.stop_requested() == false);

    source.request_stop();

    assert(connected.stop_requested() == true);
    assert(disconnected.stop_requested() == false);
}

auto test_inplace_stop_token_stop_possible() -> void
{
    // Plan:
    // - Given a connected and a disconnected inplace_stop_token.
    // - Then using stop_possible() it returns false for the
    //   disconnected inplace_stop_token and true for the connected
    //   one.
    // - When requesteing stop for the inplace_stop_source.
    // - Then the results of stop_possible() didn't change.
    // Reference: [stoptoken.inplace.members] p4

    ::test_std::inplace_stop_source source;
    ::test_std::inplace_stop_token  connected{source.get_token()};
    ::test_std::inplace_stop_token  disconnected;

    assert(connected.stop_possible() == true);
    assert(disconnected.stop_possible() == false);

    source.request_stop();

    assert(connected.stop_possible() == true);
    assert(disconnected.stop_requested() == false);
}

auto main() -> int
{
    test_inplace_stop_token_swap();
    test_inplace_stop_token_stop_requested();
    test_inplace_stop_token_stop_possible();
}
