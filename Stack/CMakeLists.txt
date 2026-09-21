cmake_minimum_required(VERSION 3.20)

project(
    Stack
    VERSION 1.0.0
    LANGUAGES C
)

# ===================== Library ==================

add_library(stack)

target_compile_features(stack
    PUBLIC
        c_std_17
)

target_sources(stack
    PRIVATE
        src/sequential_stack.c
        src/linked_stack.c
)

target_include_directories(stack
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)


# =================== CTEST =========================

if (BUILD_TESTING)
    add_executable(stack_tests)

    target_sources(stack_tests
        PRIVATE
            tests/test_stack.c
    )

    target_link_libraries(stack_tests
        PRIVATE
            stack
    )

    foreach (case IN ITEMS sequential list) 
        add_test(
            NAME stack.${case}
            COMMAND stack_tests ${case}
        )

        set_tests_properties(stack.${case} PROPERTIES
            LABELS "stack"
        )
    endforeach()

endif()
