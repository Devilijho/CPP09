#!/bin/bash

echo "1 2 + 	=> 3"
../RPN "1 2 +"
echo ""

echo "8 9 * 9 - 9 - 9 - 4 - 1 + 	=> 42"
../RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
echo ""

echo "7 7 * 7 - 	=> 42"
../RPN "7 7 * 7 -"
echo ""

echo "1 2 * 2 / 2 * 2 4 - + 	=> 0"
../RPN "1 2 * 2 / 2 * 2 4 - +"
echo ""

echo "(1 + 1) 	=> ERROR"
../RPN "(1 + 1)"
echo ""

echo "1.2 1.3 + 	=> ERROR"
../RPN "1.2 1.3 +"
echo ""

echo "1 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10 + 	=> ERROR"
../RPN "1 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10 +"
echo ""

echo "-20 20 + 	=> ERROR"
../RPN "-20 20 +"
echo ""

echo "skcus htam	=> ERROR"
../RPN "skcus htam"
echo ""

echo "1skcus 1htam	=> ERROR"
../RPN "1skcus htam"
echo ""

echo "1 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 +  	=> 45"
../RPN "1 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 +"
echo ""
