#!/bin/bash
# Apply Africoin branding changes

set -e

echo "Replacing BlackCoin with Africoin branding..."

# Find and replace text in files
# Using a more targeted approach to avoid unintended replacements
find . -type f \( -name "*.cpp" -o -name "*.h" -o -name "*.md" -o -name "*.txt" -o -name "*.json" \) \
    -not -path "./.git/*" \
    -exec sed -i \
        -e 's/BlackCoin/Africoin/g' \
        -e 's/blackcoin/africoin/g' \
        -e 's/BLACKCOIN/AFRICOIN/g' \
        {} +

echo "Branding applied successfully!"
