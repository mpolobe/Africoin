// Copyright (c) 2025 Africoin Developers
// Distributed under the MIT software license

#ifndef AFRICOIN_RAILWAY_STAKING_H
#define AFRICOIN_RAILWAY_STAKING_H

#include <string>
#include <vector>
#include <cstdint>

// Railway node configuration
struct RailwayNodeConfig {
    std::string name;
    std::string code;
    int64_t allocation;
    
    RailwayNodeConfig(const std::string& n, const std::string& c, int64_t a)
        : name(n), code(c), allocation(a) {}
};

// Railway staking node
struct RailwayStakingNode {
    std::string name;
    std::string code;
    int64_t allocation;
    bool isActive;
    int64_t lastStakeTime;
    int64_t totalStakes;
    double stakingWeight;
    
    RailwayStakingNode() 
        : isActive(false), lastStakeTime(0), totalStakes(0), stakingWeight(1.0) {}
};

// Staking health report
struct StakingHealthReport {
    double railwayParticipation;
    double networkSecurityScore;
    std::vector<std::string> recommendations;
    
    StakingHealthReport() 
        : railwayParticipation(0.0), networkSecurityScore(0.0) {}
};

#endif // AFRICOIN_RAILWAY_STAKING_H
