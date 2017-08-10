#!/usr/bin/env bash

echo ""
echo "Building CPP..."
echo ""
cd cpp
cmake .
make clean
make
cd -
echo ""

echo "Executing CPP unit tests..."
cd cpp/common/utst/
echo `pwd`
./tests
ret=$?
if [ "$ret" = "0" ]; then
    echo "CPP UTESTS SUCCESS!!!!"
else
    echo "CPP UTESTS FAILED!!!!!"
    exit 1 
fi 
cd -
echo ""
