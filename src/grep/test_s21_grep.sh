#!/bin/bash

PATH_TO="./"
FILE="lyrics.txt"
DIR_TRACES="_traces/"
 FLAGS="-e"
 PATTERN="me"

TEST_CASE="grep $FLAGS $PATTERN $PATH_TO$FILE"

clear
make

rm -rf $DIR_TRACES
mkdir $DIR_TRACES

echo "------------------------"
echo "orig: $TEST_CASE"
$TEST_CASE
echo "--------------"
echo "s21_: ./s21_$TEST_CASE"
./s21_$TEST_CASE
echo "--------------"

PATH_TO="../$PATH_TO"
TEST_CASE="grep $FLAGS $PATTERN $PATH_TO$FILE"

cd $DIR_TRACES && $TEST_CASE > orig$FLAGS-$PATTERN.txt && ../s21_$TEST_CASE > s21$FLAGS-$PATTERN.txt
diff -s orig$FLAGS-$PATTERN.txt s21$FLAGS-$PATTERN.txt

DIFF_RES="$(diff -s orig$FLAGS-$PATTERN.txt s21$FLAGS-$PATTERN.txt)"
if [ "$DIFF_RES" == "Files orig$FLAGS-$PATTERN.txt and s21$FLAGS-$PATTERN.txt are identical" ]
  then
    echo -e "Test: \033[32m✅  Passed\033[0m"
  else
    echo -e "Test: \033[31m❌  Failed\033[0m"
fi
echo "--------------"
