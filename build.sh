#!/usr/bin/env bash

echo "Building Project..."
echo ""

echo ""
echo "Building CPP..."
echo ""
cd cpp
cmake .
make clean
make
cd -
echo ""

echo ""
echo "Building CPP unit tests..."
cd cpp/common/utst/
cmake .
make clean
make
cd -
echo ""

echo "Executing CPP unit tests..."
cd cpp/common/utst/
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

echo ""
echo "Building GO..."
cd go/
go clean
go install common
go install st
go install mt
cd -
echo ""

echo ""
echo "Building GO unit tests..."
echo ""

echo ""
echo "Executing GO unit tests..."
path=`pwd`
export GOPATH=$path/go/
go test common -cover
ret=$?
if [ "$ret" = "0" ]; then
    echo "GO UTESTS SUCCESS!!!!"
else
    echo "GO UTESTS FAILED!!!!!"
    exit 1 
fi 
cd -
echo ""










