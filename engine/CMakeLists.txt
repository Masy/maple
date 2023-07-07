project(maple_engine)

add_library(maple_engine STATIC SHARED)
add_library(Maple::engine ALIAS maple_engine)

target_include_directories(maple_engine PUBLIC include)

file(GLOB_RECURSE SOURCES src/ *.cpp)
file(GLOB_RECURSE HEADERS include/ *.hpp)
target_sources(maple_engine PRIVATE ${SOURCES} .manifest)
target_sources(maple_engine PUBLIC ${HEADERS})

target_link_libraries(maple_engine PUBLIC
        Maple::math)

if (WIN32)
    # We need features of the windows api that were added with windows 10
    target_compile_definitions(maple_engine PRIVATE WINVER=0x0A00)
endif()

if (MSVC)
    target_compile_options(maple_engine PRIVATE -W4)
else()
    target_compile_options(maple_engine PRIVATE -Wall -Wextra -Wduplicated-branches -Wlogical-op -Wrestrict -Wnull-dereference -Wduplicated-cond -flarge-source-files)
endif()