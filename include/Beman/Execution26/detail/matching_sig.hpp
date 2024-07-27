// include/Beman/Execution26/detail/matching_sig.hpp                  -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef INCLUDED_BEMAN_EXECUTION26_DETAIL_MATCHING_SIG
#define INCLUDED_BEMAN_EXECUTION26_DETAIL_MATCHING_SIG

#include <concepts>

// ----------------------------------------------------------------------------

namespace Beman::Execution26::Detail
{
    template <typename Fun>
    struct matching_sig_transform
    {
        using type = Fun;
    };
    template <typename Return, typename... Args>
    struct matching_sig_transform<Return(Args...)>
    {
        using type = Return(Args&&...);
    };

    template <typename Fun1, typename Fun2>
    inline constexpr bool matching_sig
        = ::std::same_as<
            typename ::Beman::Execution26::Detail::matching_sig_transform<Fun1>::type,
            typename ::Beman::Execution26::Detail::matching_sig_transform<Fun2>::type
            >
        ;
}

// ----------------------------------------------------------------------------

#endif
