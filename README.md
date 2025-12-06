# Africoin

Africoin is a cryptocurrency core daemon built from the BlackCoin codebase with custom modifications.

## Build Scripts

This repository includes automated build scripts to set up and build the Africoin Core daemon.

### File Structure

```
/
├── build.sh              # Main build script
├── quick-build.sh        # Quick rebuild script for development
├── clean.sh              # Clean build artifacts
├── scripts/
│   ├── apply_branding.sh     # Apply Africoin branding
│   ├── apply_chain_params.sh # Configure chain parameters
│   ├── apply_security.sh     # Implement security features
│   └── apply_staking.sh      # Add staking optimizations
└── README.md
```

### Main Build Script (`build.sh`)

The main build script automates the entire build process:

1. Clone the BlackCoin repository
2. Apply Africoin branding modifications
3. Apply chain parameter modifications (1B supply, 2.5min blocks)
4. Implement PeerCoin security features
5. Add railway staking optimizations
6. Build the core daemon
7. Verify the build

**Usage:**
```bash
./build.sh
```

### Quick Rebuild Script (`quick-build.sh`)

For development purposes, use the quick rebuild script to skip cloning and modifications:

```bash
./quick-build.sh
```

### Clean Script (`clean.sh`)

To clean up build artifacts and the africoin-core directory:

```bash
./clean.sh
```

## Configuration

The build script uses the following configuration:

- **BlackCoin Repository:** https://github.com/CoinBlack/blackcoin.git
- **Project Directory:** africoin-core
- **Build Jobs:** 4

## Chain Parameters

- **Total Supply:** 1 billion coins
- **Block Time:** 2.5 minutes

## Requirements

- Git
- Build essentials (make, gcc, g++)
- Autotools (automake, autoconf, libtool)
- Berkeley DB (BDB)
- Boost libraries
- OpenSSL

## Notes

- The modification scripts contain placeholders that will be filled in with actual code modifications based on the BlackCoin codebase structure
- Scripts include error handling and clear output messages
- All scripts are idempotent where possible