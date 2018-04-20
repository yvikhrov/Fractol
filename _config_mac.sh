#!/bin/bash
set -e

CMAKE=cmake
# PROJECT_TYPE="Unix Makefiles"
PROJECT_TYPE="Xcode"

FULL_PATH=$(pwd)

if [ "$PROJECT_TYPE" != "Xcode" ]; then
	BUILD_DIR="buildUnix"
else
	BUILD_DIR="buildXcode"
fi

FULL_BUILD_PATH=$FULL_PATH/$BUILD_DIR

mkdir -p $FULL_BUILD_PATH

cd $FULL_BUILD_PATH

$CMAKE -G "$PROJECT_TYPE" \
    -DFULL_PATH="$FULL_PATH" \
    ..
