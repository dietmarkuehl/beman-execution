# Copyright © 2024 Beman Project
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

list(APPEND execution_tests
    utilities.pass
    function-objects.pass
    thread.pass
    thread-stoptoken.pass
    thread-stoptoken-intro.pass
    thread-stoptoken-syn.compile.pass
    stoptoken-concepts.pass
    stoptoken.pass
    stoptoken-general.pass
    stoptoken-mem.pass
    stopsource.pass
    stopsource-general.pass
    stopsource-cons.pass
    stopsource-mem.pass
    stopcallback.pass
    stopcallback-general.pass
    stopcallback-cons.pass
    stoptoken-never.pass
    stoptoken-never-general.pass
    stoptoken-inplace.pass
    stoptoken-inplace-general.pass
    stoptoken-inplace-members.pass
    stopsource-inplace.pass
    stopsource-inplace-general.pass
    stopsource-inplace-cons.pass
    stopsource-inplace-mem.pass
    stopcallback-inplace.pass
    stopcallback-inplace-general.pass
    stopcallback-inplace-cons.pass
)

foreach(test ${execution_tests})
    add_executable(${test} ${test}.cpp)
    add_test(NAME ${test} COMMAND $<TARGET_FILE:${test}>)
endforeach()
