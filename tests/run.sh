#!/bin/sh
set -eu
cd "$(dirname "$0")/.."
BUILD_DIR=$(mktemp -d)
trap 'rm -rf "$BUILD_DIR"' EXIT
for test in sender features; do
    "${CXX:-c++}" -std=c++11 -Wall -Wextra -Werror -Itests/stubs \
        -include tests/stubs/Arduino.h "tests/test_$test.cpp" -o "$BUILD_DIR/$test"
    "$BUILD_DIR/$test"
done
# Parse the actual receiver and generated model headers using native Arduino/CAN
# doubles. This checks C++ syntax, not the ESP32 toolchain or device memory budget.
"${CXX:-c++}" -std=c++11 -Itests/stubs -include tests/stubs/Arduino.h \
    -include cstdint -include cstdarg -x c++ -fsyntax-only \
    ESP32_2_Receiver_TinyML_Guardian/ESP32_2_Receiver_TinyML_Guardian.ino
