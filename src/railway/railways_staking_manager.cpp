// Copyright (c) 2025 Africoin Developers
// Distributed under the MIT software license

#include "railway/railways_staking_manager.h"

AfricaRailwaysStakingManager::AfricaRailwaysStakingManager() {
    InitializeRailwayNodes();
}

void AfricaRailwaysStakingManager::InitializeRailwayNodes() {
    std::vector<RailwayNodeConfig> stations = {
        {"johannesburg", "JNB", 500000 * COIN}, // 500k AFRC allocation
        {"nairobi", "NBO", 500000 * COIN},
        {"cairo", "CAI", 500000 * COIN},
        {"lagos", "LOS", 500000 * COIN},
        {"cape_town", "CPT", 300000 * COIN},
        {"addis_ababa", "ADD", 300000 * COIN}
    };

    for (const auto& station : stations) {
        railwayNodes[station.code] = CreateRailwayStakingNode(station);
    }
}

RailwayStakingNode AfricaRailwaysStakingManager::CreateRailwayStakingNode(const RailwayNodeConfig& config) {
    RailwayStakingNode node;
    node.name = config.name;
    node.code = config.code;
    node.allocation = config.allocation;
    node.isActive = true;
    node.lastStakeTime = std::time(nullptr);
    node.totalStakes = 0;
    node.stakingWeight = RAILWAY_STAKE_WEIGHT_MULTIPLIER;
    return node;
}

bool AfricaRailwaysStakingManager::ValidateRailwayStake(const RailwayStakingNode& node, const CBlockHeader& block) {
    // TODO: Integrate with PeerCoin kernel validation from PR#4
    // This will call: PeerCoin::Kernel::CheckProofOfStake()
    
    if (!node.isActive) {
        return false;
    }

    // Check minimum stake age
    int64_t stakeAge = std::time(nullptr) - node.lastStakeTime;
    if (stakeAge < RAILWAY_MIN_STAKE_AGE) {
        return false;
    }

    // Check maximum stake age
    if (stakeAge > RAILWAY_MAX_STAKE_AGE) {
        return false;
    }

    return true;
}

bool AfricaRailwaysStakingManager::ProcessRailwayStake(const RailwayStakingNode& node, const CBlockHeader& block) {
    // Apply enhanced security for railway nodes
    if (!ValidateRailwayStake(node, block)) {
        return false;
    }

    // TODO: Use hybrid staking with PeerCoin security modules from PR#4
    // Will integrate with:
    // - src/security/kernel.cpp
    // - src/security/checkpoints.cpp
    // - src/security/stakemodifier.cpp
    
    return true;
}

double AfricaRailwaysStakingManager::CalculateSecurityScore() {
    int activeNodes = 0;
    int64_t totalStakingPower = 0;
    
    for (const auto& pair : railwayNodes) {
        const RailwayStakingNode& node = pair.second;
        if (node.isActive && node.lastStakeTime > std::time(nullptr) - SECONDS_PER_DAY) {
            activeNodes++;
            totalStakingPower += node.allocation;
        }
    }

    double participationScore = (double)activeNodes / railwayNodes.size();
    double stakingScore = (totalStakingPower > 0) ? 1.0 : 0.0;
    
    return (participationScore * PARTICIPATION_WEIGHT) + (stakingScore * STAKING_POWER_WEIGHT);
}

std::vector<std::string> AfricaRailwaysStakingManager::GenerateSecurityRecommendations() {
    std::vector<std::string> recommendations;
    
    int activeNodes = 0;
    for (const auto& pair : railwayNodes) {
        if (pair.second.isActive && 
            pair.second.lastStakeTime > std::time(nullptr) - SECONDS_PER_DAY) {
            activeNodes++;
        }
    }

    double participation = (double)activeNodes / railwayNodes.size();
    
    if (participation < MIN_HEALTHY_PARTICIPATION) {
        recommendations.push_back("WARNING: Railway node participation below 66%");
        recommendations.push_back("RECOMMENDATION: Activate more railway staking nodes");
    }

    double securityScore = CalculateSecurityScore();
    if (securityScore < MIN_SECURITY_SCORE) {
        recommendations.push_back("WARNING: Network security score below threshold");
        recommendations.push_back("RECOMMENDATION: Increase railway node allocations");
    }

    if (recommendations.empty()) {
        recommendations.push_back("HEALTHY: Railway staking network is performing well");
    }

    return recommendations;
}

int64_t AfricaRailwaysStakingManager::GetTime() const {
    return std::time(nullptr);
}

StakingHealthReport AfricaRailwaysStakingManager::GetNetworkHealth() {
    StakingHealthReport report;
    int activeRailwayNodes = 0;

    for (const auto& pair : railwayNodes) {
        const RailwayStakingNode& node = pair.second;
        if (node.isActive && node.lastStakeTime > GetTime() - SECONDS_PER_DAY) {
            activeRailwayNodes++;
        }
    }

    report.railwayParticipation = (double)activeRailwayNodes / railwayNodes.size();
    report.networkSecurityScore = CalculateSecurityScore();
    report.recommendations = GenerateSecurityRecommendations();

    return report;
}

const RailwayStakingNode* AfricaRailwaysStakingManager::GetRailwayNode(const std::string& code) const {
    auto it = railwayNodes.find(code);
    if (it != railwayNodes.end()) {
        return &it->second;
    }
    return nullptr;
}

const std::map<std::string, RailwayStakingNode>& AfricaRailwaysStakingManager::GetAllNodes() const {
    return railwayNodes;
}
