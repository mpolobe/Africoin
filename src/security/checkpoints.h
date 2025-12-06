// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2012-2013 The PeerCoin developers
// Copyright (c) 2025 Africoin Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef AFRICOIN_SECURITY_CHECKPOINTS_H
#define AFRICOIN_SECURITY_CHECKPOINTS_H

#include <stdint.h>
#include <map>
#include <string>

// Forward declarations for Africoin types
// These should be replaced with actual includes once integrated
class uint256;
class CBlockIndex;

/**
 * @file checkpoints.h
 * @brief PeerCoin's checkpoint system for long-range attack prevention
 * 
 * Checkpoints are hardcoded block hashes at specific heights that:
 * 1. Prevent long-range attacks (reorganization attempts from early blocks)
 * 2. Speed up initial block verification during sync
 * 3. Provide a known-good chain state reference
 * 
 * PeerCoin Reference: https://github.com/peercoin/peercoin
 * 
 * TODO: Integrate actual PeerCoin checkpoint implementation from:
 *       https://github.com/peercoin/peercoin/blob/master/src/checkpoints.h
 * 
 * Security Notes:
 * - Checkpoints should be updated with each major release
 * - Only include blocks that are deeply confirmed (1000+ confirmations)
 * - Verify checkpoint hashes against multiple node sources
 */

namespace PeerCoin {
namespace Checkpoints {

/**
 * @brief Type definition for checkpoint map
 * 
 * Maps block height to expected block hash.
 * This is the hardened checkpoint data structure.
 */
typedef std::map<int, uint256> MapCheckpoints;

/**
 * @brief Check if a block passes hardened checkpoint validation
 * 
 * Verifies that if a checkpoint exists at the given height,
 * the block hash matches the expected checkpoint hash.
 * 
 * @param nHeight Block height to check
 * @param hash Block hash to validate
 * @return true if no checkpoint exists at height, or hash matches checkpoint
 * 
 * Security: This prevents attackers from forking the chain
 * before a checkpoint height with different blocks.
 * 
 * TODO: Implement using PeerCoin's CheckHardened() from checkpoints.cpp
 */
bool CheckHardened(int nHeight, const uint256& hash);

/**
 * @brief Get conservative estimate of total blocks
 * 
 * Returns the highest checkpointed block height.
 * Useful for progress estimation during initial sync.
 * 
 * @return Highest checkpoint block height
 * 
 * TODO: Implement using PeerCoin's GetTotalBlocksEstimate() from checkpoints.cpp
 */
int GetTotalBlocksEstimate();

/**
 * @brief Get the last checkpoint block index
 * 
 * Finds and returns the CBlockIndex for the most recent
 * checkpointed block in the current chain.
 * 
 * @param mapBlockIndex Map of block hashes to block indices
 * @return Pointer to the last checkpoint's CBlockIndex, or nullptr
 * 
 * TODO: Implement using PeerCoin's GetLastCheckpoint() from checkpoints.cpp
 */
CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex);

/**
 * @brief Get the height of the last checkpoint
 * 
 * Returns the block height of the most recent checkpoint.
 * 
 * @return Last checkpoint height, or 0 if no checkpoints defined
 * 
 * TODO: Implement using PeerCoin's checkpoint data
 */
int GetLastCheckpointHeight();

/**
 * @brief Get the expected block hash at a checkpoint height
 * 
 * If a checkpoint exists at the given height, returns the
 * expected hash. Otherwise returns a null hash.
 * 
 * @param nHeight Block height to query
 * @return Expected block hash, or null uint256 if no checkpoint
 * 
 * TODO: Implement checkpoint lookup
 */
uint256 GetCheckpointHash(int nHeight);

/**
 * @brief Verify chain integrity against checkpoints
 * 
 * Walks the chain backwards from the given index and
 * verifies all checkpoint hashes match.
 * 
 * @param pindex Block index to start verification from
 * @return true if all checkpoints are valid
 * 
 * TODO: Implement chain verification against checkpoints
 */
bool VerifyCheckpointsInChain(const CBlockIndex* pindex);

/**
 * @brief Check if automatic checkpoint updates are allowed
 * 
 * Some implementations allow the network to propose new
 * checkpoints via special transactions. This function
 * checks if that feature is enabled.
 * 
 * @return true if automatic checkpoints are enabled
 * 
 * Note: This is an advanced feature that requires careful
 * implementation to prevent checkpoint injection attacks.
 */
bool AutoCheckpointsEnabled();

/**
 * @struct CheckpointData
 * @brief Container for checkpoint-related constants
 * 
 * Holds the checkpoint map and metadata for a specific network.
 */
struct CheckpointData {
    MapCheckpoints mapCheckpoints;
    int64_t nTimeLastCheckpoint;
    int64_t nTransactionsLastCheckpoint;
    double fTransactionsPerDay;
};

/**
 * @brief Get checkpoint data for the active chain
 * 
 * Returns the appropriate checkpoint data structure based on
 * whether mainnet, testnet, or regtest is active.
 * 
 * @return Reference to the active chain's checkpoint data
 * 
 * TODO: Implement per-network checkpoint data
 */
const CheckpointData& GetCheckpointData();

} // namespace Checkpoints
} // namespace PeerCoin

#endif // AFRICOIN_SECURITY_CHECKPOINTS_H
