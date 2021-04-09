#!/usr/bin/env bash

SUDO=sudo
if [ "$GITHUB_ACTOR" == "nektos/act" ]; then
    echo "Running in 'act' container, not using sudo"
    SUDO=""
fi

echo "Updating packages"
$SUDO apt-get update
echo "Install gtests and cmake"
$SUDO apt-get install -y \
    libgtest-dev \
    cmake

echo "Navigate to gtest src"
$SUDO cd /usr/src/gtest

echo "Build gtests libraries"
$SUDO cmake CMakeLists.txt
$SUDO make

echo "Copy gtest libs to indicated folders"
$SUDO mkdir -p /usr/lib/
$SUDO cp -u lib/*.a /usr/lib/