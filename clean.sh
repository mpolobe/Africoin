#!/bin/bash
# Clean build artifacts and directories

set -e

echo "Cleaning build artifacts..."

if [ -d "africoin-core" ]; then
    rm -rf africoin-core
    echo "Removed africoin-core directory"
fi

echo "Cleanup complete!"
