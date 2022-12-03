#!/bin/bash

PATH_TO="../../datasets/"
#FILE = bytes.txt
FILE="first.txt"
DIR_TRACES="_traces/"
#flags=""
#flags="-s"
#flags="-b"
#flags="-t"
 flags="-e"
#flags="--show-nonprinting"

touch 42.txt
rm *.txt

clear
make

rm -rf $DIR_TRACES
mkdir $DIR_TRACES

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
