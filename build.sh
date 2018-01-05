#!/bin/sh

set -x

SOURCE_DIR=`pwd`
BUILD_DIR=${BUILD_DIR:-../build}
BUILD_TYPE=${BUILD_TYPE:-debug}
INSTALL_DIR=${INSTALL_DIR:-../lua-${BUILD_TYPE}-install}
MUDUO_DIR=${MUDUO_DIR:-${PWD}/$BUILD_DIR/${BUILD_TYPE}-install}

mkdir -p $BUILD_DIR/lua-$BUILD_TYPE\
  && cd $BUILD_DIR/lua-$BUILD_TYPE \
  && cmake \
           -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
           -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR \
           -DMUDUO_PATH=$MUDUO_DIR $SOURCE_DIR \
           -DLUA_INCLUDE_DIR=/usr/include/luajit-2.1 \
           -DLUA_LIBRARY=luajit-5.1 \
  && make $*

# cd $SOURCE_DIR && doxygen

