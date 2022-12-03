#!/bin/bash

PATH_TO="../../datasets/"
#FILE = bytes.txt
FILE="first.txt"
#FILE="one_empty_line.txt"
DIR_TRACES="_traces/"
#flags=""
 flags="-s"
#flags="-b"
#flags="-n"
#flags="-e"
#flags="--show-nonprinting"

touch 42.txt
rm *.txt

## Вывод cat без флагов
#echo "cat $PATH_TO$FILE"
#cat $PATH_TO$FILE
#echo ""

clear
make

rm -rf $DIR_TRACES
mkdir $DIR_TRACES

#for flags in -b -e -n -s -t -v
#do
#    echo "cat $flags $PATH_TO$FILE"
    echo "------------------------"
    echo "orig: cat $flags"
    cat $flags $PATH_TO$FILE
    echo "--------------"
    echo "s21_: s21_cat $flags"
    ./s21_cat $flags $PATH_TO$FILE
    echo "--------------"
    cd $DIR_TRACES && cat $flags ../$PATH_TO$FILE > orig$flags.txt && ../s21_cat $flags ../$PATH_TO$FILE > s21$flags.txt
    diff -s orig$flags.txt s21$flags.txt
    echo "--------------"
#done

## Вывод всех флагов одновременно
#    flags="-b -e -n -s -t -v"
#    echo "--------------"
#    echo "cat $flags"
#    cat $flags $PATH_TO$FILE

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
