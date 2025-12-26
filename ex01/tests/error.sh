#!/bin/bash

# --- ERROR CASES ---

echo "Empty string      => Error"
../RPN ""
echo ""

echo "Spaces only       => Error"
../RPN "     "
echo ""

echo "Operator only     => Error"
../RPN "+"
echo ""

echo "1 operand only    => Error"
../RPN "1"
echo ""

echo "Not enough nums   => Error"
../RPN "1 +"
echo ""

echo "Stack underflow   => Error"
../RPN "1 2 + -"
echo ""

echo "Unfinished ops    => Error"
../RPN "1 2 3 +"
echo ""

echo "Too many nums     => Error"
../RPN "1 2 3 *"
echo ""

echo "Division by zero  => Error"
../RPN "1 0 /"
echo ""

echo "Modulo forbidden  => Error"
../RPN "1 2 %"
echo ""

echo "Brackets forbidden => Error"
../RPN "(1 + 1)"
echo ""

echo "Decimals forbidden => Error"
../RPN "1.5 2 +"
echo ""

echo "Number >= 10      => Error"
../RPN "10 5 +"
echo ""

echo "Number >= 10      => Error"
../RPN "12 +"
echo ""

echo "Number >= 10      => Error"
../RPN "1 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10 +"
echo ""

echo "Alphabet chars    => Error"
../RPN "a b +"
echo ""

echo "Words             => Error"
../RPN "skcus htam"
echo ""

echo "Mixed words/nums  => Error"
../RPN "1skcus htam"
echo ""

echo "Negative input    => Error (Inputs must be < 10)"
../RPN "-5 2 +"
echo ""

echo "Start with op     => Error"
../RPN "* 1 2"
echo ""

echo "Double operator   => Error"
../RPN "1 2 + +"
echo ""

echo "Div 0 via calc    => Error"
../RPN "5 2 / 0 /"
echo ""
