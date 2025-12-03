#!/bin/bash

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_parsing.sh                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maseveri <maseveri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/03 00:00:00 by maseveri          #+#    #+#              #
#    Updated: 2025/12/03 00:00:00 by maseveri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Couleurs pour l'output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Compteurs
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

echo -e "${BLUE}╔════════════════════════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║           CUB3D PARSING TESTER                             ║${NC}"
echo -e "${BLUE}╔════════════════════════════════════════════════════════════╗${NC}"
echo ""

# Check if cub3d executable exists
if [ ! -f "./cub3d" ]; then
    echo -e "${RED}Error: ./cub3d executable not found${NC}"
    echo -e "${YELLOW}Please compile your project first with 'make'${NC}"
    echo -e "${YELLOW}Or use the C unit tester: gcc test_parsing.c parsing/*.c -I. -o test_parsing && ./test_parsing${NC}"
    exit 1
fi

# Fonction pour tester un fichier valide
test_valid_map() {
    local map_file=$1
    local test_name=$2
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    echo -ne "Testing ${YELLOW}${test_name}${NC}... "
    
    # Exécuter le programme (remplacer par ton exécutable)
    ./cub3d "$map_file" > /dev/null 2>&1
    local exit_code=$?
    
    if [ $exit_code -eq 0 ]; then
        echo -e "${GREEN}✓ PASS${NC}"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}✗ FAIL${NC} (Expected success, got error)"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
}

# Fonction pour tester un fichier invalide
test_invalid_map() {
    local map_file=$1
    local test_name=$2
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    echo -ne "Testing ${YELLOW}${test_name}${NC}... "
    
    # Exécuter le programme (remplacer par ton exécutable)
    ./cub3d "$map_file" > /dev/null 2>&1
    local exit_code=$?
    
    if [ $exit_code -ne 0 ]; then
        echo -e "${GREEN}✓ PASS${NC}"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}✗ FAIL${NC} (Expected error, got success)"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
}

echo -e "${BLUE}═══════════════════════════════════════════════════════════${NC}"
echo -e "${BLUE}  VALID MAPS TESTS${NC}"
echo -e "${BLUE}═══════════════════════════════════════════════════════════${NC}"
echo ""

# Tests des maps valides
if [ -d "maps/good" ]; then
    for map in maps/good/*.cub; do
        if [ -f "$map" ]; then
            test_valid_map "$map" "$(basename $map)"
        fi
    done
else
    echo -e "${YELLOW}Warning: maps/good directory not found${NC}"
fi

echo ""
echo -e "${BLUE}═══════════════════════════════════════════════════════════${NC}"
echo -e "${BLUE}  INVALID MAPS TESTS${NC}"
echo -e "${BLUE}═══════════════════════════════════════════════════════════${NC}"
echo ""

# Tests des maps invalides
if [ -d "maps/bad" ]; then
    for map in maps/bad/*; do
        if [ -f "$map" ]; then
            test_invalid_map "$map" "$(basename $map)"
        fi
    done
else
    echo -e "${YELLOW}Warning: maps/bad directory not found${NC}"
fi

echo ""
echo -e "${BLUE}═══════════════════════════════════════════════════════════${NC}"
echo -e "${BLUE}  EDGE CASES TESTS${NC}"
echo -e "${BLUE}═══════════════════════════════════════════════════════════${NC}"
echo ""

# Test sans argument
TOTAL_TESTS=$((TOTAL_TESTS + 1))
echo -ne "Testing ${YELLOW}No arguments${NC}... "
./cub3d > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo -e "${GREEN}✓ PASS${NC}"
    PASSED_TESTS=$((PASSED_TESTS + 1))
else
    echo -e "${RED}✗ FAIL${NC}"
    FAILED_TESTS=$((FAILED_TESTS + 1))
fi

# Test fichier inexistant
TOTAL_TESTS=$((TOTAL_TESTS + 1))
echo -ne "Testing ${YELLOW}Non-existent file${NC}... "
./cub3d "maps/nonexistent.cub" > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo -e "${GREEN}✓ PASS${NC}"
    PASSED_TESTS=$((PASSED_TESTS + 1))
else
    echo -e "${RED}✗ FAIL${NC}"
    FAILED_TESTS=$((FAILED_TESTS + 1))
fi

# Test mauvaise extension
TOTAL_TESTS=$((TOTAL_TESTS + 1))
echo -ne "Testing ${YELLOW}Wrong extension (.txt)${NC}... "
touch /tmp/test.txt
./cub3d "/tmp/test.txt" > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo -e "${GREEN}✓ PASS${NC}"
    PASSED_TESTS=$((PASSED_TESTS + 1))
else
    echo -e "${RED}✗ FAIL${NC}"
    FAILED_TESTS=$((FAILED_TESTS + 1))
fi
rm -f /tmp/test.txt

# Test fichier vide
TOTAL_TESTS=$((TOTAL_TESTS + 1))
echo -ne "Testing ${YELLOW}Empty .cub file${NC}... "
touch /tmp/empty.cub
./cub3d "/tmp/empty.cub" > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo -e "${GREEN}✓ PASS${NC}"
    PASSED_TESTS=$((PASSED_TESTS + 1))
else
    echo -e "${RED}✗ FAIL${NC}"
    FAILED_TESTS=$((FAILED_TESTS + 1))
fi
rm -f /tmp/empty.cub

echo ""
echo -e "${BLUE}═══════════════════════════════════════════════════════════${NC}"
echo -e "${BLUE}  RESULTS${NC}"
echo -e "${BLUE}═══════════════════════════════════════════════════════════${NC}"
echo ""
echo -e "Total tests:  ${BLUE}${TOTAL_TESTS}${NC}"
echo -e "Passed:       ${GREEN}${PASSED_TESTS}${NC}"
echo -e "Failed:       ${RED}${FAILED_TESTS}${NC}"
echo ""

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "${GREEN}╔════════════════════════════════════════════════════════════╗${NC}"
    echo -e "${GREEN}║                  ALL TESTS PASSED! 🎉                      ║${NC}"
    echo -e "${GREEN}╚════════════════════════════════════════════════════════════╝${NC}"
    exit 0
else
    echo -e "${RED}╔════════════════════════════════════════════════════════════╗${NC}"
    echo -e "${RED}║              SOME TESTS FAILED ❌                          ║${NC}"
    echo -e "${RED}╚════════════════════════════════════════════════════════════╝${NC}"
    exit 1
fi
