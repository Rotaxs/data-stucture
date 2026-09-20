cmake_minimum_required(VERSION 3.20)

project(
    LinkedList
    VERSION 1.0.0
    LANGUAGES C
)

# =================== LinkedList Library ===============

add_library(linked_list)

target_compile_features(linked_list
    PUBLIC
        c_std_17
)

target_sources(linked_list
    PRIVATE 
        src/singly_linked_list.c
        src/doubly_linked_list.c
        src/circular_singly_linked_list.c
        src/circular_doubly_linked_list.c
)

target_include_directories(linked_list
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ================= CTEST ==========================

if (BUILD_TESTING)
    add_executable(linked_list_tests)

    target_sources(linked_list_tests
        PRIVATE
            tests/test_linked_list.c
    )

    target_link_libraries(linked_list_tests
        PRIVATE
            linked_list
    )

    foreach (case IN ITEMS singly doubly circular_singly circular_doubly)
        add_test(
            NAME linked_list.${case}
            COMMAND linked_list_tests ${case}
        )

        set_tests_properties(linked_list.${case} PROPERTIES
            LABELS "linked_list"
        )
    endforeach()
endif()
