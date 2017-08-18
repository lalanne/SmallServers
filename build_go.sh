#!/usr/bin/env bash

echo ""
echo "Building GO..."
cd go/
path=`pwd`
echo $path
export GOPATH=$path
go get golang.org/x/net/html/charset
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

sleep 2
cd go/bin/
./st 127.0.0.1 4060&
server_pid=$!
cd -
sleep 2


cd tst
pytest -q --cmdopt=4060
ret=$?
if [ "$ret" = "0" ]; then
    echo "GO ST FUNCTIONAL SUCCESS!!!!"
else
    echo "GO ST FUNCTIONAL FAILED!!!!!"
    exit 1 
fi 
cd -

kill $server_pid

sleep 2
cd go/bin/
./mt 127.0.0.1 4070&
server_pid=$!
cd -
sleep 2


cd tst
pytest -q --cmdopt=4070
ret=$?
if [ "$ret" = "0" ]; then
    echo "GO MT FUNCTIONAL SUCCESS!!!!"
else
    echo "GO MT FUNCTIONAL FAILED!!!!!"
    exit 1 
fi 
cd -

kill $server_pid



