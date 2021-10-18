#!/bin/bash

rm -rf build && mkdir build && cd build && cmake .. && echo "Using $(nproc) process to make" && make -j$(nproc)