#!/bin/bash

# Quick run script - finds and runs executables in the current directory
# Usage: ./run.sh [executable_name]

set -e

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Get current directory
CURRENT_DIR="$(pwd)"

if [ $# -eq 1 ]; then
    # Specific executable provided
    EXECUTABLE="$1"
    if [ -f "$EXECUTABLE" ] && [ -x "$EXECUTABLE" ]; then
        echo -e "${GREEN}Running: $EXECUTABLE${NC}"
        "./$EXECUTABLE"
    else
        echo -e "${RED}Error: '$EXECUTABLE' not found or not executable${NC}"
        exit 1
    fi
else
    # Find executables in current directory (prioritize .out files)
    EXECUTABLES=($(find . -maxdepth 1 -name "*.out" -type f -executable | sort))

    # If no .out files found, look for other executables
    if [ ${#EXECUTABLES[@]} -eq 0 ]; then
        EXECUTABLES=($(find . -maxdepth 1 -type f -executable -not -name "*.sh" -not -name ".*" | sort))
    fi

    if [ ${#EXECUTABLES[@]} -eq 0 ]; then
        echo -e "${RED}No executables found in current directory${NC}"
        exit 1
    elif [ ${#EXECUTABLES[@]} -eq 1 ]; then
        # Only one executable found, run it
        EXECUTABLE="${EXECUTABLES[0]}"
        echo -e "${GREEN}Found and running: $EXECUTABLE${NC}"
        "$EXECUTABLE"
    else
        # Multiple executables found, let user choose
        echo -e "${YELLOW}Multiple executables found:${NC}"
        for i in "${!EXECUTABLES[@]}"; do
            echo "  $((i+1)). ${EXECUTABLES[$i]}"
        done

        echo -n "Choose executable (1-${#EXECUTABLES[@]}): "
        read choice

        if [[ "$choice" =~ ^[0-9]+$ ]] && [ "$choice" -ge 1 ] && [ "$choice" -le ${#EXECUTABLES[@]} ]; then
            EXECUTABLE="${EXECUTABLES[$((choice-1))]}"
            echo -e "${GREEN}Running: $EXECUTABLE${NC}"
            "$EXECUTABLE"
        else
            echo -e "${RED}Invalid choice${NC}"
            exit 1
        fi
    fi
fi
