#!/bin/bash

FILE="lyrics.txt pattern.file"
 FLAGS=""
 PATTERN="me"

TEST_CASE="grep $FLAGS $PATTERN $FILE"

rm *.log

clear
make

echo "------------------------"
echo "orig: $TEST_CASE"
$TEST_CASE
echo "--------------"
echo "s21_: ./s21_$TEST_CASE"
./s21_$TEST_CASE
echo "--------------"

      $TEST_CASE > orig$FLAGS-$PATTERN.log 
./s21_$TEST_CASE > s21_$FLAGS-$PATTERN.log
diff -s orig$FLAGS-$PATTERN.log s21_$FLAGS-$PATTERN.log

DIFF_RES="$(diff -s orig$FLAGS-$PATTERN.log s21_$FLAGS-$PATTERN.log)"
if [ "$DIFF_RES" == "Files orig$FLAGS-$PATTERN.log and s21_$FLAGS-$PATTERN.log are identical" ]
  then
    echo -e "Test: \033[32m✅  Passed\033[0m"
  else
    echo -e "Test: \033[31m❌  Failed\033[0m"
fi
echo "--------------"
