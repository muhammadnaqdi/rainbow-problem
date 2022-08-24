for i in {5..10}
do
	for j in {4..7}
	do
		./rainbow $i $j > results/$i$j.txt
	done
done
