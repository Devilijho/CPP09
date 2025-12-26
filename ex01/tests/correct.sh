# --- VALID CASES ---

echo "Subject Ex 1      => 42"
../RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
echo ""

echo "Subject Ex 2      => 42"
../RPN "7 7 * 7 -"
echo ""

echo "Subject Ex 3      => 0"
../RPN "1 2 * 2 / 2 * 2 4 - +"
echo ""

echo "Simple Add        => 3"
../RPN "1 2 +"
echo ""

echo "Simple Mult       => 81"
../RPN "9 9 *"
echo ""

echo "Simple Sub        => -1"
../RPN "1 2 -"
echo ""

echo "Simple Div        => 2"
../RPN "4 2 /"
echo ""

echo "Int Div (Trunc)   => 4"
../RPN "9 2 /"
echo ""

echo "Zero Add          => 0"
../RPN "0 0 +"
echo ""

echo "Zero Mult         => 0"
../RPN "0 5 *"
echo ""

echo "Zero Sub          => 1"
../RPN "1 0 -"
echo ""

echo "Complex 1         => 14"
../RPN "9 5 +"
echo ""

echo "Complex 2         => -4"
../RPN "5 9 -"
echo ""

echo "Complex 3         => 6"
../RPN "2 3 *"
echo ""

echo "Complex 4         => 4"
../RPN "8 2 /"
echo ""

echo "Chain Add         => 3"
../RPN "1 1 + 1 +"
echo ""

echo "Chain Ops         => 7"
../RPN "1 2 3 * +"
echo ""

echo "Chain Ops 2       => 8"
../RPN "2 2 2 * *"
echo ""

echo "Chain Ops 3       => 23"
../RPN "3 4 5 * +"
echo ""

echo "Chain Ops 4       => 14"
../RPN "5 1 2 + 4 * + 3 -"
echo ""

echo "Large Result      => 531441"
../RPN "9 9 9 9 9 9 * * * * *"
echo ""

echo "Long chain valid  => 45"
../RPN "1 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 +"
echo ""
