#!/bin/bash

#
# Copyright (с) 2022 Student of School 21:
# Yonn Argelia
#
# yonnarge@student.21-school.ru
#

# Test case naming:
#GS1E
#G - grep
#S - single file / M - multiple files
#1 - number test case
#E - flag / IV - multiple flags

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIF_RES=""
TC_NAME=""
FLAGS=""
PATTERN=""
FILE=""
TEST_CASE="grep $FLAGS $PATTERN $FILE"


function clear_vars() {
  FLAGS=""
  PATTERN=""
  FILE=""
}

function run_utils() {
  $TEST_CASE > orig_$TC_NAME.log
  ./s21_$TEST_CASE > s21_$TC_NAME.log
}

function compare_results() {
  DIF_RES="$(diff -s orig_$TC_NAME.log s21_$TC_NAME.log)"

  if [ "$DIF_RES" == "Files orig_$TC_NAME.log and s21_$TC_NAME.log are identical" ]
    then
      echo -e "Test:$TC_NAME: \033[32m✅  Passed\033[0m"
      (( COUNTER_SUCCESS++ ))
    else
      echo -e "Test:$TC_NAME: \033[31m❌  Failed\033[0m"
      (( COUNTER_FAIL++ ))
  fi
}

function run_test_case() {
  clear_vars
  run_utils
  compare_results
}

rm *.log
clear
make

echo "--------------------------------------------------------------"
#-------------------------------------------------------------------
#TEST CASE GS1E
TC_NAME="GS1E"
FLAGS="-e"
PATTERN="rock"
FILE="lyrics.txt"
TEST_CASE="grep $FLAGS $PATTERN $FILE"
run_test_case
#-------------------------------------------------------------------
#TEST CASE GS2E
TC_NAME="GS2E"
FLAGS="-e"
PATTERN="me"
FILE="lyrics.txt"
TEST_CASE="grep $FLAGS $PATTERN $FILE"
run_test_case
#-------------------------------------------------------------------
#TEST CASE GS3E
TC_NAME="GS2E"
FLAGS="-e"
PATTERN="rock -e back"
FILE="lyrics.txt"
TEST_CASE="grep $FLAGS $PATTERN $FILE"
run_test_case
#-------------------------------------------------------------------
#TEST CASE GM4E
TC_NAME="GM4E"
FLAGS="-e"
PATTERN="rock"
FILE="lyrics.txt"
TEST_CASE="grep $FLAGS $PATTERN $FILE"
run_test_case
#-------------------------------------------------------------------












echo "--------------------------------------------------------------"
echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"
echo "--------------------------------------------------------------"
