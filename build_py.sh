#!/usr/bin/env bash

echo ""
echo "Building PYTHON..."
echo ""

echo ""
echo "Building PYTHON unit tests..."
echo ""

echo ""
echo "Executing PYTHON unit tests..."
cd py/common/utst/
export PYTHONPATH=../
pytest
ret=$?
if [ "$ret" = "0" ]; then
    echo "PY UTESTS SUCCESS!!!!"
else
    echo "PY UTESTS FAILED!!!!!"
    exit 1 
fi 
cd -
echo ""


sleep 2
cd py/st/
export PYTHONPATH=../common/
python server.py &
server_pid=$!
cd -
sleep 2


cd tst
pytest
ret=$?
if [ "$ret" = "0" ]; then
    echo "PY ST FUNCTIONAL SUCCESS!!!!"
else
    echo "PY ST FUNCTIONAL FAILED!!!!!"
    exit 1 
fi 
cd -

kill $server_pid

sleep 2
cd py/mt/
export PYTHONPATH=../common/
python server.py &
server_pid=$!
cd -
sleep 2


cd tst
pytest
ret=$?
if [ "$ret" = "0" ]; then
    echo "PY MT FUNCTIONAL SUCCESS!!!!"
else
    echo "PY MT FUNCTIONAL FAILED!!!!!"
    exit 1 
fi 
cd -

kill $server_pid
