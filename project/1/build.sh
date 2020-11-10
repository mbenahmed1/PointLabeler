#!/bin/bash
mkdir build
cd build
cmake ..
make -j4
echo ""
echo "Goto build folder and run ./PointLabeler"
echo ""