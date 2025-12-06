// Copyright (c) 2025 Africoin Developers
// Distributed under the MIT software license

#ifndef AFRICOIN_SECURITY_CONFIG_H
#define AFRICOIN_SECURITY_CONFIG_H

#include <cstdint>

// COIN constant (typically 100000000 satoshis = 1 coin)
static const int64_t COIN = 100000000;

// Security thresholds
static const int RAILWAY_MIN_STAKE_AGE = 60 * 60 * 8; // 8 hours
static const int RAILWAY_MAX_STAKE_AGE = 60 * 60 * 24 * 90; // 90 days
static const double RAILWAY_STAKE_WEIGHT_MULTIPLIER = 1.5;

// Network health thresholds
static const double MIN_HEALTHY_PARTICIPATION = 0.66; // 66% railway nodes active
static const double MIN_SECURITY_SCORE = 0.75;

#endif // AFRICOIN_SECURITY_CONFIG_H
