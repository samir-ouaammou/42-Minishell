#!/bin/bash

MANGENTA="\033[35m"
BOLD="\033[1m"
CLEAR_LINE="\033[2K"
LINE_UP="\033[1A"
RED="\033[31m"
WHITE="\033[37m"
GRAY="\033[90m"
BLUE="\033[34m"
GREEN="\033[32m"
RESET="\033[0m"

spin[0]="⠁"
spin[1]="⠃"
spin[2]="⠇"
spin[3]="⠧"
spin[4]="⠷"
spin[5]="⠿"
spin[6]="⠷"
spin[7]="⠧"
spin[8]="⠇"
spin[9]="⠃"

echo -ne "$WHITE${spin[0]}$RESET Loading...\n"
for i in {1..3}; do
    for j in "${spin[@]}"; do
        echo -ne "$LINE_UP$WHITE$j$RESET Processing...\n"
        sleep 0.1
    done
done

printf "$LINE_UP$CLEAR_LINE$GREEN$BOLD✔$RESET Compilation finished successfully!$WHITE$BOLD\n"
