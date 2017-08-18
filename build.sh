#!/usr/bin/env bash

echo "Building Project..."
echo ""

./build_py.sh
ret=$?
if [ "$ret" != "0" ]; then
    echo "[ERROR]Exiting!!!!"
    exit 1
fi 
./build_go.sh
ret=$?
if [ "$ret" != "0" ]; then
    echo "[ERROR]Exiting!!!!"
    exit 1
fi 
./build_cpp.sh
ret=$?
if [ "$ret" != "0" ]; then
    echo "[ERROR]Exiting!!!!"
    exit 1
fi 










