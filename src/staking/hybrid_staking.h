// Copyright (c) 2012-2013 The PeerCoin developers
// Copyright (c) 2025 Africoin Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef AFRICOIN_STAKING_HYBRID_STAKING_H
#define AFRICOIN_STAKING_HYBRID_STAKING_H

#include <stdint.h>

// Forward declarations for Africoin types
// These should be replaced with actual includes once integrated
class uint256;
class CTransaction;
class CBlockIndex;
class CBlock;
class COutPoint;

/**
 * @file hybrid_staking.h
 * @brief Hybrid PoW/PoS staking mechanism for Africoin
 * 
 * This file implements a hybrid proof-of-work and proof-of-stake consensus
 * mechanism that combines the security benefits of both systems:
 * 
 * 1. PoW provides initial distribution security and prevents nothing-at-stake
 * 2. PoS provides energy efficiency and stakeholder governance
 * 3. The hybrid approach balances decentralization with security
 * 
 * Integration with PeerCoin security modules:
 * - kernel.h: Provides core PoS kernel validation
 * - checkpoints.h: Prevents long-range attacks
 * - stakemodifier.h: Adds unpredictability to stake selection
 * 
 * PeerCoin Reference: https://github.com/peercoin/peercoin
 */

namespace Africoin {

/**
 * @brief Block type enumeration for hybrid consensus
 * 
 * Defines the type of block in the hybrid PoW/PoS system.
 */
enum BlockType {
    BLOCK_TYPE_POW = 0,    ///< Proof of Work block
    BLOCK_TYPE_POS = 1,    ///< Proof of Stake block
    BLOCK_TYPE_HYBRID = 2  ///< Hybrid block (requires both PoW and PoS validation)
};

/**
 * @class HybridStaking
 * @brief Hybrid PoW/PoS staking mechanism for Africoin
 * 
 * The HybridStaking class combines Proof of Work and Proof of Stake
 * validation to provide enhanced security. It integrates with PeerCoin's
 * proven security modules (kernel, checkpoints, stakemodifier).
 * 
 * Key Security Features:
 * - Dual validation ensures blocks are valid under both consensus rules
 * - Stake modifier prevents stake grinding attacks
 * - Checkpoint system prevents long-range attacks
 * - Reward distribution incentivizes both miners and stakers
 */
class HybridStaking {
public:
    /**
     * @brief Validate a block using hybrid consensus rules
     * 
     * Validates a block by checking both PoW and PoS requirements
     * based on the block type and chain state.
     * 
     * @param block The block to validate
     * @param pindexPrev Previous block index
     * @return true if the block passes hybrid validation
     */
    static bool ValidateHybridBlock(const CBlock& block, const CBlockIndex* pindexPrev);

    /**
     * @brief Determine the block type for a given block
     * 
     * Analyzes the block structure to determine if it's a PoW block,
     * PoS block, or requires hybrid validation.
     * 
     * @param block The block to analyze
     * @return BlockType enumeration value
     */
    static BlockType GetBlockType(const CBlock& block);

    /**
     * @brief Check if PoW validation is required at the given height
     * 
     * Determines based on chain parameters whether PoW validation
     * is required. During early chain phases, PoW may be mandatory.
     * 
     * @param nHeight Block height to check
     * @return true if PoW validation is required
     */
    static bool IsPoWRequired(int nHeight);

    /**
     * @brief Check if PoS validation is required at the given height
     * 
     * Determines based on chain parameters whether PoS validation
     * is required. After initial distribution, PoS becomes primary.
     * 
     * @param nHeight Block height to check
     * @return true if PoS validation is required
     */
    static bool IsPoSRequired(int nHeight);

    /**
     * @brief Validate proof-of-stake using PeerCoin kernel
     * 
     * Performs PoS validation using PeerCoin's kernel protocol
     * which provides secure stake verification.
     * 
     * @param tx The coinstake transaction
     * @param nBits Difficulty bits
     * @param hashProofOfStake Output: computed proof-of-stake hash
     * @return true if PoS is valid
     */
    static bool ValidateProofOfStake(const CTransaction& tx, unsigned int nBits, 
                                     uint256& hashProofOfStake);

    /**
     * @brief Calculate hybrid block reward
     * 
     * Computes the block reward based on block type and chain state.
     * Hybrid blocks may receive enhanced rewards to incentivize
     * dual validation.
     * 
     * @param nHeight Block height
     * @param blockType Type of block (PoW/PoS/Hybrid)
     * @return Block reward in satoshis
     */
    static int64_t CalculateBlockReward(int nHeight, BlockType blockType);

    /**
     * @brief Get the hybrid stake modifier
     * 
     * Computes a combined stake modifier that incorporates both
     * PoW and PoS entropy for enhanced security.
     * 
     * @param pindexPrev Previous block index
     * @param nStakeModifier Output: computed stake modifier
     * @return true if modifier was computed successfully
     */
    static bool GetHybridStakeModifier(const CBlockIndex* pindexPrev, uint64_t& nStakeModifier);

    /**
     * @brief Select the next block producer
     * 
     * Uses the hybrid selection algorithm to determine whether
     * the next block should be PoW or PoS based on chain state.
     * 
     * @param pindexPrev Previous block index
     * @return Expected block type for next block
     */
    static BlockType SelectNextBlockType(const CBlockIndex* pindexPrev);

    /**
     * @brief Verify hybrid checkpoint compliance
     * 
     * Checks that the block complies with checkpoint requirements
     * for both PoW and PoS chains.
     * 
     * @param nHeight Block height
     * @param hash Block hash
     * @return true if checkpoint validation passes
     */
    static bool VerifyHybridCheckpoint(int nHeight, const uint256& hash);

    /**
     * @brief Get the hybrid difficulty target
     * 
     * Computes the difficulty target for hybrid blocks which
     * may differ from pure PoW or PoS targets.
     * 
     * @param pindexPrev Previous block index
     * @param blockType Type of block being created
     * @return Difficulty bits for the target
     */
    static unsigned int GetHybridDifficulty(const CBlockIndex* pindexPrev, BlockType blockType);

    /**
     * @brief Initialize hybrid staking subsystem
     * 
     * Performs initialization of the hybrid staking subsystem,
     * loading configuration and verifying security modules.
     * 
     * @return true if initialization succeeded
     */
    static bool Initialize();
};

// Hybrid staking constants

/**
 * @brief Height at which PoS becomes active
 * 
 * PoS validation begins at this height. Before this,
 * only PoW blocks are accepted.
 */
static const int nPoSStartHeight = 1000;

/**
 * @brief Height at which pure PoW blocks are no longer accepted
 * 
 * After this height, blocks must include PoS validation
 * (either pure PoS or hybrid).
 */
static const int nPurePoWEndHeight = 10000;

/**
 * @brief Ratio of PoS blocks to total blocks (target)
 * 
 * The chain aims to have this percentage of blocks
 * validated via PoS after the transition period.
 */
static const double nTargetPoSRatio = 0.9; // 90% PoS blocks

/**
 * @brief Hybrid block reward multiplier
 * 
 * Blocks that pass both PoW and PoS validation receive
 * this multiplier on their base reward.
 */
static const double nHybridRewardMultiplier = 1.1; // 10% bonus

/**
 * @brief Minimum confirmations for stake maturity
 * 
 * Stake inputs must have at least this many confirmations
 * before they can be used for staking.
 */
static const int nStakeMinConfirmations = 500;

} // namespace Africoin

#endif // AFRICOIN_STAKING_HYBRID_STAKING_H
