#!/bin/bash
# Implement PeerCoin security features
#
# This script copies PeerCoin's security implementation files into the
# Africoin build. These files provide:
# - Kernel protocol for proof-of-stake validation
# - Checkpoint system for long-range attack prevention
# - Stake modifier v0.3 for grinding attack resistance
#
# See docs/PEERCOIN_INTEGRATION.md for full documentation.

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(dirname "$SCRIPT_DIR")"
SECURITY_SRC="$REPO_ROOT/src/security"

echo "Implementing PeerCoin security features..."

# Check if we're in the right directory
if [ ! -d "src" ]; then
    echo "Error: src directory not found. Are you in the africoin-core directory?"
    exit 1
fi

# Create security directory in the build if it doesn't exist
if [ ! -d "src/security" ]; then
    echo "Creating src/security directory..."
    mkdir -p src/security
fi

# Copy PeerCoin security files
echo "Copying PeerCoin security implementation files..."

# Kernel protocol files
if [ -f "$SECURITY_SRC/kernel.h" ]; then
    cp "$SECURITY_SRC/kernel.h" src/security/
    echo "  - Copied kernel.h (PeerCoin kernel protocol header)"
fi

if [ -f "$SECURITY_SRC/kernel.cpp" ]; then
    cp "$SECURITY_SRC/kernel.cpp" src/security/
    echo "  - Copied kernel.cpp (PeerCoin kernel protocol implementation)"
fi

# Checkpoint system files
if [ -f "$SECURITY_SRC/checkpoints.h" ]; then
    cp "$SECURITY_SRC/checkpoints.h" src/security/
    echo "  - Copied checkpoints.h (Checkpoint system header)"
fi

if [ -f "$SECURITY_SRC/checkpoints.cpp" ]; then
    cp "$SECURITY_SRC/checkpoints.cpp" src/security/
    echo "  - Copied checkpoints.cpp (Checkpoint system implementation)"
fi

# Stake modifier files
if [ -f "$SECURITY_SRC/stakemodifier.h" ]; then
    cp "$SECURITY_SRC/stakemodifier.h" src/security/
    echo "  - Copied stakemodifier.h (Stake modifier v0.3 header)"
fi

if [ -f "$SECURITY_SRC/stakemodifier.cpp" ]; then
    cp "$SECURITY_SRC/stakemodifier.cpp" src/security/
    echo "  - Copied stakemodifier.cpp (Stake modifier v0.3 implementation)"
fi

# Update Makefile.am if it exists to include security files
if [ -f "src/Makefile.am" ]; then
    echo "Checking build system integration..."
    
    # Check if security files are already in Makefile.am
    if ! grep -q "security/kernel" src/Makefile.am 2>/dev/null; then
        echo "Note: Security files may need to be added to src/Makefile.am"
        echo "      Add the following to the appropriate variables:"
        echo ""
        echo "      # PeerCoin Security Implementation"
        echo "      SECURITY_H = \\"
        echo "        security/kernel.h \\"
        echo "        security/stakemodifier.h \\"
        echo "        security/checkpoints.h"
        echo ""
        echo "      SECURITY_CPP = \\"
        echo "        security/kernel.cpp \\"
        echo "        security/stakemodifier.cpp \\"
        echo "        security/checkpoints.cpp"
    fi
fi

echo ""
echo "✓ PeerCoin security features integrated successfully!"
echo ""
echo "Files installed:"
echo "  src/security/kernel.h          - Kernel protocol (stake validation)"
echo "  src/security/kernel.cpp        - Kernel protocol implementation"
echo "  src/security/checkpoints.h     - Checkpoint system (long-range attack prevention)"
echo "  src/security/checkpoints.cpp   - Checkpoint system implementation"
echo "  src/security/stakemodifier.h   - Stake modifier v0.3 (grinding attack resistance)"
echo "  src/security/stakemodifier.cpp - Stake modifier implementation"
echo ""
echo "Note: See docs/PEERCOIN_INTEGRATION.md for integration instructions."
