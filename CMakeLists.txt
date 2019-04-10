CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

set(CMAKE_OSX_SYSROOT macosx10.14)
set(CMAKE_CXX_STANDARD 14)

project("NPDFApp")

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.11")

find_library(CORE_GRAPHICS CoreGraphics)
find_library(CORE_FOUNDATION CoreFoundation)

if (NOT CORE_GRAPHICS)
	message(FATAL_ERROR "CoreFoundation not found")
endif()

if (NOT CORE_FOUNDATION)
	message(FATAL_ERROR "CoreFoundation not found")
endif()

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC "${SDK_PATH}/pdfium/include/")
target_link_libraries(${PROJECT_NAME} ${CORE_FOUNDATION}
									  ${CORE_GRAPHICS}
									  "${SDK_PATH}/pdfium/lib/libpdfiumd.a")

