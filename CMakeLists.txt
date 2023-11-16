cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(pytorch-verilog)

find_package(verilator HINTS $ENV{VERILATOR_ROOT})
find_package(Torch REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(main main.cpp)
set_property(TARGET main PROPERTY CXX_STANDARD 17)
verilate(main SOURCES adder.v TRACE VERILATOR_ARGS --x-assign unique --x-initial unique)
target_link_libraries(main PUBLIC "${TORCH_LIBRARIES}")

# The following code block is suggested to be used on Windows.
# According to https://github.com/pytorch/pytorch/issues/25457,
# the DLLs need to be copied to avoid memory errors.
if (MSVC)
  file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
  add_custom_command(TARGET example-app
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_if_different
                     ${TORCH_DLLS}
                     $<TARGET_FILE_DIR:example-app>)
endif (MSVC)
