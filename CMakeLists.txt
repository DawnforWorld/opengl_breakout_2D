cmake_minimum_required(VERSION 3.10)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 20)

project(main LANGUAGES CXX C)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE headers CONFIGURE_DEPENDS include/*.h include/*.hpp)

add_executable(main ${sources} ${headers})
target_include_directories(main PUBLIC include)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}")

execute_process(COMMAND ${CMAKE_COMMAND} -E rm -rf "${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/resource")
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resource "${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/resource")

add_subdirectory(thirdparty)
target_link_libraries(main PUBLIC glm)
target_link_libraries(main PUBLIC glfw)
target_link_libraries(main PUBLIC glad)
