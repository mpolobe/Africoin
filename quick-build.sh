#!/bin/bash
# Quick rebuild script (skips clone and modifications)

set -e

cd africoin-core

echo "Quick rebuild of Africoin Core..."

make clean
make -j4

echo "Build complete!"

./src/africoin-cli --version
./src/africoind --version
