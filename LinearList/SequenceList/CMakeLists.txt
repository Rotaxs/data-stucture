cmake_minimum_required(VERSION 3.20)

project(
    SequenceList
    VERSION 1.0.0
    LANGUAGES C
)

# ================ SequenceList Library ===================

add_library(sequence_list)

target_compile_features(sequence_list
    PUBLIC 
        c_std_17
)

target_sources(sequence_list
    PUBLIC
        src/sequence_list.c
)

target_include_directories(sequence_list
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ================= SequenceList Demo ==========================

add_executable(sequence_list_demo)

target_sources(sequence_list_demo
    PRIVATE 
        demo/main.c
)

target_link_libraries(sequence_list_demo
    PRIVATE 
        sequence_list
)

# ================= CTEST ==========================

if (BUILD_TESTING)
    add_executable(sequence_list_tests)
    
    target_sources(sequence_list_tests
        PRIVATE 
            tests/test_sequence_list.c
    )

    target_link_libraries(sequence_list_tests
        PRIVATE 
            sequence_list
    )

    foreach (case IN ITEMS insert delete modify query flip handswap)
        add_test(
            NAME sequence_list.${case}
            COMMAND sequence_list_tests ${case}
        )

        set_tests_properties(sequence_list.${case} PROPERTIES
            LABELS "sequence_list"
        )
    endforeach()
endif()
