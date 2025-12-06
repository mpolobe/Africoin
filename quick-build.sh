#!/bin/bash
# Quick rebuild script (skips clone and modifications)

set -e

if [ ! -d "africoin-core" ]; then
    echo "Error: africoin-core directory not found. Run build.sh first."
    exit 1
fi

cd africoin-core

echo "Quick rebuild of Africoin Core..."

make clean
make -j4

echo "Build complete!"

./src/africoin-cli --version
./src/africoind --version
