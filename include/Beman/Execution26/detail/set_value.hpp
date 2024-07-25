// include/Beman/Execution26/detail/set_value.hpp -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef INCLUDED_BEMAN_EXECUTION26_DETAIL_SET_VALUE
#define INCLUDED_BEMAN_EXECUTION26_DETAIL_SET_VALUE

#include <type_traits>
#include <utility>

// ----------------------------------------------------------------------------

namespace Beman::Execution26
{
    struct set_value_t
    {
        #if defined(BEMAN_EXECUTION26_HAS_DELETED_MESSAGE)
	    //-dk:TODO I think this is the preferred option: it fails
	    // the compilation with a suitable message while also being
	    // detectable if necessary.  However, overload resolution
	    // doesn't just remove the overload trying to look for
	    // other overloads and eventually failing. It isn't available
	    //  with all compilers, yet.
        template <typename Receiver, typename... Args>
        auto operator()(Receiver&, Args&&...) const -> void
            = delete("set_value requires the receiver to be passed as non-const rvalue");
        template <typename Receiver, typename... Args>
        auto operator()(Receiver const&&, Args&&...) const -> void
            = delete("set_value requires the receiver to be passed as non-const rvalue");
        #endif

        template <typename Receiver, typename... Args>
            #if not defined(BEMAN_EXECUTION26_HAS_DELETED_MESSAGE) and false
	        //-dk:TODO Using constraints makes the call ill-formed
	        // as no other overload can be found. Using this approach
	        // makes the failure detectable but there is no way to
	        // associate a suitable message. Hence, this approach is
            // explicitly disabled.
            requires(
                not std::is_lvalue_reference_v<Receiver>
                && not std::is_const_v<std::remove_reference_t<Receiver>>
                && noexcept(std::declval<Receiver>().set_value(std::declval<Args...>()))
            )
        #endif
        auto operator()(Receiver&& receiver, Args&&... args) const -> void
            //-dk:TODO should this operator be noexcept? 
        {
            // Using static_asserts allows providing a suitable message
            // why the compilation failed. Sadly, it can't be detected
            // whether the operation is available. Currently, this is
            // the only approach which can provide a message, though.
            static_assert(not std::is_lvalue_reference_v<Receiver>,
                          "set_value requires the receiver to be passed as non-const rvalue");
            static_assert(not std::is_const_v<std::remove_reference_t<Receiver>>,
                          "set_value requires the receiver to be passed as non-const rvalue");

            // This assertion can't be detected through deleted functions.
            // To get a message it is always caught be a static_assert.
            static_assert(noexcept(std::forward<Receiver>(receiver).set_value(std::forward<Args>(args)...)),
                          "the call to receiver.set_value(args...) has to be noexcept");
            std::forward<Receiver>(receiver).set_value(std::forward<Args>(args)...);
        }
    };
    inline constexpr set_value_t set_value{};
}

// ----------------------------------------------------------------------------

#endif
