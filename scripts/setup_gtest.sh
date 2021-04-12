#!/usr/bin/env bash

SUDO=sudo
if [ "$GITHUB_ACTOR" == "nektos/act" ]; then
    echo "Running in 'act' container, not using sudo"
    SUDO=""
fi

echo "Updating packages"
$SUDO apt-get update

echo "Install gtests and gmock"
$SUDO apt-get install -y \
    libgtest-dev \
    libgmock-dev

echo "Copy libs to /usr/local/lib"
$SUDO cp -u /usr/lib/x86_64-linux-gnu/libgtest.a      /usr/local/lib/
$SUDO cp -u /usr/lib/x86_64-linux-gnu/libgtest_main.a /usr/local/lib/
$SUDO cp -u /usr/lib/x86_64-linux-gnu/libgmock.a      /usr/local/lib/
$SUDO cp -u /usr/lib/x86_64-linux-gnu/libgmock_main.a /usr/local/lib/