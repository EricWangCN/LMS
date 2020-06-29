cmake_minimum_required(VERSION 3.16)
project(LMS)

set(CMAKE_CXX_STANDARD 14)

add_executable(LMS main.cpp matrix.h matrix-impl.h usingdeclare.h constants.h vector.h vector-impl.h lms.h lms-impl.h)