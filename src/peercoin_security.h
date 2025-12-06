#ifndef PEERCOIN_SECURITY_IMPORTS_H
#define PEERCOIN_SECURITY_IMPORTS_H

#include "chain.h"
#include "consensus/params.h"

// PeerCoin's robust security features we're importing
namespace PeerCoinSecurity {

    // 1. PeerCoin's proven kernel protocol
    bool CheckKernelProtocol(const CBlockIndex* pindexPrev, 
                            unsigned int nBits, 
                            uint32_t nTime, 
                            const COutPoint& prevout);

    // 2. PeerCoin's stake modifier implementation (more secure than BlackCoin's)
    uint256 ComputeStakeModifier(const CBlockIndex* pindexPrev, 
                                 const uint256& kernel);

    // 3. PeerCoin's coin age weight calculation
    int64_t GetCoinAgeWeight(int64_t nIntervalBeginning, 
                            int64_t nIntervalEnd, 
                            const Consensus::Params& params);

    // 4. PeerCoin's difficulty adjustment algorithm
    unsigned int GetNextTargetRequired(const CBlockIndex* pindexLast, 
                                      bool fProofOfStake, 
                                      const Consensus::Params& params);

    // 5. PeerCoin's comprehensive stake validation
    bool CheckStakeProtocol(const CBlockHeader& block, 
                           int nHeight, 
                           const Consensus::Params& params);

} // namespace PeerCoinSecurity

#endif // PEERCOIN_SECURITY_IMPORTS_H
