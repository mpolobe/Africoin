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
    # Add other core files that define rules and state management
    streams.cpp
    util.cpp
)

# --- 3. THE CORE EXECUTABLE (africoin-cli) ---
add_executable(africoin-cli
    main.cpp
    init.cpp
    cli.cpp
    
    # Networking
    net/net.cpp
    net/addrman.cpp
    net/p2p_commands.cpp

    # Wallet & Staking
    wallet/wallet.cpp
    wallet/railwaywallet.cpp
    staking/stakerunner.cpp

    # RPC
    rpc/mining.cpp
    rpc/rpcserver.cpp
)

# Link the executable to the consensus library and external dependencies
target_link_libraries(africoin-cli PRIVATE
    africoin_consensus
    # Standard external dependencies (from root CMakeLists.txt)
    OpenSSL::SSL
    Boost::filesystem
    Boost::system
    # Placeholder for LevelDB and libsecp256k1
)

# --- 4. THE UNIT TEST EXECUTABLE (africoin-test) ---
add_executable(africoin-test
    test/test_main.cpp 
    test/africoin_tests.cpp
    # Include any other test files here
)

# Link the test executable to the consensus library and external dependencies
target_link_libraries(africoin-test PRIVATE
    africoin_consensus
    africoin-cli  # Link to the main executable for its non-consensus files
    # Standard external dependencies
    OpenSSL::SSL
    Boost::test 
    # Placeholder for LevelDB
)

# Tell CMake to install the executables to the system path
install(TARGETS africoin-cli africoin-test DESTINATION bin)
