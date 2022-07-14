#!/bin/bash

PATH_TO="../../datasets/"
#FILE = bytes.txt
FILE="first.txt"
flags="-s"

touch 42.txt
rm *.txt

## Вывод cat без флагов
#echo "cat $PATH_TO$FILE"
#cat $PATH_TO$FILE
#echo ""

make
clear

#for flags in -b -e -n -s -t -v
#do
#    echo "cat $flags $PATH_TO$FILE"
    echo "--------------"
    echo "cat $flags"
    cat $flags $PATH_TO$FILE
    echo ""
    echo "--------------"
    echo "s21_cat $flags"
    ./s21_cat $flags $PATH_TO$FILE
    echo ""
    echo "--------------"
    cat $flags $PATH_TO$FILE > orig.txt
    ./s21_cat $flags $PATH_TO$FILE > s21_.txt
    diff -s orig.txt s21_.txt
    echo "--------------"
#done


#COUNTER_SUCCESS=0
#COUNTER_FAIL=0
#DIFF_RES=""
#TEST_FILE="bytes.txt"
#echo "" > log.txt
#
#for var in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
#do
#          TEST1="$var $TEST_FILE"
#          echo "$TEST1"
#          ./s21_cat $TEST1 > s21_cat.txt
#          cat $TEST1 > cat.txt
#          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
#          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
#            then
#              (( COUNTER_SUCCESS++ ))
#            else
#              echo "$TEST1" >> log.txt
#              (( COUNTER_FAIL++ ))
#          fi
#          rm s21_cat.txt cat.txt
#done
#
#
#echo "SUCCESS: $COUNTER_SUCCESS"
#echo "FAIL: $COUNTER_FAIL"