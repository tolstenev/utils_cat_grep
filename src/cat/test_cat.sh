#!/bin/bash

PATH_TO="../../datasets/"
#FILE = bytes.txt
FILE="first.txt"

./s21_cat $PATH_TO$FILE > s21.txt
cat $PATH_TO$FILE > orig.txt
diff s21.txt orig.txt
rm s21.txt orig.txt

// TODO