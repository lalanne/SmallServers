#!/usr/bin/env bash

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
cd .
path=`pwd`
echo $path
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
