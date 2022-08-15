cmake_minimum_required(VERSION 3.14...3.22)

project(ProtobufMessages LANGUAGES CXX)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS signature.proto delta.proto)

add_library(${PROJECT_NAME} STATIC ${PROTO_SRCS} ${PROTO_HDRS})
