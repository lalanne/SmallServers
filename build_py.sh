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
