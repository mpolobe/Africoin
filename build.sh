#!/bin/bash
# Main build script for Africoin Core

set -e  # Exit on error

# Configuration
BLACKCOIN_REPO="https://github.com/CoinBlack/blackcoin.git"
PROJECT_DIR="africoin-core"
BUILD_JOBS=4

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Functions
print_step() {
    echo -e "${GREEN}===> $1${NC}"
}

print_warning() {
    echo -e "${YELLOW}WARNING: $1${NC}"
}

print_error() {
    echo -e "${RED}ERROR: $1${NC}"
}

# Step 1: Clone BlackCoin repository
clone_blackcoin() {
    print_step "Cloning BlackCoin repository..."
    if [ -d "$PROJECT_DIR" ]; then
        print_warning "Directory $PROJECT_DIR already exists. Removing..."
        rm -rf "$PROJECT_DIR"
    fi
    git clone "$BLACKCOIN_REPO" "$PROJECT_DIR"
    cd "$PROJECT_DIR"
    rm -rf .git
    git init
    print_step "Repository cloned and reinitialized"
}

# Step 2: Apply Africoin branding modifications
apply_branding() {
    print_step "Applying Africoin branding modifications..."
    ./scripts/apply_branding.sh
}

# Step 3: Apply chain parameter modifications
apply_chain_params() {
    print_step "Applying chain parameter modifications (1B supply, 2.5min blocks)..."
    ./scripts/apply_chain_params.sh
}

# Step 4: Apply PeerCoin security features
apply_security() {
    print_step "Implementing PeerCoin security features..."
    ./scripts/apply_security.sh
}

# Step 5: Apply railway staking optimizations
apply_staking() {
    print_step "Adding railway staking optimizations..."
    ./scripts/apply_staking.sh
}

# Step 6: Build the core daemon
build_daemon() {
    print_step "Building Africoin Core daemon..."
    
    if [ ! -f "autogen.sh" ]; then
        print_error "autogen.sh not found!"
        exit 1
    fi
    
    ./autogen.sh
    ./configure --with-incompatible-bdb --enable-cxx --with-gui=no
    make -j${BUILD_JOBS}
    
    print_step "Build completed successfully!"
}

# Step 7: Verify build
verify_build() {
    print_step "Verifying build..."
    
    if [ ! -f "./src/africoin-cli" ] || [ ! -f "./src/africoind" ]; then
        print_error "Build verification failed! Binaries not found."
        exit 1
    fi
    
    echo ""
    echo "Africoin CLI version:"
    ./src/africoin-cli --version
    
    echo ""
    echo "Africoin daemon version:"
    ./src/africoind --version
    
    print_step "Build verification successful!"
}

# Main execution
main() {
    echo "========================================"
    echo "  Africoin Core Build Script"
    echo "========================================"
    echo ""
    
    clone_blackcoin
    apply_branding
    apply_chain_params
    apply_security
    apply_staking
    build_daemon
    verify_build
    
    echo ""
    print_step "All steps completed successfully!"
    echo "Binaries location: $PROJECT_DIR/src/"
}

# Run main function
main
