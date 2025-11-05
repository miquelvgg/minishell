#!/bin/bash
INPUT=README.md
NA=a.txt
make re
WHITE='\033[37m'
RED='\033[31m'
BLUE='\033[34m'
declare -i C
C=0

#"infiles/basic.txt" "cat -e" "" "outfiles/outfile"
PTEST="cat -e"
STEST=""
OUTPUT=$C$NA
echo -e "$WHITE TEST $C: Empty 2 param$BLUE"
./pipex $INPUT $PTEST $STEST y$OUTPUT
echo -e "$RED Errorno: $?$BLUE"
<$INPUT $PTEST | $STEST >b$OUTPUT
echo -e "$RED Errorno: $?$BLUE"
wait
diff -s y$OUTPUT b$OUTPUT
C+=1
