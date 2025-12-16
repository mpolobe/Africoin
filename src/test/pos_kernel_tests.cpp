#include <cassert>
#include <iostream>
#include <string>
#include "../consensus/pos_kernel.h"

// --- Mock types and helpers (replace with project types as needed) ---
struct CValidationState {
    bool error = false;
    std::string reject_reason;
    int dos_score = 0;
    bool DoS(int level, bool ret, unsigned char, std::string reason) {
        error = true;
        dos_score = level;
        reject_reason = reason;
        return ret;
    }
};

struct uint256 {
    uint64_t value;
    uint256(uint64_t v=0) : value(v) {}
    bool operator<(const uint256& o) const { return value < o.value; }
    bool operator>(const uint256& o) const { return value > o.value; }
    uint256 operator*(uint64_t n) const { return uint256(value * n); }
    uint256 operator*(int n) const { return uint256(value * n); }
    uint256 operator*(const uint256& n) const { return uint256(value * n.value); }
    std::string ToString() const { return std::to_string(value); }
};

struct CBlockHeader {
    uint256 hashPrevBlock;
};

struct CTransaction {
    uint64_t nTime;
};

// --- Mock injection for RPoSKernelTests ---
static uint256 g_baseTarget(1000);
static int g_stationTier = 1;
static uint256 g_kernelHash(1);

// Override test helpers
uint256 Test_GetBaseTarget(const CBlockHeader&) { return g_baseTarget; }
int Test_GetStationTier(const CTransaction&) { return g_stationTier; }
uint256 Test_HashKernel(const CBlockHeader&, const CTransaction&) { return g_kernelHash; }

// Redirect the consensus code to use test mocks
#undef GetBaseTarget
#define GetBaseTarget Test_GetBaseTarget

#undef GetStationTier
#define GetStationTier Test_GetStationTier

// Simple wrapper to allow kernel hash injection
bool TestCheckKernelProofOfStake(const CBlockHeader& block, const CTransaction& tx, CValidationState& state)
{
    // Copy cutoff logic from pos_kernel.cpp, but substitute the hash.
    uint256 hashTarget = GetBaseTarget(block);
    int nTier = GetStationTier(tx);
    int nMultiplier = GetTierDifficultyMultiplier(nTier);

    uint256 nCombinedTarget = hashTarget * nMultiplier;
    uint256 hashProofOfStake = g_kernelHash; // inject value

    if (hashProofOfStake > nCombinedTarget) {
        state.DoS(100, false, REJECT_INVALID, "kernel-too-hard");
        return false;
    }
    return true;
}

void RPoSKernelTests() {
    CBlockHeader block;
    CTransaction tx;
    CValidationState state;

    // --- Tier 1 Success ---
    g_stationTier = 1;
    g_baseTarget = 1000;
    g_kernelHash = 900; // Less than baseTarget * 1 == 1000
    state = CValidationState();
    assert(TestCheckKernelProofOfStake(block, tx, state) == true);
    assert(!state.error);
    std::cout << "Tier 1 Success Test Passed\n";

    // --- Tier 3 Success: Fail Tier 1, pass Tier 3 ---
    g_stationTier = 1;
    g_kernelHash = 1500; // Above Tier 1 threshold
    state = CValidationState();
    assert(TestCheckKernelProofOfStake(block, tx, state) == false);
    assert(state.error);
    assert(state.reject_reason == "kernel-too-hard");

    g_stationTier = 3;
    g_kernelHash = 1500; // Should now succeed: baseTarget*5=5000 > 1500
    state = CValidationState();
    assert(TestCheckKernelProofOfStake(block, tx, state) == true);
    assert(!state.error);
    std::cout << "Tier 3 Multiplier Success Test Passed\n";

    // --- Invalid Hash: Always too large ---
    g_stationTier = 3;
    g_baseTarget = 1000;
    g_kernelHash = 6000; // Above any tier's threshold (1000*5=5000)
    state = CValidationState();
    assert(TestCheckKernelProofOfStake(block, tx, state) == false);
    assert(state.error);
    assert(state.reject_reason == "kernel-too-hard");
    std::cout << "Invalid Hash Test Passed\n";

    std::cout << "All RPoSKernelTests Passed.\n";
}

int main() {
    RPoSKernelTests();
    return 0;
}
