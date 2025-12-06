// Copyright (c) 2012-2013 The PeerCoin developers
// Copyright (c) 2025 Africoin Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef AFRICOIN_SECURITY_KERNEL_H
#define AFRICOIN_SECURITY_KERNEL_H

#include <stdint.h>

// Forward declarations for Africoin types
// These should be replaced with actual includes once integrated
class uint256;
class CTransaction;
class CBlockIndex;
class CBlock;
class COutPoint;

/**
 * @file kernel.h
 * @brief PeerCoin's kernel protocol for proof-of-stake validation
 * 
 * This file implements PeerCoin's proven kernel protocol which provides
 * secure proof-of-stake validation. The kernel protocol is responsible for:
 * 
 * 1. Validating stake kernels to ensure proper staking
 * 2. Computing and verifying proof-of-stake hashes
 * 3. Managing stake modifiers for security
 * 
 * PeerCoin Reference: https://github.com/peercoin/peercoin
 * 
 * TODO: Integrate actual PeerCoin kernel implementation from:
 *       https://github.com/peercoin/peercoin/blob/master/src/kernel.h
 */

namespace PeerCoin {

/**
 * @class Kernel
 * @brief PeerCoin's kernel protocol for proof-of-stake validation
 * 
 * The Kernel class implements the core proof-of-stake validation logic
 * from PeerCoin. This protocol is more secure than simpler PoS implementations
 * as it uses a time-weighted stake modifier system.
 * 
 * Key Security Features:
 * - Stake modifier prevents stake grinding attacks
 * - Time-weighted selection reduces nothing-at-stake attacks
 * - Kernel hash verification ensures proper stake proofs
 */
class Kernel {
public:
    /**
     * @brief Check proof-of-stake for a coinstake transaction
     * 
     * Verifies that a transaction properly proves stake ownership
     * by checking the kernel hash against the required target.
     * 
     * @param tx The coinstake transaction to verify
     * @param nBits The difficulty bits for stake target
     * @param hashProofOfStake Output: the computed proof-of-stake hash
     * @param targetProofOfStake Output: the target hash for comparison
     * @return true if the proof-of-stake is valid
     * 
     * TODO: Implement using PeerCoin's CheckProofOfStake() from kernel.cpp
     */
    static bool CheckProofOfStake(const CTransaction& tx, unsigned int nBits, 
                                  uint256& hashProofOfStake, uint256& targetProofOfStake);
    
    /**
     * @brief Get the stake modifier for a given block
     * 
     * Retrieves the stake modifier that should be used for kernel
     * hash computation. The stake modifier provides security against
     * stake grinding attacks.
     * 
     * @param hashBlockFrom Hash of the block containing the stake
     * @param nStakeModifier Output: the stake modifier value
     * @return true if stake modifier was successfully retrieved
     * 
     * TODO: Implement using PeerCoin's GetKernelStakeModifier() from kernel.cpp
     */
    static bool GetKernelStakeModifier(const uint256& hashBlockFrom, uint64_t& nStakeModifier);
    
    /**
     * @brief Check the stake kernel hash
     * 
     * Performs the core kernel hash verification to ensure
     * the stake meets the required difficulty target.
     * 
     * @param nBits Target difficulty bits
     * @param blockFrom Block containing the stake input
     * @param nTxPrevOffset Offset of the previous transaction
     * @param txPrev Previous transaction being staked
     * @param prevout Output point of the stake
     * @param nTimeTx Timestamp of the transaction
     * @param hashProofOfStake Output: computed proof-of-stake hash
     * @param fPrintProofOfStake Whether to print debug information
     * @return true if the kernel hash meets the target
     * 
     * TODO: Implement using PeerCoin's CheckStakeKernelHash() from kernel.cpp
     */
    static bool CheckStakeKernelHash(unsigned int nBits, const CBlock& blockFrom, 
                                     unsigned int nTxPrevOffset, const CTransaction& txPrev,
                                     const COutPoint& prevout, unsigned int nTimeTx,
                                     uint256& hashProofOfStake, bool fPrintProofOfStake = false);

    /**
     * @brief Compute the time weight for stake age
     * 
     * Calculates the weight multiplier based on coin age.
     * Older stakes have higher weight up to a maximum.
     * 
     * @param nIntervalBeginning Start of the staking interval
     * @param nIntervalEnd End of the staking interval
     * @return Time weight factor
     * 
     * TODO: Implement using PeerCoin's GetWeight() from kernel.cpp
     */
    static int64_t GetWeight(int64_t nIntervalBeginning, int64_t nIntervalEnd);

    /**
     * @brief Get the coin age for a transaction
     * 
     * Computes the coin age (stake weight) for a transaction
     * which is used in stake target calculation.
     * 
     * @param tx The transaction to compute age for
     * @param nCoinAge Output: the computed coin age
     * @return true if coin age was computed successfully
     * 
     * TODO: Implement using PeerCoin's GetCoinAge() from kernel.cpp
     */
    static bool GetCoinAge(const CTransaction& tx, uint64_t& nCoinAge);
};

// Constants for kernel protocol
// These values should be adjusted based on Africoin's chain parameters

/**
 * @brief Minimum coin age for staking (in seconds)
 * 
 * Coins must be held for at least this long before they can stake.
 * This prevents rapid stake cycling attacks.
 */
static const int64_t nStakeMinAge = 60 * 60 * 24 * 30; // 30 days

/**
 * @brief Maximum coin age for staking (in seconds)
 * 
 * After this age, coins receive no additional weight benefit.
 * This encourages regular staking participation.
 */
static const int64_t nStakeMaxAge = 60 * 60 * 24 * 90; // 90 days

/**
 * @brief Target spacing between stake blocks (in seconds)
 * 
 * The desired average time between blocks.
 * Africoin uses 2.5 minute blocks.
 */
static const int64_t nStakeTargetSpacing = 2.5 * 60; // 2.5 minutes

} // namespace PeerCoin

#endif // AFRICOIN_SECURITY_KERNEL_H
