#!/bin/bash
# Apply Africoin branding changes

set -e

echo "Replacing BlackCoin with Africoin branding..."

# Find and replace text in files
find . -type f \( -name "*.cpp" -o -name "*.h" -o -name "*.md" -o -name "*.txt" -o -name "*.json" \) \
    -not -path "./.git/*" \
    -exec sed -i 's/BlackCoin/Africoin/g' {} + \
    -exec sed -i 's/blackcoin/africoin/g' {} + \
    -exec sed -i 's/BLACKCOIN/AFRICOIN/g' {} + \
    -exec sed -i 's/BLK/AFR/g' {} +

echo "Branding applied successfully!"
