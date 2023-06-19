project(maple_math)

add_library(maple_math INTERFACE)
add_library(Maple::math ALIAS maple_math)

target_include_directories(maple_math INTERFACE include)

file(GLOB_RECURSE SOURCES src/ *.cpp)
file(GLOB_RECURSE HEADERS include/ *.hpp)

target_sources(maple_math PRIVATE ${SOURCES})
target_sources(maple_math PUBLIC ${HEADERS})
