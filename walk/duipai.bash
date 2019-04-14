while true; do
./data
./1 < 1.in > 1.out
./4 < 1.in > 2.out
if diff 1.out 2.out;then
	echo AC
else
	echo WA
	exit 0
fi
done
