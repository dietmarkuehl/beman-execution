// include/Beman/Execution26/detail/stop_callback_for_t.hpp           -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef INCLUDED_BEMAN_EXECUTION26_DETAIL_STOP_CALLBACK_FOR
#define INCLUDED_BEMAN_EXECUTION26_DETAIL_STOP_CALLBACK_FOR

#include <concepts>

// ----------------------------------------------------------------------------

namespace Beman::Execution26
{
    template<class Token, class CallbackFun>
    using stop_callback_for_t = Token::template callback_type<CallbackFun>;
}

namespace Beman::Execution26::Detail
{
    template<typename CallbackFun, typename Token, typename Initializer = CallbackFun>
    concept stoppable_callback_for
        =  ::std::invocable<CallbackFun>
        && ::std::constructible_from<CallbackFun, Initializer>
        && requires { typename ::Beman::Execution26::stop_callback_for_t<Token, CallbackFun>; }
        && ::std::constructible_from<::Beman::Execution26::stop_callback_for_t<Token, CallbackFun>,
                                     Token,
                                     Initializer>
        && ::std::constructible_from<::Beman::Execution26::stop_callback_for_t<Token, CallbackFun>,
                                     Token&,
                                     Initializer>
        && ::std::constructible_from<::Beman::Execution26::stop_callback_for_t<Token, CallbackFun>,
                                     Token const&,
                                     Initializer>
        ;
}

// ----------------------------------------------------------------------------

#endif
