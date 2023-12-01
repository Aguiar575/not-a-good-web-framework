#!/bin/bash

# SHOULD HAVE THE CLANG-FORMAT IN YOUR MACHINE
# Get the directory where the script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Assume the project is in the parent directory of the script
PROJECT_PATH="$SCRIPT_DIR/.."

# Find all C++ and header files and run the formatting commands
find "$PROJECT_PATH" -type f \( -name "*.cpp" -o -name "*.h" \) -exec sh -c '
    file="$1"
    clang-format -i "$file"
' _ {} \;

echo "Script completed."

