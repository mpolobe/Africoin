# Copyright (c) 2025 Africoin Developers
# Distributed under the MIT software license

# Africoin Build System
# This file defines the source files and headers for Africoin-specific components

# Library for common Africoin functionality
libafricoin_common_a_SOURCES = \
  src/security/kernel.cpp \
  src/security/checkpoints.cpp \
  src/security/stakemodifier.cpp \
  src/staking/hybrid_staking.cpp \
  src/railway/railways_staking_manager.cpp

# Non-installed headers
noinst_HEADERS = \
  src/security/kernel.h \
  src/security/checkpoints.h \
  src/security/stakemodifier.h \
  src/security/security_config.h \
  src/staking/hybrid_staking.h \
  src/railway/railway_staking.h \
  src/railway/railways_staking_manager.h

# Include directories
AM_CPPFLAGS = -I$(srcdir)/src

# Note: This Makefile.am is designed to be integrated with the main BlackCoin/Bitcoin
# build system. When building Africoin, this file should be included or merged with
# the main src/Makefile.am from the BlackCoin codebase.
#
# Integration steps:
# 1. Merge these source definitions into the main Makefile.am
# 2. Add appropriate library targets
# 3. Link against required dependencies
