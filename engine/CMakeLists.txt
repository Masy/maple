project(maple_engine)

add_library(maple_engine STATIC SHARED)
add_library(Maple::engine ALIAS maple_engine)

target_include_directories(maple_engine PUBLIC include)

file(GLOB_RECURSE SOURCES src/ *.cpp)
file(GLOB_RECURSE HEADERS include/ *.hpp)
target_sources(maple_engine PRIVATE ${SOURCES})
target_sources(maple_engine PUBLIC ${HEADERS})

target_link_libraries(maple_engine PUBLIC
        Maple::math)

if (MSVC)
    target_compile_options(maple_engine PRIVATE -W4 -WX)
else()
    target_compile_options(maple_engine PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()