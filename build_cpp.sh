#!/usr/bin/env bash


build_cpp() {
    echo ""
    echo "Building CPP..."
    echo ""
    cd cpp
    cmake .
    make clean
    make
    cd -
    echo ""
}

execute_unit_tests_cpp() {
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
}

build_cpp
execute_unit_tests_cpp

sleep 2
cd cpp/st/
./st &
server_pid=$!
cd -
sleep 2


cd tst
pytest
ret=$?
if [ "$ret" = "0" ]; then
    echo "CPP ST FUNCTIONAL SUCCESS!!!!"
else
    echo "CPP ST FUNCTIONAL FAILED!!!!!"
    exit 1 
fi 
cd -

kill $server_pid

sleep 2
cd cpp/mt/
./mt &
server_pid=$!
cd -
sleep 2


cd tst
pytest
ret=$?
if [ "$ret" = "0" ]; then
    echo "CPP MT FUNCTIONAL SUCCESS!!!!"
else
    echo "CPP MT FUNCTIONAL FAILED!!!!!"
    exit 1 
fi 
cd -

kill $server_pid



