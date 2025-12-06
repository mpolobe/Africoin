// Copyright (c) 2025 Africoin Developers
// Distributed under the MIT software license

#ifndef AFRICOIN_RAILWAYS_STAKING_MANAGER_H
#define AFRICOIN_RAILWAYS_STAKING_MANAGER_H

#include "railway/railway_staking.h"
#include "security/security_config.h"
#include <map>
#include <vector>
#include <string>
#include <ctime>

// Forward declarations (placeholders for Bitcoin/BlackCoin types)
class CBlockHeader {
public:
    // Placeholder - to be replaced with actual implementation
    uint32_t nTime;
    uint32_t nBits;
};

class uint256 {
public:
    // Placeholder - to be replaced with actual implementation
    unsigned char data[32];
};

class AfricaRailwaysStakingManager {
private:
    std::map<std::string, RailwayStakingNode> railwayNodes;

public:
    AfricaRailwaysStakingManager();
    
    void InitializeRailwayNodes();
    
    RailwayStakingNode CreateRailwayStakingNode(const RailwayNodeConfig& config);
    
    bool ValidateRailwayStake(const RailwayStakingNode& node, const CBlockHeader& block);
    
    bool ProcessRailwayStake(const RailwayStakingNode& node, const CBlockHeader& block);
    
    double CalculateSecurityScore();
    
    std::vector<std::string> GenerateSecurityRecommendations();
    
    int64_t GetTime() const;
    
    StakingHealthReport GetNetworkHealth();
    
    const RailwayStakingNode* GetRailwayNode(const std::string& code) const;
    
    const std::map<std::string, RailwayStakingNode>& GetAllNodes() const;
};

#endif // AFRICOIN_RAILWAYS_STAKING_MANAGER_H
