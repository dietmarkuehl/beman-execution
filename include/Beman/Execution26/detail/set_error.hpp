// inclue/Beman/Execution26/detail/set_error.hpp -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef INCLUDED_BEMAN_EXECUTION26_DETAIL_SET_ERROR
#define INCLUDED_BEMAN_EXECUTION26_DETAIL_SET_ERROR

// ----------------------------------------------------------------------------

namespace Beman::Execution26
{
    struct set_error_t
    {
        #if defined(BEMAN_EXECUTION26_HAS_DELETED_MESSAGE)
            // see set_value for details
        template <typename Receiver, typename Error>
        auto operator()(Receiver&, Error&&) const -> void
            = delete("set_error requires the receiver to be passed as non-const rvalue");
        template <typename Receiver, typename Error>
        auto operator()(Receiver const&&, Error&&) const -> void
            = delete("set_error requires the receiver to be passed as non-const rvalue");
        #endif

        template <typename Receiver, typename Error>
        auto operator()(Receiver&& receiver, Error&& error) const -> void
            //-dk:TODO should this operation be noexcept?
            #if not defined(BEMAN_EXECUTION26_HAS_DELETED_MESSAGE) and false
                // see set_value for details
            requires(
                not std::is_lvalue_reference_v<Receiver>
                && not std::is_const_v<std::remove_reference_t<Receiver>>
                && noexcept(std::declval<Receiver>().set_error(std::declval<Error>()))
            )
            #endif
        {
            static_assert(not std::is_lvalue_reference_v<Receiver>,
                          "set_error requires the receiver to be passed as non-const rvalue");
            static_assert(not std::is_const_v<std::remove_reference_t<Receiver>>,
                          "set_error requires the receiver to be passed as non-const rvalue");

            static_assert(noexcept(std::forward<Receiver>(receiver).set_error(std::forward<Error>(error))),
                          "the call to receiver.set_error(e) has to be noexcept");
            std::forward<Receiver>(receiver).set_error(std::forward<Error>(error));
        }
    };
    
    inline constexpr set_error_t set_error{};
}

// ----------------------------------------------------------------------------

#endif
