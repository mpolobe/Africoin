# PeerCoin Security Integration Guide

This document describes the integration of PeerCoin's battle-tested security implementations into Africoin for enhanced proof-of-stake security.

## Overview

Africoin incorporates PeerCoin's security components to provide robust proof-of-stake validation. PeerCoin was the first successful proof-of-stake cryptocurrency and has proven security mechanisms that have withstood years of production use.

## Components

### 1. Kernel Protocol (`src/security/kernel.h`, `src/security/kernel.cpp`)

The kernel protocol is the heart of proof-of-stake validation. It handles:

- **Proof-of-stake verification**: Validates that stake transactions meet the required difficulty target
- **Stake modifier integration**: Uses stake modifiers to prevent grinding attacks
- **Coin age calculation**: Computes time-weighted stake values
- **Kernel hash computation**: Generates the proof-of-stake hash for validation

#### Key Functions

| Function | Description |
|----------|-------------|
| `CheckProofOfStake()` | Verifies a coinstake transaction's proof |
| `GetKernelStakeModifier()` | Retrieves the stake modifier for a block |
| `CheckStakeKernelHash()` | Validates the kernel hash against target |
| `GetWeight()` | Calculates time weight for stake age |
| `GetCoinAge()` | Computes coin age for a transaction |

### 2. Checkpoint System (`src/security/checkpoints.h`, `src/security/checkpoints.cpp`)

Checkpoints provide protection against long-range attacks by hardcoding known-good block hashes at specific heights.

#### Security Benefits

- **Long-range attack prevention**: Attackers cannot reorganize the chain before checkpoint heights
- **Fast initial sync**: Skip full validation for blocks before checkpoints
- **Known-good state**: Provides reference points for chain validation

#### Key Functions

| Function | Description |
|----------|-------------|
| `CheckHardened()` | Verifies block hash against checkpoint |
| `GetTotalBlocksEstimate()` | Returns highest checkpoint height |
| `GetLastCheckpoint()` | Finds most recent checkpoint in chain |
| `GetLastCheckpointHeight()` | Returns last checkpoint block height |

### 3. Stake Modifier (`src/security/stakemodifier.h`, `src/security/stakemodifier.cpp`)

The stake modifier prevents stake grinding attacks by adding unpredictability to the stake selection process.

#### PeerCoin v0.3 Protocol

Africoin uses PeerCoin's v0.3 stake modifier protocol, which provides:

- **Improved entropy**: Better randomness in modifier computation
- **Grinding resistance**: Cannot pre-compute future stake winners
- **Deterministic verification**: All nodes compute the same modifier
- **Checkpoint validation**: Modifier chain integrity verification

#### Key Functions

| Function | Description |
|----------|-------------|
| `ComputeNextStakeModifier()` | Calculates modifier for new block |
| `GetStakeModifierChecksum()` | Computes modifier chain checksum |
| `CheckStakeModifierCheckpoints()` | Verifies against checkpoints |
| `SelectBlockFromCandidates()` | Selects blocks for modifier |
| `IsProtocolV03()` | Checks if v0.3 protocol is active |

## Integration Status

### Current Status: Stub Implementation

The current files contain:
- ✅ Complete interface definitions
- ✅ Comprehensive documentation
- ✅ Placeholder implementations
- ⬜ TODO markers for actual code integration

### Next Steps

1. **Obtain PeerCoin Source**
   ```bash
   git clone https://github.com/peercoin/peercoin.git
   cd peercoin/src
   ```

2. **Review Key Files**
   - `kernel.cpp` - Kernel protocol implementation
   - `kernel.h` - Kernel protocol header
   - `checkpoints.cpp` - Checkpoint implementation

3. **Adapt Data Structures**
   - Map PeerCoin types to Africoin types
   - Adjust hash functions if needed
   - Configure consensus parameters

4. **Implement Functions**
   - Replace stub implementations with PeerCoin code
   - Test each function independently
   - Verify consensus compatibility

5. **Add Checkpoints**
   - After mainnet launch, add checkpoint data
   - Include genesis block checkpoint
   - Add checkpoints every ~50000 blocks

## Testing Requirements

### Unit Tests

Create tests for each security component:

```cpp
// Example test structure
TEST(KernelTest, CheckStakeKernelHash) {
    // Test kernel hash validation
}

TEST(CheckpointsTest, CheckHardened) {
    // Test checkpoint verification
}

TEST(StakeModifierTest, ComputeNextStakeModifier) {
    // Test modifier computation
}
```

### Integration Tests

1. **Full chain sync**: Verify chain syncs correctly with security checks
2. **Stake validation**: Test staking with security features enabled
3. **Checkpoint enforcement**: Verify invalid blocks are rejected
4. **Modifier chain**: Validate modifier checksum chain

### Regression Tests

1. Compare Africoin behavior with reference implementation
2. Verify no consensus-breaking changes
3. Test edge cases (genesis block, protocol switches)

## Security Considerations

### Licensing

- PeerCoin code is MIT licensed
- Maintain copyright attribution
- Include original license text

### Audit Requirements

Before mainnet launch:
1. Security audit of adapted code
2. Review of consensus parameter choices
3. Verification of stake modifier implementation
4. Testing on testnet with real-world scenarios

### Known Vulnerabilities

The PeerCoin security implementation addresses:
- **Stake grinding**: Prevented by stake modifier
- **Nothing-at-stake**: Mitigated by coin age requirements
- **Long-range attacks**: Prevented by checkpoints
- **Timestamp manipulation**: Checked by kernel protocol

## Configuration

### Consensus Parameters

| Parameter | Value | Description |
|-----------|-------|-------------|
| `nStakeMinAge` | 30 days | Minimum coin age for staking |
| `nStakeMaxAge` | 90 days | Maximum coin age benefit |
| `nStakeTargetSpacing` | 2.5 min | Target block time |
| `nModifierInterval` | 6 hours | Stake modifier update interval |

### Checkpoints (To Be Added)

```cpp
// Example checkpoint entries
{ 0, uint256("0x...genesis...") },      // Genesis
{ 50000, uint256("0x...") },            // First checkpoint
{ 100000, uint256("0x...") },           // Second checkpoint
```

## Build System Integration

The security files are included in the build via the following additions:

### Makefile Variables

```makefile
# PeerCoin Security Implementation
SECURITY_H = \
  src/security/kernel.h \
  src/security/stakemodifier.h \
  src/security/checkpoints.h

SECURITY_CPP = \
  src/security/kernel.cpp \
  src/security/stakemodifier.cpp \
  src/security/checkpoints.cpp
```

### Include Paths

Ensure the build system includes:
```
-I$(srcdir)/src/security
```

## References

- [PeerCoin GitHub Repository](https://github.com/peercoin/peercoin)
- [PeerCoin Whitepaper](https://peercoin.net/whitepapers/)
- [Proof-of-Stake Security Analysis](https://peercoin.net/docs/)
- [BlackCoin Original Implementation](https://github.com/CoinBlack/blackcoin)

## Changelog

### 2025-XX-XX - Initial Integration
- Created stub implementations with interfaces
- Added comprehensive documentation
- Prepared build system integration
- TODO: Integrate actual PeerCoin code

## Contributing

When modifying the security implementation:

1. Maintain compatibility with PeerCoin protocol
2. Document all changes from reference implementation
3. Include unit tests for new functionality
4. Submit for security review before merge

## Support

For questions about the security implementation:
- Open an issue on the Africoin repository
- Reference this document in your issue
- Include relevant code snippets and test cases
