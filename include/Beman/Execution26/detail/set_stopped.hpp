// include/Beman/Execution26/detail/set_stopped.hpp                   -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef INCLUDED_BEMAN_EXECUTION26_DETAIL_SET_STOPPED
#define INCLUDED_BEMAN_EXECUTION26_DETAIL_SET_STOPPED

// ----------------------------------------------------------------------------

namespace Beman::Execution26
{
    struct set_stopped_t
    {
        #if defined(BEMAN_EXECUTION26_HAS_DELETED_MESSAGE)
            // see set_value for details
        template <typename Receiver>
        auto operator()(Receiver&) const -> void
            = delete("set_stopped requires the receiver to be passed as non-const rvalue");
        template <typename Receiver>
        auto operator()(Receiver const&&) const -> void
            = delete("set_stopped requires the receiver to be passed as non-const rvalue");
        #endif

        template <typename Receiver>
        auto operator()(Receiver&& receiver) const -> void
            //-dk:TODO should this operation be noexcept?
            #if not defined(BEMAN_EXECUTION26_HAS_DELETED_MESSAGE) and false
                // see set_value for details
            requires(
                not std::is_lvalue_reference_v<Receiver>
                && not std::is_const_v<std::remove_reference_t<Receiver>>
                && noexcept(std::declval<Receiver>().set_stopped())
            )
            #endif
        {
            static_assert(not std::is_lvalue_reference_v<Receiver>,
                          "set_stopped requires the receiver to be passed as non-const rvalue");
            static_assert(not std::is_const_v<std::remove_reference_t<Receiver>>,
                          "set_stopped requires the receiver to be passed as non-const rvalue");

            static_assert(noexcept(std::forward<Receiver>(receiver).set_stopped()),
                          "the call to receiver.set_stopped() has to be noexcept");
            std::forward<Receiver>(receiver).set_stopped();
        }
    };

    inline constexpr set_stopped_t set_stopped{};
}

// ----------------------------------------------------------------------------

#endif
