﻿# CMakeList.txt : CMake project for LumenLogger, include source and define
# project specific logic here.

cmake_minimum_required (VERSION 3.8)

set (PUBLIC_HEADERS "include")

# Add source to this project's executable.
add_library (LumenLogger "logger.cc" "${PUBLIC_HEADERS}/lumen_logger/logger.h")

# TODO: Add tests and install targets if needed.
target_include_directories (LumenLogger PUBLIC ${PUBLIC_HEADERS})
target_link_libraries (LumenLogger spdlog_header_only)
