# PeerCoin Security Implementation

Africoin integrates battle-tested security features from PeerCoin's proof-of-stake protocol to enhance network security and prevent common PoS attacks.

## Security Features Implemented

### 1. Kernel Protocol (`CheckKernelProtocol`)
PeerCoin's proven kernel protocol prevents precomputation attacks by using:
- Stake modifier for randomness
- Transaction output point
- Block timestamps
- Proper difficulty targets

### 2. Stake Modifier (`ComputeStakeModifier`)
**Why PeerCoin's is better than BlackCoin's:**
- Uses deterministic selection from blockchain history
- Cannot be manipulated by attackers
- Provides true pseudo-randomness
- Prevents grinding attacks

### 3. Coin Age Weight (`GetCoinAgeWeight`)
Calculates staking weight based on coin age:
- **Minimum age**: 24 hours (coins must mature)
- **Maximum age**: 30 days (prevents hoarding)
- **Block time**: 2.5 minutes (150 seconds)

This encourages active participation while preventing long-term hoarding strategies.

### 4. Difficulty Adjustment (`GetNextTargetRequired`)
PeerCoin's per-block difficulty adjustment:
- Adjusts every block based on actual spacing
- Limits extreme adjustments (max 10x)
- Separate limits for PoW and PoS
- Responsive to network changes

### 5. Comprehensive Stake Validation (`CheckStakeProtocol`)
Full protocol validation including:
- Timestamp verification with clock drift protection
- Coinstake transaction structure validation
- Kernel hash target verification
- Stake modifier validation
- Coin age requirement checking

## Attack Prevention

These features protect against:

- **Precomputation attacks**: Stake modifier randomness
- **Grinding attacks**: Deterministic stake modifier
- **Nothing-at-stake**: Coin age requirements
- **Long-range attacks**: Checkpoint system integration
- **Timejacking**: Clock drift limits

## Integration Points

The PeerCoin security layer integrates with:
- `validation.cpp`: Block validation
- `miner.cpp`: Stake generation
- `chainparams.cpp`: Consensus parameters
- `pos.cpp`: Proof-of-stake logic

## Configuration Parameters

Key parameters in `consensus/params.h`:
```cpp
int64_t nPosTargetSpacing = 150;  // 2.5 minutes
int64_t nMaxClockDrift = 2 * 60 * 60;  // 2 hours
uint256 posLimit;  // PoS difficulty limit
```

## Testing

Ensure thorough testing of:
1. Kernel hash calculations
2. Stake modifier generation
3. Coin age weight computation
4. Difficulty retargeting
5. Full stake validation

## References

- [PeerCoin Whitepaper](https://peercoin.net/whitepaper)
- [PeerCoin GitHub](https://github.com/peercoin/peercoin)
- Stake Modifier Protocol v0.3

## Future Enhancements

Planned improvements:
- [ ] Stake modifier v0.4 protocol
- [ ] Enhanced checkpoint system
- [ ] Additional grinding attack prevention
- [ ] Performance optimizations
