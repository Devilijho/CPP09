#!/bin/bash

# --- ERROR CASES ---
# "Positive integer sequence" usually implies n > 0 and strict numeric format.

echo "Negative number (Start) => Error"
../PmergeMe "-1 2 3 4 5"
echo ""

echo "Negative number (Middle)=> Error"
../PmergeMe "1 2 -3 4 5"
echo ""

echo "Negative number (End)  => Error"
../PmergeMe "1 2 3 4 -5"
echo ""

echo "Zero (Not positive)    => Error"
../PmergeMe "0 1 2 3"
echo ""

echo "Zero in middle         => Error"
../PmergeMe "5 4 0 2 1"
echo ""

echo "Non-numeric char       => Error"
../PmergeMe "1 2 a 3"
echo ""

echo "Whole string           => Error"
../PmergeMe "one two three"
echo ""

echo "Mixed string/num       => Error"
../PmergeMe "1 2 3four 5"
echo ""

echo "Decimal number         => Error"
../PmergeMe "1 2 3.5 4"
echo ""

echo "Float notation         => Error"
../PmergeMe "1 2 4.0 5"
echo ""

echo "Explicit Plus sign     => Error (Depending on implementation, +1 might be accepted, but strict digit parsing often rejects it)"
../PmergeMe "+1 2 3"
echo ""

echo "Double sign            => Error"
../PmergeMe "++1 2 3"
echo ""

echo "Sign without number    => Error"
../PmergeMe "1 2 + 3"
echo ""

echo "INT_MAX overflow       => Error"
../PmergeMe "1 2 2147483648 4"
echo ""

echo "Long number            => Error"
../PmergeMe "1 2 999999999999999 4"
echo ""

echo "Empty string arg       => Error"
../PmergeMe ""
echo ""

echo "Empty string in seq    => Error"
../PmergeMe "1 2 \"\" 3"
echo ""

echo "Commas (Invalid sep)   => Error"
../PmergeMe "1, 2, 3"
echo ""

echo "Inverse Range          => Error"
../PmergeMe "5-10"
echo ""

echo "Equation               => Error"
../PmergeMe "1+1"
echo ""

echo "Hexadecimal            => Error"
../PmergeMe "0xFF"
echo ""

echo "Octal (starts with 0)  => Error (or treated as 0)"
../PmergeMe "010"
echo ""

echo "Negative Zero          => Error"
../PmergeMe "-0"
echo ""

echo "Only Hyphen            => Error"
../PmergeMe "-"
echo ""

echo "Space in quotes        => Error"
../PmergeMe "1 2 ' ' 3"
echo ""
