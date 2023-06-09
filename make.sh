#!/bin/bash

DIR=`pwd`

mkdir -p build
cd build

echo "install dir: ${DIR} -- $#"

cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=${DIR} -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..

make -j4 && make install

cd ..
