# --- VALID CASES ---

echo "Subject Example        => Sorted"
../PmergeMe 3 5 9 7 4
echo ""

echo "Single Number          => 42"
../PmergeMe 42
echo ""

echo "Two Numbers Sorted     => 1 2"
../PmergeMe 1 2
echo ""

echo "Two Numbers Unsorted   => 1 2"
../PmergeMe 2 1
echo ""

echo "Three Numbers Random   => 1 2 3"
../PmergeMe 3 1 2
echo ""

echo "Reverse Order          => 1 2 3 4 5"
../PmergeMe 5 4 3 2 1
echo ""

echo "Already Sorted         => 1 2 3 4 5"
../PmergeMe 1 2 3 4 5
echo ""

echo "Even amount of args    => Sorted"
../PmergeMe 10 8 6 4 2 1
echo ""

echo "Odd amount of args     => Sorted"
../PmergeMe 9 7 5 3 1
echo ""

echo "Duplicates (if handled)=> 1 1 2 2 3 3"
../PmergeMe 1 2 3 1 2 3
echo ""

echo "Large Gaps             => 1 100 1000"
../PmergeMe 1000 1 100
echo ""

echo "INT_MAX Boundary       => Sorted"
../PmergeMe 2147483647 1 42
echo ""

echo "Small consecutive      => 1 2 3 4 5 6 7 8 9 10"
../PmergeMe 10 9 8 7 6 5 4 3 2 1
echo ""

echo "Fibonacci scrambled    => 1 1 2 3 5 8 13 21"
../PmergeMe 21 1 13 2 8 3 5 1
echo ""

echo "Powers of 2            => 2 4 8 16 32 64"
../PmergeMe 64 32 16 8 4 2
echo ""

echo "Prime numbers          => 2 3 5 7 11 13 17"
../PmergeMe 17 13 11 7 5 3 2
echo ""

echo "Random sequence 10     => Sorted"
../PmergeMe 98 12 33 4 1 99 2 8 55 42
echo ""

echo "Alternating High/Low   => Sorted"
../PmergeMe 100 1 99 2 98 3 97 4
echo ""


echo "Subject large ex (shuf)=> Sorted (Check output manually)"
../PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
echo ""

echo "Large input (50)       => Sorted"
../PmergeMe `shuf -i 1-1000 -n 50 | tr "\n" " "`
echo ""

echo "Large input (100)      => Sorted"
../PmergeMe `shuf -i 1-1000 -n 100 | tr "\n" " "`
echo ""

echo "Large input (500)      => Sorted"
../PmergeMe `shuf -i 1-5000 -n 500 | tr "\n" " "`
echo ""

echo "Large input (1000)     => Sorted"
../PmergeMe `shuf -i 1-10000 -n 1000 | tr "\n" " "`
echo ""

echo "Deep Recursion Check   => Sorted"
../PmergeMe 12 45 8 2 1 9 55 23 88 10 6 4 99 100 101 09 03
echo ""


echo "Variable Length Args   => Sorted"
ARG="4 8 1 2"; ../PmergeMe $ARG
echo ""

echo "Max capacity (3001)    => Sorted (Time check)"
../PmergeMe `shuf -i 1-10000 -n 3001 | tr "\n" " "`
echo ""
