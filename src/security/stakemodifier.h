// Copyright (c) 2012-2013 The PeerCoin developers
// Copyright (c) 2025 Africoin Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef AFRICOIN_SECURITY_STAKEMODIFIER_H
#define AFRICOIN_SECURITY_STAKEMODIFIER_H

#include <stdint.h>
#include <vector>

// Forward declarations for Africoin types
// These should be replaced with actual includes once integrated
class uint256;
class CBlockIndex;
class CBlock;

/**
 * @file stakemodifier.h
 * @brief PeerCoin's stake modifier v0.3 protocol
 * 
 * The stake modifier is a critical component of proof-of-stake security.
 * It provides unpredictability to the stake selection process, preventing
 * attackers from pre-computing future stake winners.
 * 
 * PeerCoin's v0.3 stake modifier protocol is more secure than earlier
 * implementations (including BlackCoin's) because it:
 * 
 * 1. Uses a combination of block data and previous modifiers
 * 2. Updates the modifier at defined intervals
 * 3. Incorporates entropy from multiple sources
 * 4. Prevents stake grinding attacks
 * 
 * PeerCoin Reference: https://github.com/peercoin/peercoin
 * 
 * TODO: Integrate actual PeerCoin stake modifier implementation from:
 *       https://github.com/peercoin/peercoin/blob/master/src/kernel.cpp
 *       (stake modifier logic is in kernel.cpp in PeerCoin)
 */

namespace PeerCoin {

/**
 * @class StakeModifier
 * @brief PeerCoin's stake modifier v0.3 implementation
 * 
 * The StakeModifier class handles the computation and verification
 * of stake modifiers used in the kernel protocol.
 * 
 * Security Properties:
 * - Modifier is unpredictable before block creation
 * - Modifier cannot be manipulated without controlling stake
 * - Provides entropy to kernel hash calculation
 * - Checksum allows verification of modifier chain
 */
class StakeModifier {
public:
    /**
     * @brief Compute the next stake modifier
     * 
     * Calculates the stake modifier for a new block based on
     * the previous block's data and modifier.
     * 
     * The v0.3 protocol computes the modifier as:
     * - Hash of previous modifier + selected block data
     * - Selection based on stake age and modifier interval
     * 
     * @param pindexPrev Previous block index
     * @param nStakeModifier Output: computed stake modifier
     * @param fGeneratedStakeModifier Output: true if new modifier was generated
     * @return true if computation succeeded
     * 
     * TODO: Implement using PeerCoin's ComputeNextStakeModifier() from kernel.cpp
     */
    static bool ComputeNextStakeModifier(const CBlockIndex* pindexPrev, 
                                         uint64_t& nStakeModifier, 
                                         bool& fGeneratedStakeModifier);
    
    /**
     * @brief Get the stake modifier checksum
     * 
     * Computes a checksum of the stake modifier chain up to the
     * given block. Used to verify modifier integrity.
     * 
     * @param pindex Block index to compute checksum for
     * @return Checksum value
     * 
     * TODO: Implement using PeerCoin's GetStakeModifierChecksum() from kernel.cpp
     */
    static unsigned int GetStakeModifierChecksum(const CBlockIndex* pindex);
    
    /**
     * @brief Verify stake modifier checksum against checkpoints
     * 
     * Checks that the stake modifier checksum at a given height
     * matches the expected checkpoint value.
     * 
     * @param nHeight Block height to check
     * @param nStakeModifierChecksum Checksum to verify
     * @return true if checksum is valid or no checkpoint exists
     * 
     * TODO: Implement using PeerCoin's CheckStakeModifierCheckpoints() from kernel.cpp
     */
    static bool CheckStakeModifierCheckpoints(int nHeight, unsigned int nStakeModifierChecksum);

    /**
     * @brief Select blocks for stake modifier computation
     * 
     * Selects a subset of blocks to include in the stake modifier
     * calculation based on the selection algorithm.
     * 
     * PeerCoin v0.3 uses a deterministic selection based on:
     * - Block hash
     * - Previous modifier
     * - Time-based intervals
     * 
     * @param pindexPrev Previous block index
     * @param nStakeModifierPrev Previous stake modifier
     * @param pindexSelected Output: selected block index
     * @return true if selection succeeded
     * 
     * TODO: Implement using PeerCoin's SelectBlockFromCandidates()
     */
    static bool SelectBlockFromCandidates(const CBlockIndex* pindexPrev,
                                          uint64_t nStakeModifierPrev,
                                          const CBlockIndex** pindexSelected);

    /**
     * @brief Check if a block is in the stake modifier selection
     * 
     * Determines if a block should be included in the stake
     * modifier calculation based on selection criteria.
     * 
     * @param pindex Block to check
     * @param nStakeModifierPrev Previous stake modifier
     * @return true if block is selected
     * 
     * TODO: Implement selection criteria from PeerCoin
     */
    static bool IsBlockSelected(const CBlockIndex* pindex, uint64_t nStakeModifierPrev);

    /**
     * @brief Get stake modifier selection interval
     * 
     * Returns the time interval (in seconds) between stake
     * modifier updates. The modifier is recomputed every interval.
     * 
     * @return Modifier selection interval in seconds
     */
    static int64_t GetStakeModifierSelectionInterval();

    /**
     * @brief Get stake modifier selection interval section
     * 
     * The selection interval is divided into sections for
     * deterministic block selection. Returns the section
     * index for a given timestamp.
     * 
     * @param nTime Block timestamp
     * @return Section index (0-63)
     */
    static int GetStakeModifierSelectionIntervalSection(int64_t nTime);

    /**
     * @brief Check if protocol v0.3 is active
     * 
     * Determines if the v0.3 stake modifier protocol should be
     * used based on block timestamp. Earlier blocks use v0.2.
     * 
     * @param nTime Block timestamp to check
     * @return true if v0.3 protocol is active
     */
    static bool IsProtocolV03(int64_t nTime);

    /**
     * @brief Check if protocol v0.4 is active (if implemented)
     * 
     * Placeholder for future protocol upgrades.
     * 
     * @param nTime Block timestamp to check
     * @return true if v0.4 protocol is active
     */
    static bool IsProtocolV04(int64_t nTime);
};

/**
 * @brief Stake modifier selection interval
 * 
 * How often (in seconds) the stake modifier is updated.
 * PeerCoin uses 6 hours, but this can be adjusted for Africoin.
 */
static const int64_t nModifierInterval = 6 * 60 * 60; // 6 hours

/**
 * @brief Stake modifier v0.3 switch timestamp
 * 
 * Timestamp after which the v0.3 protocol is active.
 * Set to 0 to always use v0.3 for new chains.
 * 
 * TODO: Set appropriate value for Africoin mainnet
 */
static const int64_t nStakeModifierV03SwitchTime = 0; // Always use v0.3

/**
 * @brief Number of sections in stake modifier selection interval
 * 
 * The selection interval is divided into this many sections
 * for block selection purposes.
 */
static const int nStakeModifierSections = 64;

/**
 * @brief Stake modifier checkpoints
 * 
 * Map of block height to expected stake modifier checksum.
 * Used to verify the integrity of the stake modifier chain.
 * 
 * TODO: Add checkpoints after Africoin mainnet launch
 */
typedef std::pair<int, unsigned int> StakeModifierCheckpoint;

} // namespace PeerCoin

#endif // AFRICOIN_SECURITY_STAKEMODIFIER_H
