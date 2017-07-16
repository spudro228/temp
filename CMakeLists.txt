cmake_minimum_required(VERSION 3.8)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" )
if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_STANDARD C11)
    # do something special for GNU C compiler
endif()

set(CMAKE_C_FLAGS "-Wall")

project(list_usb)
include_directories(/usr/local/include/libusb-1.0)


# ADD libcsptr
add_subdirectory(libcsptr)
include_directories(libcsptr/include)

add_executable(list_usb listdevs.c)


link_directories(/usr/local/lib)
link_libraries(/usr/local/lib)
#target_link_libraries(main "${LIBS_LIB}")
target_link_libraries (list_usb libusb-1.0.so csptr)