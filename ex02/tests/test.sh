echo "SORT 3000 numbers"

for i in {1..10}
	do
		ARG=$(shuf -i 1-100000 -n 3000 | tr '\n' ' ') && ../PmergeMe $ARG | grep "After" | cut -d ':' -f 2 | tr ' ' '\n' | grep -v "^$" | sort -n -c && echo "OK: Sorted Correctly" || echo "FAIL: Not Sorted"
	done

echo "SORT WEIRD CASES"

../PmergeMe -12 0 3

../PmergeMe 0 0 0 3

../PmergeMe 2 1
