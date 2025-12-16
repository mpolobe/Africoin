# src/CMakeLists.txt

# 1. Define the core consensus static library
# in src/CMakeLists.txt

# --- 1. SET INCLUDES & DEFINITIONS ---
# Add the current directory and its subdirectories to the include path
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/consensus
    ${CMAKE_CURRENT_SOURCE_DIR}/railway
    ${CMAKE_CURRENT_SOURCE_DIR}/staking
    ${CMAKE_CURRENT_SOURCE_DIR}/wallet
    ${CMAKE_CURRENT_SOURCE_DIR}/net
)

# --- 2. THE CONSENSUS LIBRARY (Static Library) ---
# Separates core consensus logic for easy linking and testing
add_library(africoin_consensus STATIC
    consensus/validation.cpp
    consensus/pos_kernel.cpp
    railway/railway_db.cpp
    railway/railway_manager.cpp
    feeburner.cpp
    streams.cpp
    util.cpp
)

target_include_directories(africoin_consensus PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/consensus
    ${CMAKE_CURRENT_SOURCE_DIR}/railway
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 2. Define the main node executable
add_executable(africoin-cli 
    main.cpp
    init.cpp
    net/net.cpp
    net/addrman.cpp
    net/protocol.h
    wallet/wallet.cpp
    wallet/staking.cpp
    rpc/mining.cpp
)

# Link main executable to consensus lib and system deps
target_link_libraries(africoin-cli
    africoin_consensus
    OpenSSL::SSL
    Boost::filesystem
    Boost::system
)

# 3. Define the test executable
add_executable(africoin-test
    test/africoin_tests.cpp
    test/railway_tests.cpp
)

# Link test runner to consensus lib and system deps
target_link_libraries(africoin-test
    africoin_consensus
    OpenSSL::SSL
    Boost::filesystem
    Boost::system
)

# Optionally, set compile options and include paths globally
target_compile_features(africoin-cli PRIVATE cxx_std_20)
target_compile_features(africoin-test PRIVATE cxx_std_20)
